#include "server.h"

using namespace ObjectModel;

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
			printf("recv() failed... error code: %d\n", WSAGetLastError());
			exit(EXIT_FAILURE);
		}
	}

	void Server::process() {
		printf("packet from: %s:%d\n", inet_ntoa(info.sin_addr), ntohs(info.sin_port));
		if (buffer[0] == 0x1) {
			std::vector<int8_t> result;
			for (unsigned i = 0; i < (unsigned)recvlength; i++) result.push_back(buffer[i]);
			Primitive p = Primitive::unpack(result);
			primitives.insert(std::make_pair(p.getName(), p));
			current = p.getName();
			
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

	void Server::send() { 
		if (primitives.empty()) {
			if ((sendto(serversocket, buffer, recvlength, 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR) {
				printf("send() failed... error code: %d\n", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
		}
		else {
			int16_t it = 0;
			std::unique_ptr<Primitive> p = modify(current);
			std::vector<int8_t> result(p->getSize());
			p->pack(&result, &it);
			std::copy(result.begin(), result.end(), buffer);

			if ((sendto(serversocket, buffer, p->getSize(), 0, (struct sockaddr*)&info, infolength)) == SOCKET_ERROR) {
				printf("send() failed... error code: %d\n", WSAGetLastError());
				exit(EXIT_FAILURE);
			}
			primitives.erase(current);
		}
	}

	std::unique_ptr<Primitive> Server::modify(std::string key) {
		primitives.erase(key); //right ver: primitives.find(key)
		int16_t overtwentysix = 726;
		std::unique_ptr<Primitive> p(Primitive::create("int16", Type::I16, overtwentysix));
		primitives.insert(std::make_pair(p->getName(), *p));

		return p;
	}	

	Server::~Server() {
		WSACleanup();
		closesocket(serversocket);
	}
} // namespace Net
