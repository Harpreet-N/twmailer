#include "GameState.h"
#include <iostream>

GameState::GameState()
{

	/* for(int n=0; n<9; ++n)
		gameBoard[n] = '_';
	activePlayer = 'X';
	won = ' '; */
	std::cout << "Mail Server startet\n";
}

void GameState::printBoard()
{
	/*for(int n=0; n<9; ++n)
	{
		if(n%3 == 0)
			std::cout << std::endl;
		std::cout << " " << gameBoard[n] << " ";
	} */
}

bool GameState::setState(std::string msg)
{
    printf("%s\n", msg.c_str());
    return true;
}
/*
printf("%s\n", msg.c_str());
return true; */

std::string GameState::getMsg()
{
	std::string msg;
	for(int n=0; n<9; ++n)
		msg += gameBoard[n];
	msg += activePlayer;
	msg += won;
	return msg;
}
/*
void GameState::checkWin()
{
	if(gameBoard[0] == activePlayer && gameBoard[4] == activePlayer && gameBoard[8] == activePlayer)
	{
		won = activePlayer;
		return;
	}
	if(gameBoard[2] == activePlayer && gameBoard[4] == activePlayer && gameBoard[6] == activePlayer)
	{
		won = activePlayer;
		return;
	}
	for(int n=0; n<3; ++n)
	{
		if(gameBoard[n] == activePlayer && gameBoard[n+3] == activePlayer && gameBoard[n+6] == activePlayer)
		{
			won = activePlayer;
			return;
		}
		if(gameBoard[n*3] == activePlayer && gameBoard[n*3+1] == activePlayer && gameBoard[n*3+2] == activePlayer)
		{
			won = activePlayer;
			return;
		}
	}
} */

void GameState::playField(int index)
{
	if(index >= 0 && index <= 8 && gameBoard[index] == '_')
	{
		gameBoard[index] = activePlayer;
		//checkWin();
		activePlayer = activePlayer == 'X' ? 'O' : 'X';	
	}
}


std::vector <std::string> evaluateResult(std::string msg) {
    std::istringstream str(msg);
    // TZEst  asd
    std::vector <std::string> result;
    std::string line;
    std::getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, '\n')) {
        result.push_back(cell);
    }
    // This checks for a trailing comma with no data after it.
    if (!lineStream && cell.empty()) {
        // If there was a trailing comma then add an empty element.
        result.push_back("");
    }
   //  printf("HHHHHHHH        %d     \n", result)
    return result;
}




char GameState::wonGame()
{
	return won;
}
