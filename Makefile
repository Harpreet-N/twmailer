all: client file server

client: clientMain.cpp
	g++ -std=c++14 -Wall -Werror -o client clientMain.cpp MailClient.cpp MailClient.h MailState.cpp MailState.h

file: mainB.cpp
	g++ -std=c++14 -Wall -Werror -o file mainB.cpp MsgContainer.cpp MsgContainer.h FileIO.h FileOP.cpp -pthread

server: main.cpp
	g++ -std=c++14 -Wall -Werror -o server main.cpp MailServer.cpp MailServer.h MailState.cpp MailState.h -pthread

clean:
	rm client
	rm file
	rm server

