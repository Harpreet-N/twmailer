#include "MailClient.h"

MailClient::MailClient(std::string ip, int port)
{
    this->port = port;
    this->ipAddress = ip;
}

MailClient::~MailClient()
{
}

bool MailClient::start()
{
    //erstellt Socket File descriptor
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket error");
        return false;
    }

    //Werte mit 0 initialiseren
    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(this->port);
    inet_aton(this->ipAddress.c_str(), &address.sin_addr);

    return true;
}

void MailClient::connectServer()
{
    //erstellt Verbindung zu ip adresse
    if (connect(create_socket, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("Connect error - no server available");
        exit(EXIT_FAILURE);
    }

    printf("Connection with server (%s) established\n", inet_ntoa(address.sin_addr));

    do
    {
        std::ostringstream msg;

        //buffer mit \0 initialisieren, vermeiden von alten Werten
        for(int i = 0; i < BUF; i++)
        {
            buffer[i] = '\0';
        }

        //Daten von Server empfangen - auch indikator für start
        size = recv(create_socket, buffer, BUF - 1, 0);
        if (size == -1)
        {
            perror("recv error");
            break;
        }
        else if (size == 0)
        {
            printf("Server closed remote socket\n");
            break;
        }
        else
        {
            //hier ist die verbindung erfolgreich und die User interaktion findet statt
            system("clear");

            printf("\n%s", buffer);

            printf("\n(Enter Command) >> ");

            std::vector<std::string> userInput = this->readUserInput();

            if (0 < userInput.size() && "QUIT" == userInput[0])
            {
                break;
            }

            for (std::string line : userInput)
            {
                msg << line << std::endl;
            }

            //sende input an Server
            if ((send(create_socket, msg.str().c_str(), msg.str().size(), 0)) == -1)
            {
                perror("send error");
                break;
            }
        }
    } while (1);

    if (create_socket != -1)
    {
        //wenn socket fehler, dann socket verbindungen verbieten und beenden
        if (shutdown(create_socket, SHUT_RDWR) == -1)
        {
            perror("shutdown create_socket");
        }
        if (close(create_socket) == -1)
        {
            perror("close create_socket");
        }
        create_socket = -1;
    }
}

std::vector<std::string> MailClient::readUserInput()
{
    std::vector<std::string> stringVector;
    std::string input;

    //input lesen und in Vector schreiben für auswertung, muss vor senden also in einen String gewandelt werden
    do
    {
        std::getline(std::cin, input);
        stringVector.push_back(input);
    } while ((stringVector[0] == "SEND" && input.at(0) != '.') ||
             (stringVector[0] == "LIST" && stringVector.size() < 2) ||
             (stringVector[0] == "READ" && stringVector.size() < 3) ||
             (stringVector[0] == "DEL" && stringVector.size() < 3) ||
             (stringVector[0] == "QUIT" && stringVector.size() < 1) ||
             (stringVector[0] == "SEND" && stringVector[0] == "LIST" && stringVector[0] == "READ" && stringVector[0] == "DEL" && stringVector[0] == "QUIT") );

    return stringVector;
}