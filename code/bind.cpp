#include <functional>
#include <iostream>

using namespace std;

int b = 10;

class A {
public:
    A();
    void fun(int i) {
        cout << i << endl;
    }
    function<void()> f;
};

A::A() {
    f = std::bind(&A::fun, this, b);
}

int main() {
    A a;
    a.f();

    return 0;
}