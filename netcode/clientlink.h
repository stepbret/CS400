#ifndef CLIENTLINK_H
#define CLIENTLINK_H

#include "udpsocket.h"
#include "serverpacket.h"
#include "clientpacket.h"
#include <iostream>
#include <string>

class Clientlink {
	UDPsocket socket;
	
	Serverpacket old_spacket;
	Serverpacket spacket;
	Clientpacket cpacket;
	std::string username;
	int connected;
	bool gameover;
	struct sockaddr_in addr; //server address
	int shutdown;
	long int currentscore;

	public:
		Clientlink(char* username, int localport, std::string remoteaddr, int remoteport);

		void* sendloop(void);
		void* recvloop(void);

		//http://stackoverflow.com/questions/1151582/pthread-function-from-a-class
		static void *send_helper(void *context) {
			return ((Clientlink*)context)->sendloop();
		}
		static void *recv_helper(void *context) {
			return ((Clientlink*)context)->recvloop();
		}
		struct timespec * getLastReceived();
		void modPacket(char c);
		bool getGameover();
		void setGameover(bool go);
		void resetPacket();
		void processPacket();
		void connect();
		int getConnected();
		int getClientStatus();
		void shut_down();
		int getShutdown();
		void printHighscores();
		void writeScores();
		std::string readScores();
		int getX();
		int getY();
		int getForwards();
		int getBackwards();
		int getJump();
		int getShoot();
		int getScore();
};
#endif
