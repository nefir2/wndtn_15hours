#include <limits>
#include "client.h"

using namespace ObjectModel;

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

		if (message == "max" || message == "min") {
			Primitive* p;
			if (message == "max") p = Primitive::create("int32", Type::I32, std::numeric_limits<int32_t>::max()); 
			else p = Primitive::create("int32", Type::I32, std::numeric_limits<int32_t>::min()); 
			std::vector<int8_t> result(p->getSize());
			int16_t it = 0;
			p->pack(&result, &it);
			std::copy(result.begin(), result.end(), buffer);
			
			if ((sendto(clientsocket, buffer, p->getSize(), 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR) {
				printf("send() failed... error code: %d\n", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
		}
		else {
			if ((sendto(clientsocket, message.c_str(), message.size(), 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR) {
				printf("send() failed... error code: %d\n", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
		}
	}

	void Client::receive() {
		if ((recvlength = recvfrom(clientsocket, buffer, SIZE, 0, (struct sockaddr*)&info, &infolength)) == SOCKET_ERROR) {
			printf("recv() failed... error code: %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Client::process() {
		printf("packet from: %s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		if (buffer[0] == 0x1) {
			std::vector<int8_t> result;
			for (unsigned i = 0; i < (unsigned)recvlength; i++) result.push_back(buffer[i]);
			Primitive p = Primitive::unpack(result);
			
			printf("Primitive:\n");
			printf("\t |Name:'%s'\n", p.getName().c_str());
			printf("\t |Size:'%d'\n", p.getSize());
			printf("\t |Data:");
			for (auto d : p.getData()) printf("[%d]", d);
		}
		else {
			printf("data: ");
			for (unsigned i = 0; i < recvlength; i++) printf("%c", buffer[i]);
		}
		printf("\n");
	}

	Client::~Client() {
		WSACleanup();
		closesocket(clientsocket);
	}
} // namespace Net
