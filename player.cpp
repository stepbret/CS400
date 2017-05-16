#include "netcode/clientlink.h"
#include "screens/screens.hpp"
#include "engine/engine.hpp"
#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <chrono>
#include <ncurses.h>
#include <panel.h>

// Game vars
pthread_mutex_t xcoord;
int coord_x = 0;

pthread_mutex_t ycoord;
int coord_y = 0;

pthread_mutex_t paus;
int paused = 1;

pthread_mutex_t movemnt;
char movement = 's';

pthread_mutex_t gameOver;
bool gameover = false;

pthread_mutex_t shooting;
int shoot = 0;

//Flags for screens
pthread_mutex_t waitsc;
bool waitscr = false;

pthread_mutex_t menusc;
bool menuscr = true;

pthread_mutex_t discon;
bool disconn = false;

pthread_mutex_t gamescore;
int gmscore = 0;

std::string highScr;

int menu = 0;

int twoplayers = 0;

static int s_interrupted = 0;

int threadDone = false;

//Called when signal interrupt received
void signalHandler(int signum) {
	s_interrupted = 1;
        threadDone = true;
}

//Switches keyboard input to unbuffered for one char (need to remember where I borrowed this from
//-- was on stack overflow...)
char getChar() {
	char buf = 0;
	fd_set set;
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = 1000;
	int rv;
	FD_ZERO(&set);
	FD_SET(0, &set);
    
	struct termios old = {0};
	if (tcgetattr(0, &old) < 0) {
		perror("tcsetattr()");
	}
	old.c_lflag &= ~ICANON;
	old.c_lflag &= ~ECHO;
	old.c_cc[VMIN] = 1;
	old.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &old) < 0) {
		perror("tcsetattr ICANON");
	}
	rv = select(1, &set, NULL, NULL, &timeout);
	if (rv == -1)
		perror("select()");
	else if (rv == 1) {
		if (read(0, &buf, 1) < 0)
			perror("read()");
	}
	
	old.c_lflag |= ICANON;
	old.c_lflag |= ECHO;
	if (tcsetattr(0, TCSADRAIN, &old) < 0) {
		perror("tcsetattr ~ICANON");
	}
	return buf;
}
char checkInput() {
  halfdelay(1);
  char key = getch();
  switch(key){
    case 'w':
      return 'a';
    case 'l':
      return 'd';
    case 'a':
      return ' ';
    case 'p':
      return 'f';
    case 'q':
      return 'q';
    default:
      return 's';
  }
}
void* runLevel1(void * arg) {
	//set up conditions for ncurses
    initscr();		//start ncurses mode
    curs_set(0);	 	//make cursor invisible
    start_color();		//turn on ncurses color mode
    noecho();		//don't write keyboard input to screen
    
    Clientlink *link = ((Clientlink*)arg); //pointer to link sent by thread invocation

    /*********DEFINE COLOR PAIRS*********/
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_MAGENTA);
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_YELLOW, COLOR_BLACK);
    /*******END DEFINE COLOR PAIRS*******/
    
    int keypress = -1, keypress2, keypress3;	//variables for screens
    Screens *displayScr; //object that contains and mainpulates all menu screens
    //getScreen(0) ==> loading screen
    //getScreen(1) ==> main menu screen
    //getScreen(2) ==> tutorial screen
    //getScreen(3) ==> wait screen
    //getScreen(4) ==> start level screen
    //getScreen(5) ==> end level screen
    //getScreen(6) ==> game over screen
    //getScreen(7) ==> status bar
    displayScr = new Screens();
    
    //show loading screen:
    displayScr->displayScreen(displayScr->getScreen(0));
    //for load screen animation
    displayScr->animateBullet();
    displayScr->teardownScreen(displayScr->getScreen(0));//teardown loading screen
	
    //used for end level screen demo - not used in regular setup
    long endscores[] = {2000, 3500, 5000};
    std::string endtime[] = {"01:50", "02:05", "02:31"};

      //display menu screen
      
      displayScr->displayScreen(displayScr->getScreen(1));
      while(keypress != 'p')
      { 
        keypress = (displayScr->getScreen(1))->keyListen();
        switch(keypress) {
        case 'q':
        case 'Q':
              std::cout << "Q was pressed...\n";
              endwin();
              threadDone = true;
              s_interrupted = 1;
              break;
        case 't':
        case 'T':
              displayScr->teardownScreen(displayScr->getScreen(1));
              displayScr->displayScreen(displayScr->getScreen(2));	//show tutorial screen
              menu = 2;
              do {
                      keypress2 = (displayScr->getScreen(2))->keyListen();
              } while (keypress2 < 0);
              displayScr->teardownScreen(displayScr->getScreen(2));
              displayScr->displayScreen(displayScr->getScreen(1));
              menu = 0;
              break;
        case 'p':
        case 'P':
              displayScr->teardownScreen(displayScr->getScreen(1));
              paused = 1;
              int connect = 0;
              link->modPacket('c');
              if (twoplayers == 0) {
                displayScr->displayScreen(displayScr->getScreen(3));
                //keypress3 = (displayScr->getScreen(3))->keyListen();
                int continueloop = 1;
                while (continueloop == 1) {
                //wait for 2 players connected
                  if (link->getClientStatus() == 3) {
                    connect = 1;
                    continueloop = 0;
                  //} else if (keypress3 == 'Q' || keypress3 == 'q') {
                    //continueloop = 0;
                  }
                }
                displayScr->teardownScreen(displayScr->getScreen(3));
                if (connect == 1) {
                  break;
                } else {
                  displayScr->displayScreen(displayScr->getScreen(1));
                  keypress = ' ';
                }
              }

            
              break;
        }
      }
    
      int minutes=0; //for score
      int seconds=0; //for score

      std::string levels[3];
      levels[0] = "engine/1level.txt";
      levels[1] = "engine/2level.txt";
      levels[2] = "engine/3level.txt";

      Engine game(60, 100);
  /********************************************************
  * for start and end level screen demo - start and end	*
  * level screens should sandwich game screen; all should *
  * be encapsulated in while loop that cycles through 	*
  * levels						*
  ********************************************************/
      //display start level screen
      bool collide = false;
      bool endOfLevel = false;
      int level = 0;
      double time[] = {0.100, 0.080, 0.050};
      int shootTest = 1;
      while(!collide && level < 3)
      {
        endOfLevel = false;
        (displayScr->getStartScreen())->setLevel(level+1);
        displayScr->displayScreen(displayScr->getScreen(4));
        usleep(5000000);
        displayScr->teardownScreen(displayScr->getScreen(4));
      
        // Load level and lock coords to set the proper place 
        game.load(level);
        pthread_mutex_lock(&xcoord);
        coord_x = game.setxCoord();
        pthread_mutex_unlock(&xcoord);
        pthread_mutex_lock(&ycoord);
        coord_y = game.setyCoord();
        pthread_mutex_unlock(&ycoord);

        displayScr->displayScreen(displayScr->getScreen(7));//show status bar
        int tick = 1;
        while(!collide && !endOfLevel)
        {
          if(paused == 1)
          {
            using namespace std::chrono;
            std::ifstream fp(levels[level]);
            steady_clock::time_point startTime = steady_clock::now();
            while(!collide && !endOfLevel)
            {
              // Lock the coords so that there isn't an overflow
              pthread_mutex_lock(&xcoord);
              pthread_mutex_lock(&ycoord);
              game.getCoords(coord_x, coord_y);
              pthread_mutex_unlock(&xcoord);
              pthread_mutex_unlock(&ycoord);
              pthread_mutex_lock(&shooting);
              game.getShoot(shoot);
              pthread_mutex_unlock(&shooting);
            
              //game gametime
              minutes = int(gmscore/60);
              seconds = int(gmscore%60);
            
              // get the current time and set ticks for game
              steady_clock::time_point currentTime = steady_clock::now();
              duration<double> time_span = duration_cast<duration<double>>(currentTime - startTime);
              if(time_span.count() >= time[level])
              {
                // update the objects in the game
                game.updateObjs(level);
                //update status bar
                (displayScr->getStatusBar())->setScore(gmscore);
                (displayScr->getStatusBar())->setLevelMinutes(minutes);
                (displayScr->getStatusBar())->setLevelSeconds(seconds);
                (displayScr->getScreen(7))->setupWindow();
                (displayScr->getScreen(7))->updatePanels();
                tick++;
                collide = game.detectPlayerCollisions();
                game.detectMissleCollisions();

                // get the next obstacles
                if(tick % 20 == 0)
                {
                  endOfLevel = game.getObs(fp);
                  game.setScenery(level);
                }

                //if we get a gameover from the server, set collide to true
                pthread_mutex_lock(&gameOver);
                if(gameover)
                {
                  collide = true;
                }
                pthread_mutex_unlock(&gameOver);
         
                // Pause the game if there is a collision lock paused
                if(collide)
                {
                  pthread_mutex_lock(&gameOver);
                  gameover = true;
                  pthread_mutex_unlock(&gameOver);
                  pthread_mutex_lock(&paus);
                  paused = 0;
                  pthread_mutex_unlock(&paus);
                }
                // get the new time
                startTime = steady_clock::now();
              }
              pthread_mutex_lock(&movemnt);
              movement = checkInput();
              pthread_mutex_unlock(&movemnt);
              refresh();
            }
          }
          if(!collide)
          {
            //Tear down game level
            game.endLevel(level);
            refresh();
  
            //display end level screen
            (displayScr->getEndLevelScreen())->setLevel(level+1);
            (displayScr->getEndLevelScreen())->setScore(gmscore);
            (displayScr->getEndLevelScreen())->setLevelMinutes(minutes);
            (displayScr->getEndLevelScreen())->setLevelSeconds(seconds);
            displayScr->displayScreen(displayScr->getScreen(5));
            usleep(5000000);
            displayScr->teardownScreen(displayScr->getScreen(5));
            level++;
          }
	}
      }
      if(collide)
      {
        //Tear down game graphics 
        game.endLevel(level);

        //set up game over screen (collision)
        (displayScr->getGameOverWin())->setDead(1);
        (displayScr->getGameOverWin())->setHighScore(0);
        displayScr->displayScreen(displayScr->getScreen(6));
          (displayScr->getGameOverWin())->setHighScoreList(highScr);
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(2));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(3));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(4));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(5));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(6));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(7));
        (displayScr->getScreen(6))->updatePanels();
        usleep(5000000);
        displayScr->teardownScreen(displayScr->getScreen(6));
        threadDone = true;
      }
      else
      {
        //Tear down the game graphics
        game.endLevel(level);
        doupdate();
        refresh();

      /******************************************************
       * this should be in its own else if(highScore) block *
       * (will set up later): shows when player reaches end *
       *  of game and has high score        *
       * ***************************************************/
	(displayScr->getGameOverWin())->setDead(0);
        (displayScr->getGameOverWin())->setScore(gmscore);
        (displayScr->getGameOverWin())->setHighScore(1);
  	(displayScr->getGameOverWin())->setHighScoreList(highScr);
        displayScr->displayScreen(displayScr->getScreen(6));
        displayScr->animateFireworks();
        displayScr->teardownScreen(displayScr->getScreen(6));
      /******************************************************
       * this should be in the last/default else block will *
       * set up later): shows when player reahces end of    *
       * game but doesn't have high score       *
       *****************************************************/
        (displayScr->getGameOverWin())->setDead(0);
	(displayScr->getGameOverWin())->setHighScoreList(highScr);
        (displayScr->getGameOverWin())->setScore(gmscore);
        (displayScr->getGameOverWin())->setHighScore(0);
        displayScr->displayScreen(displayScr->getScreen(6));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(2));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(3));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(4));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(5));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(6));
        (displayScr->getScreen(6))->hidePanel((displayScr->getScreen(6))->getPanel(7));
        (displayScr->getScreen(6))->updatePanels();
        usleep(2000000);
        displayScr->teardownScreen(displayScr->getScreen(6));
        threadDone = true;
      }
  delete displayScr;
  endwin();
}

