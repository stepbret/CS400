#include "serverlink.h"
#include <iostream>
#include <csignal>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


static int s_interrupted = 0;

void signalHandler(int signum) {
	s_interrupted = 1;
}

/*
void checkGameOver(Serverlink * link) {

	int x = link->getX(); //gets latest x
	int y = link->getY(); //gets latest y

	if (x == 5 && y == 5) {
		link->setGameover();
		usleep(100000);
		link->reset();
		std::cout << "\nGame Over\n";
		std::cout << "\nLink reset, socket remains open for new clients/new game...\n\n";
	}

}
*/

int main(int argc, char* argv[]) {

	if (argc < 2) {
		//not enough args
		std::cerr << "Usage: " << argv[0] << " <local port>";
		return 0;
	}

	Serverlink *link = new Serverlink(atoi(argv[1]));

	link->readScores();

	signal(SIGINT, signalHandler);

	pthread_t threads[2];
	pthread_create(&threads[0], NULL, &Serverlink::send_helper, link); //send thread
	pthread_create(&threads[1], NULL, &Serverlink::recv_helper, link); //receive thread

	std::cout << "\nUDP socket initiated -- <ctrl-C> to terminate...\n";
	std::cout.flush();

	while (true) {
		if (s_interrupted == 1) {
			std::cout << "Interrupt detected, shutting down...";
			link->shut_down();
			break;
		}
		//checkGameOver(link);

	}

	usleep(1000);
}