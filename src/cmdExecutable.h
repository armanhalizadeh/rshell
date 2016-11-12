#ifndef CMDEXECUTABLE_H
#define CMDEXECUTABLE_H

#include "cmdBase.h"
#include <string.h>
#include <vector>

using namespace std;

class cmdExecutable: public cmdBase
{
    private:
        char* executable;
        char* args[30];

    public:
        cmdExecutable(char*);
        ~cmdExecutable() {};
        bool execute();
};

#endif