//This is the status function that is passed to the status thread. It continually checks for changes
//to the status of the game. In my humble opinion, this is where calls to the various menu objects
//should be made. Ideally, they'd be presented on top of the gameplay display frame that is always
//displayed in the background.
void * checkStatus(void * data) {
    

	Clientlink *link = ((Clientlink*)data); //pointer to link sent by thread invocation
	int connect_qual = 0; //connection quality
	struct timespec now;
	int clientstatus = 0;
	int prevstatus = 0; //for detecting changes on each loop iteration
	int prevConnected = 0; //for detecting changes on each loop iteration
	int z = 1;

	int x;
	int y;
  	int score;

  	FILE *fp;
  	fp = fopen("nwlog.txt", "w");

    
	//std::cout << "UDP socket initialized -- hit 'c' to connect ( or ctrl-x to terminate)...\n";
    

	//while SIGINT hasn't been detected
	while (s_interrupted == 0) {	
    		clock_gettime(CLOCK_REALTIME, &now); //current time in 'timespec' form
    		pthread_mutex_lock(&gameOver);
    		bool tempGO = gameover;
    		pthread_mutex_unlock(&gameOver);
    		if (tempGO) {
      			highScr = link->readScores();
      			link->setGameover(true);
	    		link->shut_down(); //ends send/receive loops and closes socket
	    		return 0; //ends status thread
    		}
		//check if game over
		if (link->getGameover()) {
			highScr = link->readScores();
			pthread_mutex_lock(&gameOver);
			gameover = true;
			pthread_mutex_unlock(&gameOver);
			link->shut_down(); //ends send/receive loops and closes socket
			return 0; //ends status thread
		}
		//if client connected to server (received packet from server)
	  	if (link->getConnected() == 1) {
      			prevConnected = 1; //for next iteration

			//check server status
			if (connect_qual == 2 && now.tv_sec - link->getLastReceived()->tv_sec > z) {
				//had full connection quality with a new delay since last packet
				fprintf(fp, "\nWarning: No packet from server in %i seconds\n", z);
				connect_qual = 1; //poor connection quality
				z++;
				if (z > 10) {
					//10 seconds since packet received from server
					fprintf(fp,"\nError: Server packet timeout -- shutting down\n");
					link->shut_down(); //ends send/receive loops and closes socket
					return 0;
				}
			} else {
				if (connect_qual == 0 && now.tv_sec - link->getLastReceived()->tv_sec < 3) {
					//had no connection quality and recently received packet from server
					connect_qual = 2; //now fully connected

				} else if (connect_qual == 1 && now.tv_sec - link->getLastReceived()->tv_sec < 1) {
					//had poor connection quality and recently received packet from server
					connect_qual = 2; //now fully connected
				}
			}
            
            
			//check client status (sent from server)
			clientstatus = link->getClientStatus();
			switch (clientstatus) {        
				case 0: //no clients connected
					if (prevstatus != 0) {
						/* doesn't make sense, since a packet was just received (meaning a client is
						connected) */
						perror("Packet issue/conflict -- this shouldn't happen");
						link->shut_down();
						return 0;
					}
					break;

				case 1: //one client connected
					if (prevstatus == 2) {
						/* had one client connected, one experiancing difficulty. Now just have one
						client. */
						prevstatus = 1; //now only one client
						break;
					} else if (prevstatus == 3) {
						/* had two clients connected, now just have one client. Implies other player
						quit, but not due to timeout. */
						prevstatus = 1; //now only one client
					} else if (prevstatus == 0) {
						/* had no clients, now have one client (implies this one) */
						pthread_mutex_lock(&waitsc);
						waitscr = true;
						pthread_mutex_unlock(&waitsc);
						menu = 3;
						prevstatus = 1; //now only one client
					} else {
						/* status hasn't changed, check if player wants to stop waiting */	
						pthread_mutex_lock(&waitsc);
						waitscr = false;
						pthread_mutex_unlock(&waitsc);
						//link->modPacket('q');
						//usleep(10000); //wait for disconnect packet to reach server
					}
					break;

				case 2: /* one client connected, one client experiencing difficulty (delay in
					 packets received at server) */
					if (prevstatus == 3) {
						//had two clients, now one is late in sending packets, pause the game
						pthread_mutex_lock(&paus);
						paused = 1;
						pthread_mutex_unlock(&paus);
						prevstatus = 2; //now one player connected, one having trouble
					}
					break;

				case 3: //two clients fully connected
					twoplayers = 1;
					if (prevstatus == 2) {
						//had one client connected, one with delay in received packet at server
						pthread_mutex_lock(&paus);
						paused = 0;
						pthread_mutex_unlock(&paus);
						prevstatus = 3; //now two clients connected
						break;
					} else if (prevstatus == 1 || prevstatus == 0) {
						prevstatus = 3; //now two clients connected
						break;
					} 
					//no issues, both players remain fully connected
					//Deal with shooting
					pthread_mutex_lock(&shooting);
					shoot = link->getShoot();
					pthread_mutex_unlock(&shooting);

					//deal with coordinates
					x = link->getX();
					y = link->getY();
					pthread_mutex_lock(&xcoord);
					pthread_mutex_lock(&ycoord);
					if (x != coord_x || y != coord_y) {
						coord_x = x;
						coord_y = y;
					}
					pthread_mutex_unlock(&xcoord);
					pthread_mutex_unlock(&ycoord);

					//get game score from server
					score = int(link->getScore());
					pthread_mutex_lock(&gamescore);
					if (score != gmscore){
						gmscore = score;
					}
					pthread_mutex_unlock(&gamescore);

					//link->modPacket(getChar());
					break;
			}
		} else if (prevConnected == 1) {
			//not currently connected but was previously connected
			prevConnected = 0; //no longer connected
			connect_qual = 0; //no connection quality
			pthread_mutex_lock(&discon);
			disconn = true;
			pthread_mutex_unlock(&discon);
		} else {
			//not connected and wasn't connected previously
			//get char

			//return value from keypress (wait for input)
			menuscr = true;
			menu = 1;
			//link->modPacket('c');
			usleep(5000); //wait for packet to reach server

		}
	}
}

