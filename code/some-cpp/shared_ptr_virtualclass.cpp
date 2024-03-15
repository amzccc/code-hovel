#include <iostream>
#include <memory>

using namespace std;

class VirtualClass {
public:
    virtual void fun() = 0;
};

using VirtualClassPtr = shared_ptr<VirtualClass>;

class Drived : public VirtualClass {
public:
    void fun() override {
        cout << "override" << endl;
    }
};

int main() {
    VirtualClassPtr vp = make_shared<VirtualClass>(Drived());   // error 抽象类无法实例化
    vp->fun();

    return 0;
}

