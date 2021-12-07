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
#include "GameState.h"
#include <iostream>

#define BUF 1024
#define PORT 6543
#define MSGSIZE 11

class GameServer
{
	private:
	GameState gameState;
	int create_socket = -1;
	bool abortRequested = false;
	socklen_t addrlen;
	struct sockaddr_in address, cliaddress;
	int new_socket = -1;
	
	public:
	GameServer();
	bool start(int);
	void listenForClients();
	void abort();
	void clientCommunication(int* parameterSocket);
	void sendGameState(int* socket);
};

#endif
