#include "clientlink.h"
#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <termios.h>
#include <stdio.h>


static int s_interrupted = 0;

//Called when signal interrupt received
void signalHandler(int signum) {
	s_interrupted = 1;
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
	int x = 0;
	int y = 0;
	bool shoot = false;

	std::cout << "UDP socket initialized -- hit 'c' to connect ( or ctrl-x to terminate)...\n";

	//while SIGINT hasn't been detected
	while (s_interrupted == 0) {
		
		clock_gettime(CLOCK_REALTIME, &now); //current time in 'timespec' form

		//check if game over
		if (link->getGameover()) {
			std::cout << "\nGame Over!\n"; //replace with menu object displaying same message
			link->printHighscores();
			link->shut_down(); //ends send/receive loops and closes socket
			return 0; //ends status thread
		}

		//if client connected to server (received packet from server)
		if (link->getConnected() == 1) {
			prevConnected = 1; //for next iteration
			
			//check server status
			if (connect_qual == 2 && now.tv_sec - link->getLastReceived()->tv_sec > z) {
				//had full connection quality with a new delay since last packet
				std::cout << "\nWarning: No packet from server in " << z << " seconds\n";
				connect_qual = 1; //poor connection quality
				z++;
				if (z > 10) {
					//10 seconds since packet received from server
					std::cout <<"\nError: Server packet timeout -- shutting down\n";
					link->shut_down(); //ends send/receive loops and closes socket
					return 0;
				}
			} else {
				if (connect_qual == 0 && now.tv_sec - link->getLastReceived()->tv_sec < 3) {
					//had no connection quality and recently received packet from server
					std::cout << "\nConnection established!\n";
					std::cout << " - hit 'q' to disconnect (or ctrl-x to terminate)...\n";
					connect_qual = 2; //now fully connected
				
				} else if (connect_qual == 1 && now.tv_sec - link->getLastReceived()->tv_sec < 1) {
					//had poor connection quality and recently received packet from server
					std::cout << "\nConnection re-established!\n";
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
					}
					break;
				
				case 1: //one client connected
					if (prevstatus == 2) {
						/* had one client connected, one experiancing difficulty. Now just have one 
							client. */
						std::cout << "\nOther player was kicked for connection timeout -- wait for reconnect or ctrl-c to quit...\n";
						prevstatus = 1; //now only one client
						break;
					}
					if (prevstatus == 3) {
						/* had two clients connected, now just have one client. Implies other player 
							quit, but not due to timeout. */
						std::cout << "\nOther player terminated their connection. Wait for another player or ctrl-c to quit...\n";
						prevstatus = 1; //now only one client
					}
					if (prevstatus == 0) {
						/* had no clients, now have one client (implies this one) */
						std::cout << "\nConnected: Waiting for second player to connect\n";
						prevstatus = 1; //now only one client
					}
					break;
				
				case 2: /* one client connected, one client experiencing difficulty (delay in 
							packets received at server) */
					if (prevstatus == 3) {
						//had two clients, now one is late in sending packets
						std::cout << "\nGame paused: waiting on other player's connectivity\n";
						prevstatus = 2; //now one player connected, one having trouble
					}
					break;
				
				case 3: //two clients fully connected
					if (prevstatus == 2) {
						//had one client connected, one with delay in received packet at server
						std::cout << "\nResuming game: both players fully connected\n";
						prevstatus = 3; //now two clients connected
					}
					if (prevstatus < 2) {
						//had either one or no clients connected
						std::cout << "\nBoth players connected, begin playing!\n";
						std::cout << " - hit 'd' to move forwards\n";
						std::cout << " - hit 'a' to move backwards\n";
						std::cout << " - hit ' ' to jump\n";
						std::cout << " - hit 'f' to fire\n";
						prevstatus = 3; //now two clients connected
					}

					if (link->getX() != x || link->getY() != y) {
						x = link->getX();
						y = link->getY();
						printf("(%d, %d): %d\n", x, y, link->getScore());
					}
					if (link->getShoot()) {
						printf("Shoot\n");
						link->setGameover(true);
					}

					/*
					if (link->getForwards()) {
						std::cout << "Forwards\n";
					}
					if (link->getBackwards()) {
						std::cout << "Backwards\n";
					}
					if (link->getJump()) {
						std::cout << "Jump\n";
					}
					if (link->getShoot()) {
						std::cout << "Shoot\n";
					}
					*/
					break;
					//no issues, both players remain fully connected
			}
		} else if (prevConnected == 1) {
			//not currently connected but was previously connected
			prevConnected = 0; //no longer connected
			connect_qual = 0; //no connection quality
			std::cout << "Disconnected from server: hit 'c' to re-connect or ctrl-c to quit\n";
		}
	}
}

/* Very simple main function (as it should be). I expect we need to add an ncurses graphics/display 
	thread which is passed arguments by the status thread. */
int main(int argc, char* argv[]) {

	if (argc < 5) {
		// not enough arguments
		std::cerr << "Usage: " << argv[0] << " <local port> <server ip> <server port>";
		return 0;
	}

	Clientlink link = Clientlink(argv[1], atoi(argv[2]), argv[3], atoi(argv[4]));
	
	std::cout << link.readScores() << std::endl;

	pthread_t threads[3];
	pthread_create(&threads[0], NULL, &Clientlink::send_helper, &link); //Send thread
	pthread_create(&threads[1], NULL, &Clientlink::recv_helper, &link); //Recv thread
	pthread_create(&threads[2], NULL, &checkStatus, &link); //Status thread

	signal(SIGINT, signalHandler);
	
	int prevConnected = 0;

	while (link.getShutdown() == 0) {
		usleep(10000);
		if (s_interrupted == 1) {
			std::cout << "Interrupt detected, shutting down...";
			link.shut_down(); //kills both threads and closes socket
			//kills status thread by terminating while loop
			break;
		}


		link.modPacket(getChar()); //modify client packet from user input
		//std::cout.flush(); //due to cout not being threadsafe

	}

	usleep(1000); //give threads time to send/recv
}
