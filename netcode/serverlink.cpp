#include "serverlink.h"
#include "udpsocket.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
#include <vector>

//Constructor
Serverlink::Serverlink(int localport) {
	socket = UDPsocket(localport);
	shutdown = 0;
	c1.playerNum = 1;
	c1.alive = 0;
	c2.playerNum = 2;
	c2.alive = 0;
	jumpcounter = 0;
	jumpflag = false;
	shootcounter = 0;
	shootflag = false;
	listen_timer = 0;


}

//https://gist.github.com/diabloneo/9619917
void timespec_diff(struct timespec *start, struct timespec *stop,
                   struct timespec *result)
{
    if ((stop->tv_nsec - start->tv_nsec) < 0) {
        result->tv_sec = stop->tv_sec - start->tv_sec - 1;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec + 1000000000;
    } else {
        result->tv_sec = stop->tv_sec - start->tv_sec;
        result->tv_nsec = stop->tv_nsec - start->tv_nsec;
    }

    return;
}

void Serverlink::resumeScore() {
	struct timespec * now = spacket.getHack();
	clock_gettime(CLOCK_REALTIME, (now));
	std::cout << "\nStarted clock\n";
}

void Serverlink::pauseScore() {
	struct timespec stop = (struct timespec){0};
	clock_gettime(CLOCK_REALTIME, &(stop));
	struct timespec * start = spacket.getHack();
	struct timespec result = (struct timespec){0};
	timespec_diff(start, &stop, &result);
	spacket.setScore(spacket.getScore() + static_cast<long int>(result.tv_sec));
	std::cout << "Stopped clock: score is " << spacket.getScore() << "\n\n";
}

void Serverlink::updateScore() {
	struct timespec stop = (struct timespec){0};
	clock_gettime(CLOCK_REALTIME, &(stop));
	struct timespec * start = spacket.getHack();
	struct timespec result = (struct timespec){0};
	timespec_diff(start, &stop, &result);
	spacket.setScore(spacket.getScore() + static_cast<long int>(result.tv_sec));
}



//Sends current spacket to c1, c2 or both if they are 'alive'.
void* Serverlink::sendloop(void) {
	int bytessent = 0;
	
	while(shutdown != 1) {
		
		if (spacket.getClientStatus() == 3) {
			updateScore();
		}

		if (c1.alive) {
			spacket.setLastReceived(&(c1.lastreceived));
			spacket.setSent();
			bytessent = socket.sendpacket(&spacket, sizeof(spacket), &c1.addr);
		}

		if (c2.alive) {
			spacket.setLastReceived(&(c2.lastreceived));
			spacket.setSent();
			bytessent = socket.sendpacket(&spacket, sizeof(spacket), &c2.addr);
		}
		usleep(1000); //1000 microseconds
	}
	return 0;
}

/* Dummy function to update stored coords based on input from received Clientpacket. This is where
	Brett's server side code would go. **Change 1: Brett is keeping gameplay code on client side***/
void Serverlink::processPacket(Client * client, Clientpacket * newb) {

	int num = client->playerNum;
	if (num == 2) {
		if (jumpcounter > 0 && jumpflag) {
			jumpcounter--;
			//std::cout << jumpcounter << std::endl;
		} else if (jumpcounter == 0 && jumpflag) {
			spacket.decY();
			jumpflag = false;
		} else if (newb->getJump()) {	
			std::cout << "Client #" << num << ": Jump\n";
			jumpcounter = 4000;
			spacket.incY();
			jumpflag = true;
		}

		if (jumpcounter > 0 && jumpflag) {
			jumpcounter--;
			//std::cout << jumpcounter << std::endl;
		} else if (jumpcounter == 0 && jumpflag) {
			spacket.decY();
			jumpflag = false;
		} else if (newb->getJump()) {	
			std::cout << "Client #" << num << ": Jump\n";
			jumpcounter = 1000;
			spacket.incY();
			jumpflag = true;
		}
	

		if (shootcounter > 0 && shootflag) {
			shootcounter--;
			//std::cout << shootcounter << std::endl;
		} else if (shootcounter == 0 && shootflag) {
			spacket.setShoot(false);
			shootflag = false;
		} else if (newb->getShoot()) {	
			std::cout << "Client #" << num << ": Shoot\n";
			shootcounter = 200;			
			spacket.setShoot(true);
			shootflag = true;
		}
	} else {
	

		if (newb->getForwards()) {
			std::cout << "Client #" << num << ": Forwards\n";
			spacket.incX();
		}
		if (newb->getBackwards()) {
			std::cout << "Client #" << num << ": Backwards\n";
			spacket.decX();
		}
	}

	if (newb->getGameover()) {
		wait = 10000;
		setGameover();
	}

	if (newb->getConnect() == 0) {
		std::cout << "Client #" << num << " has terminated connection...\n";
		client->alive = 0;
		switch (spacket.getClientStatus()) {
			case 0:
				//shouldn't happen, there was at least one connection
				break;
			case 1:
				spacket.setClientStatus(0); //had 1 player connected, now have none
				break;
			case 2:
				spacket.setClientStatus(0); //had 1 player connected, one trying. Connected one quit.
				break;
			case 3:
				spacket.setClientStatus(1); //Had 2 players, now have one
				pauseScore();
				break;
		}
	}
}

