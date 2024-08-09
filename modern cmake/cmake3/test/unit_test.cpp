#include <iostream>
#include <string>
#include "calc_test.h"

using namespace std;

int main(int argc, char** argv) {
    if(argc < 2 || argv[1] == string("1")) {
        cout << "start-1\n";
        sumTwoIntegers();
    }

    if(argc < 2 || argv[1] == string("2")) {
        cout << "start-2\n";
        multiplyTwoIntegers();
    }

    return 0;
}