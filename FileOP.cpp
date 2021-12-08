#include "FileIO.h"

#include <iostream>

FileIO::FileIO(std::string rootDir)
{
    this->rootDirPath = rootDir;
    this->currentDirPath = rootDir;
}

FileIO::~FileIO()
{
}

void FileIO::setUser(std::string username)
{
    this->currentDirPath = this->rootDirPath + "/" + username;
}

std::vector<MsgContainer> FileIO::getMessages()
{
    DIR* dirp;
    struct dirent* direntp;
    std::vector<MsgContainer> messages = {};

    if ( NULL == ( dirp = opendir ( this->currentDirPath.c_str() ) ) )
    {
        perror ( "Failed to open directory" );
        return messages;
    }

    while ( NULL != (direntp = readdir(dirp) ))
    {
        if( DT_DIR != direntp->d_type && 0 != strcmp ( direntp->d_name, "." ) && 0 != strcmp ( direntp->d_name, ".." ) )
        {
            std::string name(direntp->d_name);
            MsgContainer msg = MsgContainer();
            msg.setWithFilename(name);
            messages.push_back(msg);
        }
    }

    return messages;
}

std::string FileIO::readDirFiles()
{
    std::string output;

    std::vector<MsgContainer> messges = this->getMessages();

    for(MsgContainer msg : messges)
    {
        output.append( std::to_string(msg.getId()) ).append(" : ").append(msg.getSubject()).append("\n");
    }

    return output;
}

int FileIO::getNextID()
{
    std::vector<MsgContainer> messges = this->getMessages();
    std::vector<int> numbers = {};
    int newId = -1;

    for(MsgContainer msg : messges)
    {
        numbers.push_back( msg.getId() );
    }

    if(0 == numbers.size())
    {
        return 0;
    }

    newId = *std::max_element( numbers.begin(), numbers.end() );

    newId += 1;

    return newId;

}

void FileIO::saveMsg(std::string msg, std::string subject)
{
    int id = this->getNextID();
    std::ofstream newFile;

    std::string filename = this->makeFilename(id, subject);

    newFile.open(filename);

    if(newFile.is_open())
    {
        newFile << msg;
    }

    newFile.close();

}

std::string FileIO::getContent(std::string filename)
{
    std::string output;
    std::ifstream msgFile;
    msgFile.open(filename, std::ios::in);

    if(msgFile)
    {
        std::stringstream strStream;
        strStream << msgFile.rdbuf();
        output = strStream.str();
    }
    else 
    {
        std::cout << "Fehler beim Lesen!" << std::endl;
        return "";
    }

    return output;
}

std::string FileIO::readMsg(int id)
{
    std::vector<MsgContainer> messges = this->getMessages();
    std::string output;

    for(MsgContainer msg : messges)
    {
        if( id == msg.getId() )
        {
            output = this->getContent(this->makeFilename(msg.getId(), msg.getSubject()));
            break;
        }
    }

    return output;
}

std::string FileIO::makeFilename(int id, std::string subject)
{
    return ( this->currentDirPath + "/" + subject + "_" + std::to_string(id) + ".txt" );
}

bool FileIO::delMsg(int id)
{
    std::vector<MsgContainer> messges = this->getMessages();

    for(MsgContainer msg : messges)
    {
        if( id == msg.getId() )
        {
            if( 0 != std::remove( (this->makeFilename(msg.getId(), msg.getSubject() ) ).c_str() ) )
            {
                perror("Error deleting file");
                return false;
            }
            else
            {
                return true;
            }

            break;
        }
    }

    return false;
}