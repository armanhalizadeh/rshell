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
            if ( left == NULL )
                return false;

            left->execute();

            if ( right == NULL )
                return false;

            right->execute();

            return true;
        }
};

#endif
