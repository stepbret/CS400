#ifndef SERVERPACKET_H
#define SERVERPACKET_H

#include <vector>

struct Score {
	char u1[10];
	char u2[10];
	long int score;
	Score() {
		score = 0;
	}
};

class Serverpacket {
	int x;
	int y;

	bool forwards;
	bool backwards;
	bool jump;
	bool shoot;

	int clientstatus; 	//status of clients 
						//0 == 0 clients fully connected
						//1 == 1 client fully connected 
						//2 == 2 clients connected but one is having connection problems
						//3 == 2 clients fully connected
	struct timespec lastreceived; //time last clientpacket (from destination client) received at server 
	struct timespec sent;		//time this packet sent to clients
	struct timespec hack;
	long int score;
	Score highscores[5];
	bool gameover;
	public:
		Serverpacket();
		void incX();
		void decX();
		void incY();
		void decY();
		int getX();
		int getY();
		void setForwards(bool f);
		bool getForwards();
		void setBackwards(bool b);
		bool getBackwards();
		void setJump(bool j);
		bool getJump();
		void setShoot(bool s);
		bool getShoot();
		void setGameover(bool go);
		bool getGameover();
		void setClientStatus(int x);
		int getClientStatus();
		void setLastReceived(struct timespec *);
		struct timespec * getLastReceived();
		struct timespec * getHack();
		void setHack(struct timespec *);
		void setSent();
		int getScore();
		void setScore(long int score);
		void setHighscores (std::vector<Score> * scores);
		Score * getScore(int i);
};

#endif