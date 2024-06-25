#include <cstdlib>
#include <iostream>
#include "calc.h"

void sumTwoIntegers() {
    Calc sut;
    std::cout << 1 << std::endl;
    if(sut.sum(2, 2) != 4) {
        std::exit(1);
    }
}

void multiplyTwoIntegers() {
    Calc sut;
    std::cout << 2 << std::endl;
    if(sut.multiply(1, 3) != 3) {
        std::exit(1);
    }
}