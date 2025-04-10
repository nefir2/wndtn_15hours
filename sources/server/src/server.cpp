#include "server.h"

namespace Net
{
	Server::Server(int port, std::string ipaddress) : wsa{ 0 }, port(port), ipaddress(ipaddress), serversocket(INVALID_SOCKET), info{ 0 }, infolength(sizeof(info)) {}

	void Server::init() {
		info.sin_family = AF_INET; //ip version (ipv4)
		info.sin_port = htons(port); //htons - host to netowk, short; big/litle endians for port
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str()); //ip address

		printf("WSA init\n");
		assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "couldn't init wsa"); //MAKEWORD(2, 2) same as MAKEWORD(514)
		printf("WSA SUCCESS\n");

		printf("Creating socket\n");
		assert(!((serversocket = socket(info.sin_family, SOCK_DGRAM, 0)) == SOCKET_ERROR) && "couldn't create socket"); //in original he is repeated AF_INET
		printf("Success!\n");

		printf("bind socket\n");
		int32_t bindval = bind(serversocket, (struct sockaddr*)&info, infolength);
		printf("bind value: %d\n", bindval);
		assert(!bindval && "couldn't bind socket");
		printf("socket binded\n");

		printf("server started at: %s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
	}

	void Server::start() {
		init();

		for (;;) {
			receive();
			process();
			send();
		}
	}

	void Server::receive() {
		if ((recvlength = recvfrom(serversocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR) {
			printf("recv() failed... error code: \n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Server::process() {
		printf("packet from: %s:%d\npacket buffer: '", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < recvlength; i++) printf("%c", buffer[i]);
		printf("'\n");
	}

	void Server::send() { 
		if ((sendto(serversocket, buffer, recvlength, 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR) {
			printf("send() failed... error code: \n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	Server::~Server() {
		WSACleanup();
		closesocket(serversocket);
	}
} // namespace Net
