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

bool FileIO::setUser(std::string username)
{
    //suche ob Ordner/Username vorhanden
    DIR* dirp;
    struct dirent* direntp;

    if ( NULL == ( dirp = opendir ( this->rootDirPath.c_str() ) ) )
    {
        perror ( "Failed to open directory" );
        return false;
    }

    while ( NULL != (direntp = readdir(dirp) ))
    {
        if( DT_DIR == direntp->d_type)
        {
            std::string name(direntp->d_name);
            
            //wenn gefunden, dann setze pfad und return true
            if(0 == strcmp(direntp->d_name, username.c_str()))
            {
                this->currentDirPath = this->rootDirPath + "/" + username;
                return true;
            }
        }
    }

    //falls nicht gefunden, nachträglich auskommentiert, da user anlegen nicht gefragt war

    if(-1 == mkdir((this->rootDirPath + "/" + username).c_str(), S_IRWXU))
    {
        perror ( "Failed to create directory" );
        return false;
    }

    this->currentDirPath = this->rootDirPath + "/" + username;


    return false;
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

    //alle nachrichten/Datein in ordner auswerten und strukturiert zurück geben
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

    //Ausgabe der Nachrichten für Client formatieren/als String
    output.append( std::to_string( messges.size() ) ).append(" Mails").append("\n");

    for(MsgContainer msg : messges)
    {
        output.append( std::to_string(msg.getId()) ).append(" : ").append(msg.getSubject()).append("\n");
    }

    return output;
}

int FileIO::getNextID()
{
    //alle nachrichten abfragen
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

    //max id holen, und um eins erhöhen
    newId = *std::max_element( numbers.begin(), numbers.end() );

    newId += 1;

    return newId;

}

void FileIO::saveMsg(std::string msg, std::string subject)
{
    int id = this->getNextID();
    //neue datei erstellen und in Datei schreiben, sowie schließen
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
    //Datei öffnen und lesen, inhalt zurück geben
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

    //Nachricht anhand vin ID suchen
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
    //Filename aus currentDirPath,Subject und id erstellen
    return ( this->currentDirPath + "/" + subject + "_" + std::to_string(id) + ".txt" );
}

bool FileIO::delMsg(int id)
{
    std::vector<MsgContainer> messges = this->getMessages();

    //Nachricht suchen
    for(MsgContainer msg : messges)
    {
        if( id == msg.getId() )
        {
            //löschen
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