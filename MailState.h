#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <sstream>
#include <vector>
#include <string>
#include "string.h"
#include "FileIO.h"

class MailState
{
	private:
	char gameBoard[9];
	char activePlayer;
	char won;
	
	public:
	MailState();
	
	//CLIENT
	//bool setMailStage(std::string msg);
	void printBoard();
	char wonGame();


    // Client Mail
   bool setState(std::string msg);
	
	//SERVER
	std::string getMsg();
	std::string getMethodName(std::vector <std::string>, std::string);
	void playField(int index);
	// void evaluateResult(std::string msg);
    std::vector <std::string> evaluateResult(std::string);
    void setDirectory(std::string);
	// void checkWin();
}; // TZEst  asd

#endif