/* Continuously listen for packets from clients. Due to the nature of having multiple clients, status
	updates need to occur in here as opposed to within the servermain.cpp file. Since there are no
	graphical display components on the server side, this should be no problem */
void* Serverlink::recvloop(void) {
	int bytesreceived = 0;
	char str[INET_ADDRSTRLEN]; //stores address in string format
	struct timespec now;
	int y = 1;
	int z = 1;

	while(shutdown != 1) {
		bytesreceived = socket.recvpacket(&cpacket, sizeof(cpacket), &addr); //blocks for packet
		if (wait == 0) {

			inet_ntop(AF_INET, &(addr.sin_addr), str, INET_ADDRSTRLEN); //convert address to string

			int cstatus; //client status
			
			if (bytesreceived > 0) {
				cstatus = spacket.getClientStatus(); //grabs current client status stored at server
				
				
				if (addr.sin_addr.s_addr == c1.addr.sin_addr.s_addr && addr.sin_port == c1.addr.sin_port) {
					//packet received from previously connected c1

					clock_gettime(CLOCK_REALTIME, &(c1.lastreceived)); //set lastreceived to current time
					processPacket(&c1, &cpacket); 	//process input from client
					c1.packet = cpacket; 			//update packet to latest from client
					//memcpy(&(c1.addr), &addr, sizeof(addr));

					if (c1.alive == 0 && c1.packet.getConnect() > 0 && cpacket.getGameover() == false) {
						//client was dropped but has re-attempted connection
						
						printf("\nClient 1 (%s) re-connected from : %s:%i\n", c1.packet.getUsername(), str, ntohs(addr.sin_port));
						//std::cout << "Client 1 (" << c1.packet.getUsername() << ") re-connected from: " << str << ":" << ntohs(addr.sin_port) << "\n";
						
						if (cstatus > 0) {
							//a client was connected
							spacket.setClientStatus(3); //now both clients connected
							resumeScore();
						
						} else {
							//no clients were connected
							spacket.setClientStatus(1); //now one client connected
						}
						c1.alive = 1;
					}
					
				} else if (addr.sin_addr.s_addr == c2.addr.sin_addr.s_addr && addr.sin_port == c2.addr.sin_port) {
					//packet received from previously connected c2

					clock_gettime(CLOCK_REALTIME, &(c2.lastreceived)); //set lastreceived to current time
					processPacket(&c2, &cpacket); 	//process input from client
					c2.packet = cpacket;			//update packet to latest from client
					//memcpy(&c2.addr, &addr, sizeof(addr));
				
					if (c2.alive == 0 && c2.packet.getConnect() > 0 && cpacket.getGameover() == false) {
						//client was dropped but has re-attempted connection
						
						printf("\nClient 2 (%s) re-connected from : %s:%i\n", c2.packet.getUsername(), str, ntohs(addr.sin_port));
						//std::cout << "Client 2 (" << c2.packet.getUsername() << ") re-connected from: " << str << ":" << ntohs(addr.sin_port) << "\n";
						
						if (cstatus > 0) {
							//a client was connected
							spacket.setClientStatus(3); //now both clients connected
							resumeScore();
						} else {
							//no clients were connected
							spacket.setClientStatus(1); //now one client connected
						}
						c2.alive = 1;
					}
				
				
				} else {
					//packet received from new client
					
					if (c1.alive == 0 && cpacket.getConnect() == 1 && cpacket.getGameover() == false) { 
						//open c1 position
						
						clock_gettime(CLOCK_REALTIME, &(c1.lastreceived));
						c1.packet = cpacket;
						memcpy(&(c1.addr), &addr, sizeof(addr)); //storing new address/port
						
						printf("\nClient 1 (%s) connected from : %s:%i\n", c1.packet.getUsername(), str, ntohs(addr.sin_port));
						//std::cout << "Client 1 (" << c1.packet.getUsername() << ") connected from: " << str << ":" << ntohs(addr.sin_port) << "\n";
						
						if (cstatus > 0) {
							//c2 is connected
							spacket.setClientStatus(3); //now both clients connected
							resumeScore();
						} else {
							//no clients were connected
							spacket.setClientStatus(1); //now one client connected
						}
						c1.alive = 1;

					} else if (c2.alive == 0 && cpacket.getConnect() == 1 && cpacket.getGameover() == false) {
						//c1 already occupied, open c2 position

						clock_gettime(CLOCK_REALTIME, &(c2.lastreceived));
						c2.packet = cpacket;
						memcpy(&c2.addr, &addr, sizeof(addr)); //storing new address/port
						
						printf("\nClient 2 (%s) connected from : %s:%i\n", c2.packet.getUsername(), str, ntohs(addr.sin_port));
						//std::cout << "Client 2 (" << c2.packet.getUsername() << ") connected from: " << str << ":" << ntohs(addr.sin_port) << "\n";
						resumeScore();
						spacket.setClientStatus(3); //now both clients are connected
						c2.alive = 1;
					
					} else {
						//no open positions, discard packet
					}
				}
			/*	
			} else if (listen_timer > 0) {
				listen_timer--;
				std::cout << "Listen_timer: " << listen_timer << std::endl;
			}
			*/
			}
			
			//Updating status of clients
			clock_gettime(CLOCK_REALTIME, &now);
			if (c1.alive && now.tv_sec - c1.lastreceived.tv_sec > y) {
				//c1 is late in sending their packet
				if (c2.alive) {
					spacket.setClientStatus(2); //now 2 clients connected but one is having connection problems
				} else {
					spacket.setClientStatus(0); //now 0 clients fully connected
				}
				std::cout << "\nHaven't received packet from c1 in " << y << " secs...\n";
				y++;
				if (y > 10) {
					std::cout << "\nNo response from c1 in 10 secs, c1 is dropped!\n";
					if (c2.alive) {
						spacket.setClientStatus(1); //now 1 client fully connected
					} else {
						spacket.setClientStatus(0); //now 0 clients fully connected
					}

					c1.alive = 0;
					y = 1;
				}
			}
			if (c2.alive && now.tv_sec - c2.lastreceived.tv_sec > z) {
				//c2 is late in sending their packet
				if (c1.alive) {
					spacket.setClientStatus(2); //now 2 clients connected but one is having connection problems
				} else {
					spacket.setClientStatus(0); //now 0 clients fully connected
				}
				std::cout << "\nHaven't received packet from c2 in " << z << " secs...\n";
				z++;
				if (z > 10) {
					std::cout << "\nNo response from c2 in 10 secs, c2 is dropped!\n";
					if (c1.alive) {
						spacket.setClientStatus(1); //now 1 client fully connected
					} else {
						spacket.setClientStatus(0); //now 0 clients fully connected
					}
					c2.alive = 0;
					z = 1;
				}
			}
		} else {
			wait--;
		} 
	}
	return 0;
}

