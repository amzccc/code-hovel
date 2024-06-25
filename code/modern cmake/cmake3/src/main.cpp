#include <iostream>
#include "calc.h"

using namespace std;

int main() {
    Calc c;
    cout << "2 + 2 = " << c.sum(2, 2) << endl;
    cout << "3 * 3 = " << c.multiply(3, 3) << endl;

    return 0;
}