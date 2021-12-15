#ifndef __MAILCLIENT_H
#define __MAILCLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>  

#define BUF 1024

class MailClient
{
	private:
	int create_socket;
	char buffer[BUF];
	struct sockaddr_in address;
	int size;
    int port;
	std::string ipAddress;
    std::vector<std::string> readUserInput();
	
	public:
	MailClient(std::string ip, int port);
    ~MailClient();
	bool start();
	void connectServer();
};

#endif
