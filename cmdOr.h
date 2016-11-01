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
      left->execute();
      right->execute();
      return true;
    }
};

#endif
