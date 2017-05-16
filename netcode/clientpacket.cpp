#include <sys/time.h>
#include <iostream>
#include "clientpacket.h"
#include <stdio.h>
#include <string.h>

Clientpacket::Clientpacket() {
	jump = false;
	shoot = false;
	forwards = false;
	backwards = false;
	connect = 0;
	lastreceived = (struct timespec){0};
	sent = (struct timespec){0};
}


void Clientpacket::setForwards(bool f) {
	forwards = f;
}

void Clientpacket::setBackwards(bool b) {
	backwards = b;
}

void Clientpacket::setJump(bool j) {
	jump = j;
}

void Clientpacket::setShoot(bool s) {
	shoot = s;
}

bool Clientpacket::getForwards() {
	return forwards;
}

bool Clientpacket::getBackwards() {
	return backwards;
}

bool Clientpacket::getJump() {
	return jump;
}

bool Clientpacket::getShoot() {
	return shoot;
}

void Clientpacket::setConnect(int connect) {
	this->connect = connect;
}

int Clientpacket::getConnect() {
	return connect;
}

void Clientpacket::setGameover(bool go) {
	gameover = go;
}

bool Clientpacket::getGameover() {
	return gameover;
}

void Clientpacket::setLastReceived() {
	if(clock_gettime(CLOCK_REALTIME, &lastreceived) < 0)
		perror("Couldn't update client packet time (last received)");
}

void Clientpacket::setSent() {
	if(clock_gettime(CLOCK_REALTIME, &sent) < 0)
		perror("Couldn't update client packet time (sent)");
}

void Clientpacket::reset() {
	forwards = false;
	backwards = false;
	jump = false;
	shoot = false;
}

char* Clientpacket::getUsername() {
	return username;
}

void Clientpacket::setUsername(char * name) {
	strcpy(username, name);
}