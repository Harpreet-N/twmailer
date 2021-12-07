#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <sstream>
#include <vector>
#include <string>

class GameState
{
	private:
	char gameBoard[9];
	char activePlayer;
	char won;
	
	public:
	GameState();
	
	//CLIENT
	//bool setMailStage(std::string msg);
	void printBoard();
	char wonGame();


    // Client Mail
   bool setState(std::string msg);
	
	//SERVER
	std::string getMsg();
	void playField(int index);
	// void evaluateResult(std::string msg);
    std::vector <std::string> evaluateResult(std::string);
	// void checkWin();
}; // TZEst  asd

#endif