int Serverlink::getClientStatus() {
	return spacket.getClientStatus();
}

int Serverlink::getX() {
	return spacket.getX();
}

int Serverlink::getY() {
	return spacket.getY();
}

void Serverlink::setGameover() {
	
	pauseScore();
	updateScores();
	writeScores();
	
	spacket.setGameover(true);
	usleep(10000);
	reset();
	std::cout << "\n** Game Over ** -- Link reset, socket remains open for new clients/new game...\n\n";
}

void Serverlink::updateScores() {
	//bubble sort

	std::cout << "Current score = " << spacket.getScore() << "\n";

	if (highscores.size() == 0) { //no high scores
		Score new_score;
		strcpy((new_score.u1), c1.packet.getUsername());
		strcpy((new_score.u2), c2.packet.getUsername());
		new_score.score = spacket.getScore();
		highscores.insert(highscores.begin(), new_score);
	} else { //at least one high score
		int x = highscores.size();
		for (int i = 0; i < x; i++) {
			std::cout << "Score " << i+1 << ": " << highscores.at(i).score << "\n";
			if (spacket.getScore() > highscores.at(i).score) {
				std::cout << "Score greater than high score " << i+1 << ": Updating score " << i+1 << "\n";
				Score new_score;
				strcpy((new_score.u1), c1.packet.getUsername());
				strcpy((new_score.u2), c2.packet.getUsername());
				new_score.score = spacket.getScore();
				highscores.insert(highscores.begin() + i, new_score);
				if (i > 4) {
					highscores.pop_back();
					i = i+1;
				}
				spacket.setHighscores(&highscores);
				printHighscores();
				spacket.setScore(0);
				return;
			}
			
		}
		if (highscores.size() < 5) {
			Score new_score;
			strcpy((new_score.u1), c1.packet.getUsername());
			strcpy((new_score.u2), c2.packet.getUsername());
			new_score.score = spacket.getScore();
			highscores.insert(highscores.end(), new_score);

			
		}
		
	}
	spacket.setHighscores(&highscores);
	printHighscores();
	spacket.setScore(0); 
}

