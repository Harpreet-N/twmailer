#include "MailState.h"
#include <iostream>

MailState::MailState()
{
	std::cout << "Mail Server startet\n";
}


bool MailState::setState(std::string msg)
{
    printf("%s\n", msg.c_str());
    return true;
}


std::string MailState::getMsg()
{
	std::string msg;
	return msg;
}

std::string MailState::getMethodName(std::vector<std::string>  msg, std::string directory)
{
   FileIO* fileio = new FileIO(directory);

   std::string evaluteMethod = msg[1];
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


std::vector <std::string> MailState::evaluateResult(std::string msg)
{
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
