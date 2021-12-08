#include <iostream>
#include "FileIO.h"

int main(int argc, char** argv)
{
    std::string mailsString;
    //hier den parameter von CLI für Spool Directory
    FileIO* fileio = new FileIO("/home/lukas/Downloads/MailSpool");

    //hier immer vor operation den Usernamen übergeben für ordner in Mailspool
    fileio->setUser("judith");

    //Diese Funktion liest den Inahlt
    mailsString = fileio->readDirFiles();
    std::cout << mailsString << std::endl;

    //Hier ist der erste Parameter die ganze msg und der zweite der Betreff
    fileio->saveMsg("Das ist der Inhalt von Msg 1", "Betreff1");
    fileio->saveMsg("Das ist der Inhalt", "Betreff2");

    //Kontrolle ob alles gespeichert
    mailsString = fileio->readDirFiles();
    std::cout << mailsString << std::endl;

    //Inhalt von Nachricht 1 Lesen
    std::cout << fileio->readMsg(1) << std::endl;

    //Nachricht 1 Löschen
    fileio->delMsg(1);

    //Kontrolle von löschen
    mailsString = fileio->readDirFiles();
    std::cout << mailsString << std::endl;

    //Ordner leeren
    fileio->delMsg(2);

    //speicher im Heap freigeben
    delete fileio;

    return 0;
}