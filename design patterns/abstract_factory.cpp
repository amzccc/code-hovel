#include <iostream>
#include <memory>

using namespace std;

class AbstractProductA {
public:
    virtual ~AbstractProductA() = default;

    virtual void eat() = 0;
};

class ProductA1 : public AbstractProductA {
    void eat() override {
        cout << "yummy" << endl;
    }
};

class ProductA2 : public AbstractProductA {
    void eat() override {
        cout << "awful" << endl;
    }
};

class AbstractProductB {
public:
    virtual ~AbstractProductB() = default;

    virtual void play() = 0;
};

class ProductB1 : public AbstractProductB {
public:
    void play() override {
        cout << "just so so" << std::endl;
    }
};

class ProductB2 : public AbstractProductB {
public:
    void play() override {
        cout << "very cool" << std::endl;
    }
};

class AbstractFactory {
public:
    virtual ~AbstractFactory() = default;

public:
    virtual std::shared_ptr<AbstractProductA> createProductA() = 0;

    virtual std::shared_ptr<AbstractProductB> createProductB() = 0;
};

class ConcreteFactoryA : public AbstractFactory {
public:
    ~ConcreteFactoryA() = default;

public:
    std::shared_ptr<AbstractProductA> createProductA() override {
        cout << "productA made in factoryA" << endl;
        return std::make_shared<ProductA1>();
    }

    std::shared_ptr<AbstractProductB> createProductB() override {
        cout << "productB made in factoryA" << endl;
        return std::make_shared<ProductB2>();
    }
};

class ConcreteFactoryB : public AbstractFactory {
public:
    std::shared_ptr<AbstractProductA> createProductA() override {
        cout << "productA made in factoryB" << endl;
        return std::make_shared<ProductA2>();
    }

    std::shared_ptr<AbstractProductB> createProductB() override {
        cout << "productB made in factoryB" << endl;
        return std::make_shared<ProductB1>();
    }
};

class ProductA3 : public AbstractProductA {
    void eat() override {
        cout << "delicious" << endl;
    }
};

class ProductB3 : public AbstractProductB {
    void play() override {
        cout << "super cool" << endl;
    }
};

class ConcreteFactoryC : public ConcreteFactoryB {
    std::shared_ptr<AbstractProductA> createProductA() override {
        cout << "productA made in factoryC" << endl;
        return std::make_shared<ProductA3>();
    }

    std::shared_ptr<AbstractProductB> createProductB() override {
        cout << "productB made in factoryC" << endl;
        return std::make_shared<ProductB3>();
    }
};

void client(AbstractFactory& factory) {
    auto product_a = factory.createProductA();
    product_a->eat();
    auto product_b = factory.createProductB();
    product_b->play();
}

int main() {
    ConcreteFactoryA factory_a;
    client(factory_a);

    ConcreteFactoryB factory_b;
    client(factory_b);

    ConcreteFactoryC factory_c;
    client(factory_c);

    return 0;
}