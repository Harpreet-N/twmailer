all: client server

client: clientMain.cpp
	g++ -std=c++14 -Wall -Werror -o client clientMain.cpp GameClient.cpp GameClient.h GameState.cpp GameState.h

server: main.cpp
	g++ -std=c++14 -Wall -Werror -o server main.cpp GameServer.cpp GameServer.h GameState.cpp GameState.h -pthread

clean:
	rm client
	rm server
