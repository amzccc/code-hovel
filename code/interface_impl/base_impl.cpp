#include "base_impl.h"
#include <iostream>

using std::cout;
using std::endl;

Impl::Base::Base() {
    cout << "Impl::Base()" << endl;
}

Impl::Base::~Base() {
    cout << "Impl::~Base()" << endl;
}

void Impl::Base::print() {
    cout << "[function] Impl::Base::print()" << endl;
}