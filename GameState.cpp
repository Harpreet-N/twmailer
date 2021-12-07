#include "GameState.h"
#include <iostream>

GameState::GameState()
{

	for(int n=0; n<9; ++n)
		gameBoard[n] = '_';
	activePlayer = 'X';
	won = ' ';
	std::cout << "Mail Server startet\n";
}

void GameState::printBoard()
{
	for(int n=0; n<9; ++n)
	{
		if(n%3 == 0)
			std::cout << std::endl;
		std::cout << " " << gameBoard[n] << " ";
	}
}

bool GameState::setState(std::string msg)
{
	for(int n=0; n<9; ++n)
		gameBoard[n] = msg[n];
	activePlayer = msg[9];
	won = msg[10];	
	return true;
}

std::string GameState::getMsg()
{
	std::string msg;
	for(int n=0; n<9; ++n)
		msg += gameBoard[n];
	msg += activePlayer;
	msg += won;
	return msg;
}

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
}

void GameState::playField(int index)
{
	if(index >= 0 && index <= 8 && gameBoard[index] == '_')
	{
		gameBoard[index] = activePlayer;
		checkWin();	
		activePlayer = activePlayer == 'X' ? 'O' : 'X';	
	}
}

char GameState::wonGame()
{
	return won;
}
