#ifndef CMDAND_H
#define CMDAND_H

#include "cmdBase.h"
#include <string.h>
#include <iostream>

class cmdAnd: public cmdBase
{
    private:
        cmdBase* left;
        cmdBase* right;

    public:
        cmdAnd(cmdBase* l, cmdBase* r): left(l), right(r) {};

        ~cmdAnd()
        {
            delete left;
            delete right;
        }

        bool execute()
        {

            // if there is no input to the right
            // return
            if ( right == NULL )
                return false;

            if (!left->execute())
                return false;

            else if (!right->execute())
                return false;
            else
                return true;
        }
};

#endif
