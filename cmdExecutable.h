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
    vector<char*> args;
  public:
    cmdExecutable(char*);
    bool execute();
};

#endif
