#ifndef __FILEIO_H
#define __FILEIO_H

#include <iostream>
#include <string>
#include <string.h>
#include <dirent.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstdio>

#include "MsgContainer.h"

class FileIO
{
private:
    std::string rootDirPath;
    std::string currentDirPath;
    int getNextID();
    std::vector<MsgContainer> getMessages();
    std::string getContent(std::string filename);
    std::string makeFilename(int id, std::string subject);
public:
    FileIO(std::string rootDir);
    ~FileIO();
    void setUser(std::string username);
    std::string readDirFiles();
    void saveMsg(std::string msg, std::string subject);
    std::string readMsg(int id);
    bool delMsg(int id);
};


#endif

