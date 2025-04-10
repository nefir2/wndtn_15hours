#pragma once
#include <cassert>
#include <iostream>
#include <thread>
#include <unordered_map>
#include <vector>
#include <string>
#include <winsock2.h>
#include "serialization.h"

// #pragma comment(lib, "Ws2_32.lib") //ненужно, если не в Visual studio

#define SIZE 1024

namespace Net
{
	class Client {
	private:
		WSADATA wsa;
		SOCKET clientsocket;
		std::string ipaddress;
		int port;
		char buffer[SIZE];
		std::string message;
		struct sockaddr_in info;
		int infolength;
		int recvlength;
	public:
		Client(int, std::string);
		~Client();
	public:
		void connect();
	private:
		void init();
		void receive();
		void process();
		void send();
	};
}