#include "drived_impl.h"
#include <iostream>

using std::cout;
using std::endl;

Impl::Drived::Drived() {
    cout << "Impl::Drived()" << endl;
}

Impl::Drived::~Drived() {
    cout << "Impl::~Drived()" << endl;
}

void Impl::Drived::print2() {
    cout << "[function] Impl::Drived::print2()" << endl;
}