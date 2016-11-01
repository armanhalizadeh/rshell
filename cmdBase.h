#ifndef CMDBASE_H
#define CMDBASE_H

class cmdBase
{
  public:
    cmdBase() {};
    virtual bool execute() = 0;
};

#endif