void Serverlink::reset() {
	c1 = Client();
	c2 = Client();
	c1.playerNum = 1;
	c1.alive = 0;
	c2.playerNum = 2;
	c2.alive = 0;
	spacket = Serverpacket();
	spacket.setGameover(false);
}


void Serverlink::shut_down() {
	shutdown = 1;
	usleep(1000);
	socket.closesocket();
}

void Serverlink::printHighscores() {
	std::cout << "\n***** High Scores *****\n";
	for (int i = 0; i < 5; i++) {
		Score * score = spacket.getScore(i);
		if (score->score > 0) {
			printf("%i. %s %s %i\n", i+1, score->u1, score->u2, score->score);
		}
	}

	
}

//http://stackoverflow.com/questions/3811328/try-to-write-char-to-a-text-file
void Serverlink::writeScores() {
	std::ofstream stream;
    
    stream.open("serverscores.txt", std::ofstream::out | std::ofstream::trunc);
    std::cout << std::endl;
    if( !stream )
        std::cout << "\nOpening file failed\n" << std::endl;
    // use operator<< for clarity
    for (int i = 0; i < 5; i++) {
		Score * score = spacket.getScore(i);
		if (score->score > 0) {
			std::cout << "Writing score " << i+1 << "\n";
			stream << i+1 << ". " << score->u1 << " " << score->u2 << " " << score->score << "\n";
		}
	}

    // test if write was succesful - not *really* necessary
    if( !stream )
        std::cout << "\nWrite failed\n" << std::endl;
    stream.close();

}

void Serverlink::readScores() {
	std::ifstream ifs("serverscores.txt");
	
	char line[100];
	char l_char[100];
	int begin = 0;
	int end = 0;
	int position = 0;

	Score score;
	std::vector<Score> scorevector;

	int count = 0;
	memset(line, 0, sizeof(line));
	if (ifs.is_open()) {
		std::cout << "\nOpening serverscores.txt\n";
		if (ifs.good()) {
			std::cout << "Open successful\n";
		}
		while(ifs.getline(line, 99)) {
			if (line[0] != 0) {
				//std::cout << "Reading line " << count << std::endl;
				//std::cout << line << std::endl;
				//std::cout << ifs.fail();
				for (int i = 3; i < 50; i++) {
					//std::cout << i << " " << begin << " " << end << " " << line[i] << std::endl;
					if (line[i] != '\n' && line[i] != ' ' && begin == 0) {
						begin = i;
					} else if ((line[i] == ' ' || line[i] == '\n' || line[i] == 0 || line[i] == '\r') && begin != 0) {
						end = i;
						if (position == 0) {
							memset(score.u1, 0, sizeof(score.u1));
							memcpy(score.u1, line + begin, end - begin);
							//std::cout << score.u1 << std::endl;
							position = 1;
							begin = 0;
							end = 0;
						} else if (position == 1) {
							memset(score.u2, 0, sizeof(score.u2));
							memcpy(score.u2, line + begin, end - begin);
							//std::cout << score.u2 << std::endl;
							position = 2;
							begin = 0;
							end = 0;
						} else {
							memcpy(l_char, line + begin, end - begin);
							//std::cout << l_char << std::endl;
							score.score = strtol (l_char, NULL, 10);
							memset(l_char, 0, sizeof(l_char));
							position = 0;
							scorevector.push_back(score);
							memset(line, 0, sizeof(line));
							count++;
							begin = 0;
							end = 0;
							break;
						}
					}
				}
			}
		}
	} else {
		std::cout << "\nCouldn't open serverscores.txt\n";
	}
	spacket.setHighscores(&scorevector);
	highscores = scorevector;
	printHighscores();
}

