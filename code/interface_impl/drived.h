#ifndef __DRIVED_H__
#define __DRIVED_H__

#include "base.h"

class IDrived : virtual public IBase {
public:
    IDrived();
    virtual ~IDrived();

    virtual void print2() = 0;
};

#endif