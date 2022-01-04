all: twmailer_client twmailer_server

twmailer_client: main_client.cpp
	g++ -std=c++14 -Wall -Werror -Iinc -o twmailer_client main_client.cpp inc/MailClient.h src/MailClient.cpp inc/FileIO.h src/FileIO.cpp inc/MsgContainer.h src/MsgContainer.cpp inc/LdapClient.h src/LdapClient.cpp

twmailer_server: main_server.cpp
	g++ -std=c++14 -Wall -Werror -Iinc -o twmailer_server main_server.cpp inc/MailServer.h src/MailServer.cpp inc/FileIO.h src/FileIO.cpp inc/MsgContainer.h src/MsgContainer.cpp inc/LdapClient.h src/LdapClient.cpp

clean:
	rm -f twmailer_client
	rm -f twmailer_server
