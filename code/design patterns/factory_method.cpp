#include <iostream>

using std::cout;
using std::endl;

class BaseProduct {
public:
    virtual void eat() = 0;
    virtual void drink() = 0;
    virtual void play() = 0;
};

class BaseFactory {
public:
    virtual BaseProduct* createProduct() = 0;
};

struct ProductA : public BaseProduct {
    void eat() override {
        cout << "product a eat\n";
    }

    void drink() override {
        cout << "product a drink\n";
    }

    void play() override {
        cout << "product a play\n";
    }
};

class FactoryA : public BaseFactory {
    BaseProduct* createProduct() override {
        return new ProductA;
    }
};

struct ProductB : public BaseProduct {
    void eat() override {
        cout << "product b eat\n";
    }

    void drink() override {
        cout << "product b drink\n";
    }

    void play() override {
        cout << "product b play\n";
    }
};

class FactoryB : public BaseFactory {
    BaseProduct* createProduct() override {
        return new ProductB;
    }
};

int main() {
    BaseFactory* ptr = new FactoryA;

    BaseProduct* p_a = ptr->createProduct();
    p_a->eat();
    p_a->drink();
    p_a->play();
    delete ptr;

    ptr = new FactoryB;
    BaseProduct* p_b = ptr->createProduct();
    p_b->eat();
    p_b->drink();
    p_b->play();
    
    return 0;
}