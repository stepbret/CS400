#include <time.h>
#include "serverpacket.h"
#include <stdio.h>


Serverpacket::Serverpacket() {
	x = 0;
	y = 42;
	lastreceived = (struct timespec){0};
	sent = (struct timespec){0};
	hack = (struct timespec){0};
	clientstatus = 0;
	score = 0;
	forwards = false;
	backwards = false;
	jump = false;
	shoot = false;

}

void Serverpacket::incX() {
	this->x = x+1;
}

void Serverpacket::decX() {
	this->x = x-1;
}

void Serverpacket::incY() {
	this->y = y-10;
}

void Serverpacket::decY() {
	this->y = y+10;
}

int Serverpacket::getX() {
	return x;
}

int Serverpacket::getY() {
	return y;
}

void Serverpacket::setForwards(bool f) {
	forwards = f;
}

bool Serverpacket::getForwards() {
	return forwards;
}

void Serverpacket::setBackwards(bool b) {
	backwards = b;
}

bool Serverpacket::getBackwards() {
	return backwards;
}

void Serverpacket::setJump(bool j) {
	jump = j;
}

bool Serverpacket::getJump() {
	return jump;
}

void Serverpacket::setShoot(bool s) {
	shoot = s;
}

bool Serverpacket::getShoot() {
	return shoot;
}


void Serverpacket::setGameover(bool go) {
	gameover = go;
}

bool Serverpacket::getGameover() {
	return gameover;
}

void Serverpacket::setClientStatus(int x) {
	clientstatus = x;
}

int Serverpacket::getClientStatus() {
	return clientstatus;
}

void Serverpacket::setLastReceived(struct timespec * lr) {
	lastreceived = *lr;
}

struct timespec * Serverpacket::getLastReceived() {
	return &lastreceived;
}

void Serverpacket::setSent() {
	if(clock_gettime(CLOCK_REALTIME, &sent) < 0)
		perror("Couldn't update server packet time sent");
}

void Serverpacket::setHack(struct timespec * ts) {
	hack = *ts;
}

struct timespec * Serverpacket::getHack() {
	return &hack;
}

int Serverpacket::getScore() {
	return score;
}

void Serverpacket::setScore(long int s) {
	score = s;
}

void Serverpacket::setHighscores(std::vector<Score> * scores) {
	for (int i = 0; i < scores->size(); i++) {
		highscores[i] = scores->at(i);
	}
}

Score * Serverpacket::getScore(int i) {
	return &(highscores[i]);
}