#include <iostream>
#include "configure.h"

using namespace std;

int main() {
#ifdef FOO_ENABLE
    cout << "FOO_ENABLE: ON" << endl;
#endif
    cout << "FOO_STRING1: " << FOO_STRING1 << endl;
    cout << "FOO_STRING1: " << FOO_STRING2 << endl;  

    return 0;
}