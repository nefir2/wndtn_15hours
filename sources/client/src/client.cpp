#include "client.h"

namespace Net
{
	Client::Client(int port, std::string ipaddress) : wsa{ 0 }, port(port), ipaddress(ipaddress), clientsocket(INVALID_SOCKET), info{ 0 }, infolength(sizeof(info)) {}

	void Client::init() {
		info.sin_family = AF_INET; //ip version (ipv4)
		info.sin_port = htons(port); //htons - host to netowk, short; big/litle endians for port
		info.sin_addr.s_addr = inet_addr(ipaddress.c_str()); //ip address

		printf("WSA init\n");
		assert(!(WSAStartup(MAKEWORD(2, 2), &wsa)) && "couldn't init wsa"); //MAKEWORD(2, 2) same as MAKEWORD(514)
		printf("WSA SUCCESS\n");

		printf("Creating socket\n");
		assert(!((clientsocket = socket(info.sin_family, SOCK_DGRAM, 0)) == SOCKET_ERROR) && "couldn't create socket"); //in original he is repeated AF_INET
		printf("Success!\n");
	}

	void Client::connect() {
		init();

		for (;;) {
			send();
			receive();
			process();
		}
	}

	void Client::send() { 
		printf("Enter a message: ");
		std::getline(std::cin, message);


		if ((sendto(clientsocket, message.c_str(), message.size(), 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR) {
			printf("send() failed... error code: \n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Client::receive() {
		if ((recvlength = recvfrom(clientsocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR) {
			printf("recv() failed... error code: \n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Client::process() {
		printf("packet from: %s:%d", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		for (unsigned i = 0; i < recvlength; i++) {
			printf("%c", buffer[i]);
		}
	}

	Client::~Client() {
		WSACleanup();
		closesocket(clientsocket);
	}
} // namespace Net
