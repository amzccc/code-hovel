#ifndef __DRIVED_IMPL_H__
#define __DRIVED_IMPL_H__

#include "base_impl.h"
#include "drived.h"

namespace Impl {

class Drived : virtual public IDrived, public Impl::Base {
public:
    Drived();
    virtual ~Drived();

    void print2() override;

private:
    int b{1};
};

}   // !namespace Impl

#endif