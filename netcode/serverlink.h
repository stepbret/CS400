#ifndef SERVERLINK_H
#define SERVERLINK_H

#include "udpsocket.h"
#include "serverpacket.h"
#include "clientpacket.h"
#include <iostream>
#include <time.h>
#include <vector>

struct Client {
	int playerNum;
	int alive;
	Clientpacket packet;
	struct timespec lastreceived;
	struct sockaddr_in addr;
};

class Serverlink {
	UDPsocket socket;
	//char* sendbuffer;
	//char* recvbuffer;
	int shutdown;
	Serverpacket spacket;
	Client c1;
	Client c2;
	std::vector<Score> highscores;
	struct sockaddr_in addr;
	Clientpacket cpacket;
	int jumpcounter;
	bool jumpflag;
	int shootcounter;
	bool shootflag;
	int listen_timer;
	int wait;

	public:
		Serverlink(int localport);

		void* sendloop(void);
		void* recvloop(void);

		void processPacket(Client * client, Clientpacket * newb);

		//http://stackoverflow.com/questions/1151582/pthread-function-from-a-class
		static void *send_helper(void *context) {
			return ((Serverlink*)context)->sendloop();
		}
		static void *recv_helper(void *context) {
			return ((Serverlink*)context)->recvloop();
		}
		int getX();
		int getY();

		int getClientStatus();
		void setGameover();

		//char* getbuffer();
		void reset();
		void shut_down();
		void resumeScore();
		void pauseScore();
		void updateScores();
		void updateScore();
		void printHighscores();
		void writeScores();
		void readScores();
};
#endif
