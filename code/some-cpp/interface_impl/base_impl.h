#ifndef __BASE_IMPL_H__
#define __BASE_IMPL_H__

#include "base.h"

namespace Impl {   

class Base : virtual public IBase {
public:
    Base(); 
    virtual ~Base(); 

    void print() override;

private:
    int a{0};
};

}   // !namespace Impl

#endif