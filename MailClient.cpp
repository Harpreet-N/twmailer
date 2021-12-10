#include "MailClient.h"

MailClient::MailClient() {}

bool MailClient::start(char *ip, int port) {
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket error");
        return false;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(port);
    inet_aton(ip, &address.sin_addr);

    return true;
}

std::string readInput();

void MailClient::connectServer() {
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
            mailState.setState(buffer);

            printf("\n What do you want to send? >> ");
            if (fgets(buffer, BUF, stdin) != NULL) {
                std::vector<std::string> stringVector;
                std::ostringstream output;

                char bufferChar[255] = {'\0'};
                std::string bufferString = strcpy(bufferChar, buffer);

                do{
                    std::getline(std::cin, bufferString);
                    stringVector.push_back(bufferString);
                } while (bufferString.at(0) != '.');

                for(std::string line : stringVector){
                    output << line << std::endl;
                }

                int bufferSize = bufferString.size();

                // SEND DATA

                std::string sendData = output.str();
                const char * c = sendData.c_str();

                if ((send(create_socket, c, bufferSize, 0)) == -1) {
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
