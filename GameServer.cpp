#include "GameServer.h"

GameServer::GameServer(){}

bool GameServer::start(int port)
{
	int reuseValue = 1;

	if ((create_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Socket error");
		return false;
	}
	if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEADDR, &reuseValue, sizeof(reuseValue)) == -1)
	{
		perror("set socket options - reuseAddr");
		return false;
	}
	if (setsockopt(create_socket, SOL_SOCKET, SO_REUSEPORT, &reuseValue,	sizeof(reuseValue)) == -1)
	{
		perror("set socket options - reusePort");
		return false;
	}

	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET; //adress familiy ipv4
	address.sin_addr.s_addr = INADDR_ANY; // = 0
	address.sin_port = htons(port);

	if (bind(create_socket, (struct sockaddr*)&address, sizeof(address)) == -1)
	{
		perror("bind error");
		return false;
	}
	return true;
}

void GameServer::listenForClients()
{
	if (listen(create_socket, 5) == -1)
	{
		perror("listen error");
		return;
	}

	while (!abortRequested)
	{
		printf("Waiting for connections...\n");

		// ACCEPTS CONNECTION SETUP
		addrlen = sizeof(struct sockaddr_in);
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


		// START CLIENT
		printf("Client connected from %s:%d...\n", inet_ntoa(cliaddress.sin_addr), ntohs(cliaddress.sin_port));
		gameState = GameState();
		clientCommunication(&new_socket);
		new_socket = -1;
	}

	abort();
}

void GameServer::clientCommunication(int* current_socket)
{
	char buffer[BUF];
	int size;
	sendGameState(current_socket);

	do
	{
		// RECEIVE
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
			printf("Client closed remote socket\n"); // ignore error
			break;
		}

		printf("Message received: %s\n", buffer); // ignore error

        gameState.evaluateResult(std::string(buffer));
// TZEst  asd
		sendGameState(current_socket);

	} while (!abortRequested);

	// closes/frees the descriptor if not already
	if (*current_socket != -1)
	{
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

void GameServer::sendGameState(int* socket)
{
	std::string msg = gameState.getMsg();
	std::cout << "Sending: " << msg << std::endl;
	if (send(*socket, msg.c_str(), msg.size(), 0) == -1)
	{
		perror("send failed");
	}
}

void GameServer::abort()
{
	abortRequested = true;
	if (new_socket != -1)
	{
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




































