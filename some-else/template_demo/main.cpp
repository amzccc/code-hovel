#include <iostream>
#include "template_interface.hpp"

using std::cout;
using std::endl;

int main() {
    Selection<Kind::bird, Voice::jojo, Leg::two> bird;
    bird.feather.push_back("pink");
    bird.property();
    Selection<Kind::cat, Voice::mimi, Leg::four> cat1;
    cat1.name = "xiao hua";
    cat1.property();
    Selection<Kind::cat, Voice::miao, Leg::four> cat2;
    cat2.lazy = 5;
    cat2.property();
    Selection<Kind::dog, Voice::wang, Leg::four> dog;
    cout << dog.tag << endl;
    dog.job = "destory sofa";
    dog.property();
    return 0;
}