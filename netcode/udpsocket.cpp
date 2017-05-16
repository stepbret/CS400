#include <sys/socket.h>
#include "udpsocket.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <netinet/in.h>

UDPsocket::UDPsocket() {
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("cannot create local socket");
	}
	memset((char *)&localaddr, 0, sizeof(localaddr)); //zeroize localaddr
	memset((char *)&remoteaddr, 0, sizeof(remoteaddr)); //zeroize remoteaddr
	remoteaddr.sin_family = AF_INET;
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(50000);
	if (bind(s, (struct sockaddr *)&localaddr, sizeof(localaddr)) < 0) {
		perror("binding of local socket failed");
	}

	if (fcntl(s, F_SETFL, O_NONBLOCK, 1) == -1) {
		perror("failed to set non-blocking");
	}
}

//create socket, bind it
UDPsocket::UDPsocket(int localport) {
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
		perror("cannot create local socket");
	}
	memset((char *)&localaddr, 0, sizeof(localaddr)); //zeroize localaddr
	memset((char *)&remoteaddr, 0, sizeof(remoteaddr)); //zeroize remoteaddr
	remoteaddr.sin_family = AF_INET;
	localaddr.sin_family = AF_INET;
	localaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localaddr.sin_port = htons(localport);
	if (bind(s, (struct sockaddr *)&localaddr, sizeof(localaddr)) < 0) {
		perror("binding of local socket failed");
	}

	if (fcntl(s, F_SETFL, O_NONBLOCK, 1) == -1) {
		perror("failed to set non-blocking");
	}

}

void UDPsocket::setRemoteAddr(std::string addr, int port) {
	inet_pton(AF_INET, addr.c_str(), &(remoteaddr.sin_addr));
	remoteaddr.sin_port = htons(port);
}

int UDPsocket::sendpacket(void* buffer, int size, struct sockaddr_in * addr) {
	socklen_t addr_len = sizeof(remoteaddr);
	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(addr->sin_addr), str, INET_ADDRSTRLEN);

	//std::cout << "Sending packet to " << str << ":" << ntohs(addr->sin_port) << "\n";
	//std::cout.flush();
	int sent_bytes = sendto(s, buffer, size, 0, (sockaddr*)addr, addr_len);
	if (sent_bytes != size) {
		perror("failed to completely send packet\n");
		return 0;
	}
	return sent_bytes;
}

int UDPsocket::recvpacket(void* buffer, int size, void* addr) {
	sockaddr_in from;
	socklen_t addr_len = sizeof(from);

	char str[INET_ADDRSTRLEN];
	inet_ntop(AF_INET, &(localaddr.sin_addr), str, INET_ADDRSTRLEN);

	//std::cout << "Listening on " << str << ":" << ntohs(localaddr.sin_port) << "\n";
	//std::cout.flush();

	int recv_bytes = recvfrom(s, buffer, size, 0, (sockaddr*)&from, &addr_len);
	if (recv_bytes <= 0) {
		//perror("nothing received");
		return 0;
	}

	
	//set remoteaddr to address that sent packet
	memcpy(addr, &from, addr_len);

	return recv_bytes;
}

void UDPsocket::closesocket() {
	close(s);
}
