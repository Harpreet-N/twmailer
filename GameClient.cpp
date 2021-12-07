#include "GameClient.h"

GameClient::GameClient() {}

bool GameClient::start(char *ip, int port) {
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket error");
        return false;
    }

    // Ip und port übergeben
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_aton(ip, &address.sin_addr);

    return true;
}

void GameClient::connectServer() {
    if (connect(create_socket, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("Connect error - no server available");
        exit(EXIT_FAILURE);
    }

    printf("Connection with server (%s) established\n",
           inet_ntoa(address.sin_addr));

    do {
        size = recv(create_socket, buffer, BUF - 1, 0);
        if (size == -1) {
            perror("recv error");
            break;
        } else if (size == 0) {
            printf("Server closed remote socket\n");
            break;
        } else {
            // Hier dann Mail usw
            gameState.setState(buffer);

            printf("\n What do you want to send? >> ");
            if (fgets(buffer, BUF, stdin) != NULL) {
                int bufferSize = strlen(buffer);
                // remove new-line signs from string at the end
                if (buffer[bufferSize - 2] == '\r' && buffer[bufferSize - 1] == '\n') {
                    bufferSize -= 2;
                    buffer[size] = 0;
                } else if (buffer[bufferSize - 1] == '\n') {
                    --bufferSize;
                    buffer[bufferSize] = 0;
                }
                if (strcmp(buffer, "quit") == 0)
                    break;

                // SEND DATA
                if ((send(create_socket, buffer, bufferSize, 0)) == -1) {
                    perror("send error");
                    break;
                }
            }
        }
    } while (1);

    if (create_socket != -1) {
        if (shutdown(create_socket, SHUT_RDWR) == -1) {
            perror("shutdown create_socket");
        }
        if (close(create_socket) == -1) {
            perror("close create_socket");
        }
        create_socket = -1;
    }
}
