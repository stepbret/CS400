#ifndef CLIENTPACKET_H
#define CLIENTPACKET_H

#include <sys/time.h>

class Clientpacket {
	char username[10];
	bool forwards;
	bool backwards;
	bool jump;
	bool shoot;
	int connect;
	bool gameover;
	struct timespec lastreceived;
	struct timespec sent;
	public:
		Clientpacket();
		void setForwards(bool f);
		void setBackwards(bool b);
		void setJump(bool j);
		void setShoot(bool s);
		bool getForwards();
		bool getBackwards();
		bool getJump();
		bool getShoot();
		bool getGameover();
		void setGameover(bool go);
		void setSent();
		void setLastReceived();
		void setConnect(int);
		int getConnect();
		void reset();
		char* getUsername();
		void setUsername(char* name);
};

#endif