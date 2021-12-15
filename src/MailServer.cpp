#include "MailServer.h"

MailServer::MailServer()
{

}

MailServer::~MailServer()
{
    //speicher freigeben
    delete this->fileIO;
}

void MailServer::setDir(std::string dir)
{
    //rot dir für FileIO setzen
    this->fileIO = new FileIO(dir);
}

void MailServer::setPort(int port)
{
    this->port = port;
}

bool MailServer::start()
{
    int reuseValue = 1;

    //erstellt Socket File descriptor
    if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("Socket error");
        return false;
    }
    //setzt optionen: reuse address and port, reuseVaue = 1 => true
    if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEADDR, &reuseValue, sizeof(reuseValue)) == -1)
    {
        perror("set socket options - reuseAddr");
        return false;
    }
    if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEPORT, &reuseValue, sizeof(reuseValue)) == -1)
    {
        perror("set socket options - reusePort");
        return false;
    }

    memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;         //adress familiy ipv4
    address.sin_addr.s_addr = INADDR_ANY; // = 0
    address.sin_port = htons(this->port);

    //bindet adresse an socket
    if (bind(create_socket, (struct sockaddr *)&address, sizeof(address)) == -1)
    {
        perror("bind error");
        return false;
    }
    return true;
}

void MailServer::listenForClients()
{
    //setze socket zu liste => bereit für accept
    if (listen(create_socket, 5) == -1)
    {
        perror("listen error");
        return;
    }

    while (!abortRequested)
    {
        printf("Waiting for connections...\n");

        addrlen = sizeof(struct sockaddr_in);
        //konsumiert erste anfrage 
        if ((new_socket = accept(create_socket, (struct sockaddr *)&cliaddress, &addrlen)) == -1)
        {
            if (abortRequested)
            {
                perror("accept error after aborted");
            }
            else
            {
                perror("accept error");
            }
            break;
        }

        printf("Client connected from %s:%d...\n", inet_ntoa(cliaddress.sin_addr), ntohs(cliaddress.sin_port));

        //Hier Auswertung von Nachricht
        clientCommunication(&new_socket);
        new_socket = -1;
    }

    abort();
}

void MailServer::clientCommunication(int *current_socket)
{
    char buffer[BUF];
    int size;

    //sende Antwort, signalisiere Bereit
    sendAnswer(current_socket, "Ready");

    do
    {
        for (int i = 0; i < BUF; i++)
        {
            buffer[i] = '\0';
        }

        //empfange Server nachricht
        size = recv(*current_socket, buffer, BUF - 1, 0);
        if (size == -1)
        {
            if (abortRequested)
            {
                perror("recv error after aborted");
            }
            else
            {
                perror("recv error");
            }
            break;
        }
        else if (size == 0)
        {
            printf("Client closed remote socket\n");
            break;
        }

        printf("Message received: %s\n", buffer);

        //split c string in Vector mit std::string
        std::vector<std::string> msg = splitMsg(std::string(buffer));

        //Auswerten der Anfrage und setzten der aktionen sowie antworten senden
        if (msg[0] == "SEND")
        {
            if (fileIO->setUser(msg[2]))
            {
                this->fileIO->saveMsg(std::string(buffer), msg[3]);
                sendAnswer(current_socket, "OK\n");
                printf("test");
            }
            else
            {
                sendAnswer(current_socket, "ERR\n");
            }
        }
        else if (msg[0] == "LIST")
        {
            if (fileIO->setUser(msg[1]))
            {
                std::string answ = fileIO->readDirFiles();
                sendAnswer(current_socket, answ);
            }
            else
            {
                sendAnswer(current_socket, "0 Mails\n");
            }
        }
        else if (msg[0] == "READ")
        {
            if (fileIO->setUser(msg[1]))
            {
                std::string answ = fileIO->readMsg(std::stoi(msg[2]));
                sendAnswer(current_socket, "OK\n" + answ);
            }
            else
            {
                sendAnswer(current_socket, "ERR\n");
            }
        }
        else if (msg[0] == "DEL")
        {
            if (fileIO->setUser(msg[1]))
            {
                if (fileIO->delMsg(std::stoi(msg[2])))
                {
                    sendAnswer(current_socket, "OK\n");
                }
                else
                {
                    sendAnswer(current_socket, "ERR\n");
                }
            }
            else
            {
                sendAnswer(current_socket, "ERR\n");
            }
        }
        else
        {
            sendAnswer(current_socket, "ERR\n");
        }

    } while (!abortRequested);

    if (*current_socket != -1)
    {
        //wenn socket fehler, dann socket verbindungen verbieten und beenden
        if (shutdown(*current_socket, SHUT_RDWR) == -1)
        {
            perror("shutdown new_socket");
        }
        if (close(*current_socket) == -1)
        {
            perror("close new_socket");
        }
        *current_socket = -1;
    }
}

void MailServer::sendAnswer(int *socket, std::string msg)
{
    std::cout << "Sending: " << msg << std::endl;
    //sende msg an client
    if (send(*socket, msg.c_str(), msg.size(), 0) == -1)
    {
        perror("send failed");
    }
}

void MailServer::abort()
{
    abortRequested = true;
    if (new_socket != -1)
    {
        //socket verbindungen verbieten und beenden
        if (shutdown(new_socket, SHUT_RDWR) == -1)
        {
            perror("shutdown new_socket");
        }
        if (close(new_socket) == -1)
        {
            perror("close new_socket");
        }
        new_socket = -1;
    }

    if (create_socket != -1)
    {
        //socket verbindungen verbieten und beenden
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

std::vector<std::string> MailServer::splitMsg(std::string msg)
{
    std::vector<std::string> stringVector;
    std::string line;
    //string in string stream konvertieren
    std::stringstream msgStream(msg);

    //sollange stream vorhanden, bei \n spalten und in vector geben
    while (msgStream.good())
    {
        std::getline(msgStream, line);
        stringVector.push_back(line);
    }

    return stringVector;
}