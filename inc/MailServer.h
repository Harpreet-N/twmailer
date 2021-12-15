#ifndef __MAILSERVER_H
#define __MAILSERVER_H

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
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "FileIO.h"

#define BUF 1024
#define MSGSIZE 11

class MailServer
{
	private:
	int create_socket = -1;
	bool abortRequested = false;
	socklen_t addrlen;
	struct sockaddr_in address, cliaddress;
	int new_socket = -1;
    int port;
    FileIO* fileIO;
	void clientCommunication(int* parameterSocket);
	void sendAnswer(int* socket, std::string);
    std::vector<std::string> splitMsg(std::string);
	
	public:
	MailServer();
    ~MailServer();
    void setDir(std::string);
    void setPort(int);
	bool start();
	void listenForClients();
    void abort();
	
};

#endif