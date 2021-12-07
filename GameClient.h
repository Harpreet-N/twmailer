#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "GameState.h"

#define BUF 1024
#define PORT 6543

class GameClient
{
	private:
	GameState gameState;
	int create_socket;
	char buffer[BUF];
	struct sockaddr_in address;
	int size;
	
	public:
	GameClient();
	bool start(char*,int);
	void connectServer();
};

#endif
