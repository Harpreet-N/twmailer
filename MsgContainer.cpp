#include "MsgContainer.h"

MsgContainer::MsgContainer()
{
    this->id = -1;
    this->subject = "";
}

MsgContainer::MsgContainer(int id, std::string subject)
{
    this->id = id;
    this->subject = subject;
}

MsgContainer::~MsgContainer()
{
    
}

void MsgContainer::setWithFilename(std::string filename)
{
    std::string msgNumber;
    int splitIndex = filename.find_last_of("_");
    msgNumber = filename.substr(splitIndex+1, filename.size()-4);
    msgNumber = msgNumber.substr(0, msgNumber.size()-4);

    this->subject = filename.substr(0,splitIndex);
    this->id = std::stoi(msgNumber);
}

int MsgContainer::getId()
{
    return this->id;
}

std::string MsgContainer::getSubject()
{
    return this->subject;
}