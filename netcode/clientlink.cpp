#include "clientlink.h"
#include "udpsocket.h"
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <time.h>

/* Constructor */
Clientlink::Clientlink(char* username, int localport, std::string remoteaddr, int remoteport) {
	cpacket.setUsername(username);
	socket = UDPsocket(localport);
	socket.setRemoteAddr(remoteaddr, remoteport);
	inet_pton(AF_INET, remoteaddr.c_str(), &(addr.sin_addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(remoteport);
	connected = 0;
	shutdown = 0;
	gameover = false;
	currentscore = 0;
}

//Creates loop that continuously sends cpacket to stored server address
void* Clientlink::sendloop(void) {
	int bytessent = 0;

	//while no sigint received by calling client application
	while(shutdown != 1) {
		cpacket.setSent();
		//std::cout << "\nSize of cpacket: " << sizeof(cpacket) << "\n";
		
		//connection terminated by player
		if (cpacket.getConnect() == 0 && connected == 1) {
			bytessent = socket.sendpacket(&cpacket, sizeof(cpacket), &addr);
			connected = 0;
		
		//connection either already established or player has initiated connection
		} else if (connected == 1 || cpacket.getConnect() == 1) {
			bytessent = socket.sendpacket(&cpacket, sizeof(cpacket), &addr);
		} 

		cpacket.reset(); //default state is 0's for all keyboard input

		//std::cout << "Sent " << bytessent << " bytes to server\n";
		
		std::cout.flush(); //cout is not thread safe
		usleep(1000); //Reducing computation
	}
	return 0;
}

//Dummy function that prints updated coordinates, if they have changed
void Clientlink::processPacket() {
	cpacket.setLastReceived();
	if (spacket.getX() != old_spacket.getX() || spacket.getY() != old_spacket.getY()) {
		//std::cout << spacket.getX() << ", " << spacket.getY() << "\n";	
	}


	if (spacket.getGameover()) {
		cpacket.setConnect(0);
		connected = 0;
		gameover = true;
	}
	currentscore = spacket.getScore();
}

int Clientlink::getX() {
	return spacket.getX();
}

int Clientlink::getY() {
	return spacket.getY();
}

//Creates loop that continuously receives spacket
void* Clientlink::recvloop(void) {
	int bytesreceived = 0;

	//while no sigint received by main calling application
	while(shutdown != 1) {

		bytesreceived = socket.recvpacket(&spacket, sizeof(spacket), &addr);
		if (bytesreceived > 0) {
			
			//connection established (assume bytes received are from server for now...)
			if (connected == 0 && cpacket.getConnect() == 1) {
				connected = 1;
			}
			processPacket();
			old_spacket = spacket;
		}

		/*
		if (bytesreceived > 0) {
			std::cout << "Received " << bytesreceived << " bytes from server\n";
			std::cout.flush();
		}
		*/
	}
	return 0;
}

//Modifies current packet action variables based on char input by user
void Clientlink::modPacket(char c) {
	
	if(c == ' ') {
		cpacket.setJump(true);
		return;
	} 
	if (c == 'f') {
		cpacket.setShoot(true);
		return;
	} 
	if (c == 'a') {
		cpacket.setBackwards(true);
		return;
	} 
	if (c == 'd') {
		cpacket.setForwards(true);
		return;
	}
	if (c == 'q') {
		cpacket.setConnect(0);
		return;
	}
	if (c == 'c') {
		connect();
		return;
	} 

	//all other chars not recognized	
}

struct timespec * Clientlink::getLastReceived() {
	return spacket.getLastReceived();
}

int Clientlink::getClientStatus() {
	return spacket.getClientStatus();
}

int Clientlink::getConnected() {
	return connected;
}

bool Clientlink::getGameover() {
	return gameover;
}

void Clientlink::setGameover(bool go) {
	cpacket.setGameover(go);
	usleep(1000);
	gameover = true;
}

void Clientlink::connect() {
	cpacket.setConnect(1);
}

//Set client packet action variables to 0
void Clientlink::resetPacket() {
	cpacket.reset();
}

//http://stackoverflow.com/questions/3811328/try-to-write-char-to-a-text-file
void Clientlink::writeScores() {
	std::ofstream stream;
    
    stream.open("highscores.txt", std::ofstream::out | std::ofstream::trunc);
    if( !stream )
        std::cout << "Opening file failed" << std::endl;
    // use operator<< for clarity
    for (int i = 0; i < 5; i++) {
		Score * score = spacket.getScore(i);
		if (score->score > 0) {
			stream << i << ". " << score->u1 << " " << score->u2 << " " << score->score << std::endl;
		}
	}

    // test if write was succesful - not *really* necessary
    if( !stream )
        std::cout << "Write failed" << std::endl;
    stream.close();

}

std::string Clientlink::readScores() {
	std::ifstream ifs("highscores.txt");
	std::string content;
	content.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	return content;
}

//close socket and stop threaded send/recv loops
void Clientlink::shut_down() {
	
	writeScores();
	connected = 0;
	shutdown = 1;
	socket.closesocket();
}

int Clientlink::getShutdown() {
	return shutdown;
}

int Clientlink::getForwards() {
	return spacket.getForwards();
}

int Clientlink::getBackwards() {
	return spacket.getBackwards();
}

int Clientlink::getJump() {
	return spacket.getJump();
}

int Clientlink::getShoot() {
	return spacket.getShoot();
}

int Clientlink::getScore() {
	return currentscore;
}

void Clientlink::printHighscores() {
	std::cout << "***** High Scores *****\n";
	for (int i = 0; i < 5; i++) {
		Score * score = spacket.getScore(i);
		if (score->score > 0) {
			printf("%i. %s %s %i\n", i+1, score->u1, score->u2, score->score);
		}
	}
}