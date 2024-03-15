#include <iostream>
#include <memory>

using namespace std;

namespace Impl {
    class Base;
    class Driver;    
} // end of namespace Impl

class IBase {
public:
    virtual void print() = 0; 

    virtual ~IBase() {
        cout << "~IBase" << endl;
    };
};

class Impl::Base : virtual public IBase {
public:
    Base() {
        cout << "Impl::Base()" << endl;
    }

    virtual ~Base() {
        cout << "Impl::~Base()" << endl;
    }

    void print() override {
        cout << "Base print function" << endl;
    }
    
};

class IDriver : virtual public IBase {
public:
    virtual ~IDriver() {
        cout << "~IDriver()" << endl;
    };

    virtual void print2() = 0;
};

class Impl::Driver : virtual public IDriver, public Impl::Base {
public:
    Driver() : Base() {
        cout << "Impl::Driver()" << endl;
    }
    virtual ~Driver() {
        cout << "Impl::~Driver()" << endl;
    }

    void print2() override {
        cout << "Driver print2 function" << endl;
    }
};

class Driver : public IDriver {
public:
    Driver() : impl(make_unique<Impl::Driver>()) {
        cout << "Driver()" << endl;
    };
    ~Driver() {
        cout << "~Driver()" << endl;
        impl.~unique_ptr();
    };

    void print() override {
        impl->print();
    }

    void print2() override {
        impl->print2();
    }

private:
    unique_ptr<Impl::Driver> impl;
};

void fun(IDriver& driver) {
    driver.print();
    driver.print2();
}

int main() {
    cout << "----- create Driver -----\n";
    Driver d;
    cout << "----- call fun -----\n";
    fun(d);
    cout << "----- end program -----\n";
    return 0;
}