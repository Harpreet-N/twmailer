#include "MailClient.h"

int main(int argc, char *argv[]) {

    if (argc != 3) {
        perror("Error");
        return 1;
    }

    // We get the ip and port
    char ipString[255] = {'\0'};
    strcpy(ipString, argv[1]);
    int port = atoi(argv[2]);

    MailClient client;
    if (!client.start(ipString, port)) {
        perror("start client");
        return EXIT_FAILURE;
    }

    client.connectServer();
    return EXIT_SUCCESS;
}
