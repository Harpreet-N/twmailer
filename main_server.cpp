#include <iostream>
#include "MailServer.h"

void signalHandler(int);
//hier leider global, da signalhanler keinen pointer zu server mit übernehemn kann
MailServer server = MailServer();

int main(int argc, char **argv)
{
    //primitive Fehlerbehandlung möglich, da Reihenfolge der parameter vorgegeben war
    if (argc != 3)
	{
        perror("Error\n");
		printf("Use: ./twmailer-server <port> <mail-spool-directoryname>\n");
		return 1;
	}

    std::string mailDir(argv[2]);

	int port = atoi(argv[1]);

    server.setDir(mailDir);
    server.setPort(port);
   
    if (signal(SIGINT, signalHandler) == SIG_ERR)
    {
        perror("signal can not be registered");
        return EXIT_FAILURE;
    }

    if (!server.start())
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
