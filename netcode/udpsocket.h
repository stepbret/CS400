#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

//creates socket and 2 addresses -- local and remote
class UDPsocket {
	struct sockaddr_in localaddr;
	struct sockaddr_in remoteaddr;
	int s;
	public:
		//local port
		UDPsocket();
		UDPsocket(int localport);
		void setRemoteAddr(std::string, int);
		int sendpacket(void*, int size, struct sockaddr_in *);
		int recvpacket(void*, int size, void*);
		void closesocket();
};

#endif