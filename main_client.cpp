#include <iostream>
#include <MailClient.h>

int main(int argc, char** argv)
{
	//primitive Fehlerbehandlung möglich, da Reihenfolge der parameter vorgegeben war
    if (argc != 3)
	{
		perror("Error\n");
        printf("Use: ./twmailer-client <ip> <port>\n");
		return 1;
	}

    std::string ipAddrress(argv[1]);

	int port = atoi(argv[2]);

    MailClient client(ipAddrress,port);
	if(!client.start())
	{
		perror("start client");
		return EXIT_FAILURE;
	}
	
	client.connectServer();
	
	return EXIT_SUCCESS;
}