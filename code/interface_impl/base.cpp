#include "base.h"
#include <iostream>

using std::cout;
using std::endl;

IBase::IBase() {
    cout << "IBase()" << endl;    
}

IBase::~IBase() {
    cout << "~IBase()" << endl;
}