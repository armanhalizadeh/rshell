#ifndef CMDOR_H
#define CMDOR_H

#include "cmdBase.h"
#include <string.h>

class cmdOr: public cmdBase
{
    private:
        cmdBase* left;
        cmdBase* right;

    public:

        cmdOr(cmdBase* l, cmdBase* r): left(l), right(r) {};

        bool execute()
        {

            if ( right == NULL )
                return false;

            if(left->execute())
                return true;

            else if(right->execute())
                return true;
            
            return false;
        }
};

#endif
