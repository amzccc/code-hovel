#include "drived.h"
#include "drived_impl.h"
#include <memory>
#include <iostream>

using namespace std;

class DrivedInstance : virtual public IDrived {
public:
    DrivedInstance() {
        cout << "DrivedInstance()" << endl;
    }

    virtual ~DrivedInstance() {
        cout << "~DrivedInstance()" << endl;
    }

    void print() override {
        impl->print();
    }

    void print2() override {
        impl->print2();
    }

private:
    unique_ptr<Impl::Drived> impl{make_unique<Impl::Drived>()};
};

void fun(IDrived& d) {
    d.print();
    d.print2();
}

int main(int argc, char** argv) {
    DrivedInstance instance;
    fun(instance);

    return EXIT_SUCCESS;
}