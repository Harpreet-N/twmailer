#include <iostream>
#include "GameServer.h"

void signalHandler(int);
GameServer server;

int main(int argc, char *argv[])
{
	
	/*if (argc != 3)
	{
		perror("Error");
		return 1;
	} 

	char directoryString[255] = {'\0'};
	strcpy(directoryString, argv[2]); */

	int port = atoi(argv[1]);

	printf("%d\n", port);

	if (signal(SIGINT, signalHandler) == SIG_ERR)
	{
		perror("signal can not be registered");
		return EXIT_FAILURE;
	}

	if(!server.start(port))
	{
		perror("start server");
		return EXIT_FAILURE;
	}
	server.listenForClients();
	
	return 0;
}

void signalHandler(int sig)
{
	if (sig == SIGINT)
	{
		printf("abort Requested... ");
		server.abort();
	}
}
