#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <thread>
#include <cstddef>
#include "MailState.h"
#include <iostream>
#include <vector>

#define BUF 1024
#define PORT 6543
#define MSGSIZE 11

class GameServer
{
	private:
	MailState mailState;
	int create_socket = -1;
	bool abortRequested = false;
	socklen_t addrlen;
	struct sockaddr_in address, cliaddress;
	int new_socket = -1;
	
	public:
	GameServer();
	bool start(int);
	void listenForClients(std::string);
	void abort();
	void clientCommunication(int* parameterSocket, std::string);
	void sendGameState(int* socket);
};

#endif
