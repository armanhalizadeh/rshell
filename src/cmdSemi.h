#ifndef CMDSEMI_H
#define CMDSEMI_H

#include "cmdBase.h"
#include <string.h>

class cmdSemi: public cmdBase
{
    private:
        cmdBase* left;
        cmdBase* right;
    public:
        cmdSemi(cmdBase* l, cmdBase* r): left(l), right(r) {};
        bool execute()
        {
            left->execute();
            right->execute();
            return true;
        }
};

#endif
