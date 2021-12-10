#ifndef MAILCLIENT_H
#define MAILCLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "MailState.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#define BUF 1024
#define PORT 6543

class MailClient
{
	private:
	MailState mailState;
	int create_socket;
	char buffer[BUF];
	struct sockaddr_in address;
	int size;
	
	public:
    MailClient();
	bool start(char*,int);
	void connectServer();
};

#endif