/* Very simple main function (as it should be). I expect we need to add an ncurses graphics/display
 thread which is passed arguments by the status thread. */
int main(int argc, char* argv[]) {
    
    
	if (argc < 4) {
		// not enough arguments
		std::cerr << "Usage: " << argv[0] << " <local port> <server ip> <server port>";
		return 0;
	}
    

	// Create the locks
	pthread_mutex_init(&xcoord,NULL);
	pthread_mutex_init(&ycoord,NULL);
	pthread_mutex_init(&paus,NULL);
	pthread_mutex_init(&waitsc,NULL);
	pthread_mutex_init(&menusc,NULL);
	pthread_mutex_init(&discon,NULL);
	pthread_mutex_init(&movemnt, NULL);
	pthread_mutex_init(&gameOver, NULL);
	pthread_mutex_init(&gamescore, NULL);



	Clientlink link = Clientlink(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));

	pthread_t threads[3];
	pthread_create(&threads[0], NULL, &Clientlink::send_helper, &link); //Send thread
	pthread_create(&threads[1], NULL, &Clientlink::recv_helper, &link); //Recv thread
	pthread_create(&threads[2], NULL, &checkStatus, &link); //Status thread
    
	/******************************************************************
	*                      Setup gamethread
	* ***************************************************************/

	pthread_t gp;
	pthread_create(&gp, NULL, &runLevel1, &link);

	signal(SIGINT, signalHandler);

	int prevConnected = 0;

	while (link.getShutdown() == 0) {
	    pthread_mutex_lock(&movemnt);
	    link.modPacket(movement);
	    pthread_mutex_unlock(&movemnt);
	    usleep(10000);
	    if (s_interrupted == 1) {
	        addstr("Interrupt detected, shutting down...");
	        refresh();
	        link.shut_down(); //kills both threads and closes socket
	        //kills status thread by terminating while loop
	        break;
	    }
	usleep(1000); //give threads time to send/recv
	}

	while(!threadDone){}
	endwin();

	//destroy the mutexs
	pthread_mutex_destroy(&xcoord);
	pthread_mutex_destroy(&ycoord);
	pthread_mutex_destroy(&paus);
	pthread_mutex_destroy(&waitsc);
	pthread_mutex_destroy(&menusc);
	pthread_mutex_destroy(&discon);
	pthread_mutex_destroy(&movemnt);
	pthread_mutex_destroy(&gameOver);
	pthread_mutex_destroy(&gamescore);
	link.printHighscores();
} 
