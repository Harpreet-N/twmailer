#ifndef __MSGCONTAINER_H
#define __MSGCONTAINER_H

#include <string>
#include <string.h>
#include <dirent.h>

class MsgContainer
{
private:
    int id;
    std::string subject;

public:
    MsgContainer();
    MsgContainer(int id, std::string subject);
    ~MsgContainer();
    void setWithFilename(std::string filename);
    int getId();
    std::string getSubject();
};


#endif
