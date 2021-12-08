#include "MailState.h"
#include <iostream>

MailState::MailState()
{

	/* for(int n=0; n<9; ++n)
		gameBoard[n] = '_';
	activePlayer = 'X';
	won = ' '; */
	std::cout << "Mail Server startet\n";
}

void MailState::printBoard()
{
	/*for(int n=0; n<9; ++n)
	{
		if(n%3 == 0)
			std::cout << std::endl;
		std::cout << " " << gameBoard[n] << " ";
	} */
}

bool MailState::setState(std::string msg)
{
    printf("%s\n", msg.c_str());
    return true;
}
/*
printf("%s\n", msg.c_str());
return true; */

std::string MailState::getMsg()
{
	std::string msg;
	for(int n=0; n<9; ++n)
		msg += gameBoard[n];
	msg += activePlayer;
	msg += won;
	return msg;
}

std::string MailState::getMethodName(std::vector<std::string>  msg, std::string directory) {

    fileio = FileIO(directory);

    std::string evaluteMethod = msg[0].c_str();
    std::string user = msg[1].c_str();

    fileio->setUser(user);

    char firstCharacter = evaluteMethod[0];
    switch (firstCharacter) {
        case 'S':
            fileio->saveMsg(msg[4].c_str(),  msg[3].c_str());
            return "SEND";
            break;
        case 'L':
            break;
        case 'R':
            break;
        case 'D':
            break;
        case 'Q':
            break;
    }
    return 0;
}

void MailState::setDirectory(std::string directory)
{

}



void MailState::playField(int index)
{
	if(index >= 0 && index <= 8 && gameBoard[index] == '_')
	{
		gameBoard[index] = activePlayer;
		//checkWin();
		activePlayer = activePlayer == 'X' ? 'O' : 'X';	
	}
}


std::vector <std::string> MailState::evaluateResult(std::string msg) {
    std::istringstream str(msg);
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
    return result;
}


char MailState::wonGame()
{
	return won;
}
