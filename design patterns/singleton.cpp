#include <iostream>
#include <memory>
#include <map>
#include <string>

using std::cout;
using std::endl;

class FactorySingleton {
public:
    FactorySingleton() = default;

public:
    template<typename T>
    static void registerSelf(std::string name) {
        m_registry.insert(std::make_pair(name, std::shared_ptr<T>(new T)));
    }

    static std::shared_ptr<FactorySingleton> instance(std::string name) {
        if(m_registry.find(name) == m_registry.end()) {
            return nullptr;
        }
        return m_registry.at(name);
    }

private:
    inline static std::map<std::string, std::shared_ptr<FactorySingleton>> m_registry{};

public:
    virtual void whoami() = 0;
};

class Factory : public FactorySingleton {
public:
    Factory(const Factory&) = delete;
    Factory& operator=(const Factory&) = delete;

protected:
    Factory() = default;
    
public:
    void whoami() override {
        cout << "factory" << endl;
    }

    friend class FactorySingleton;
};

class SonFactory : public Factory {
public:
    SonFactory(const SonFactory&) = delete;
    SonFactory& operator=(const SonFactory&) = delete;

protected:
    SonFactory() = default;

public:
    void whoami() override {
        cout << "son factory" << endl;
    }

    friend class FactorySingleton;
};

class ChildFactory : public SonFactory {
public:
    ChildFactory(const ChildFactory&) = delete;
    ChildFactory& operator=(const ChildFactory&) = delete;

protected:
    ChildFactory() = default;

public:
    void whoami() {
        cout << "child factory" << endl;
    }

    friend class FactorySingleton;
};

int main() {
    Factory::registerSelf<Factory>("factory");

    SonFactory::registerSelf<SonFactory>("sonfactory");

    ChildFactory::registerSelf<ChildFactory>("childfactory");

    FactorySingleton::instance("factory")->whoami();

    FactorySingleton::instance("sonfactory")->whoami();

    FactorySingleton::instance("childfactory")->whoami();

    cout << std::boolalpha << (FactorySingleton::instance("noexist").get() == nullptr) << endl;

    cout << FactorySingleton::instance("factory").use_count() << endl;

    cout << FactorySingleton::instance("sonfactory").use_count() << endl;

    cout << FactorySingleton::instance("childfactory").use_count() << endl;

    return 0;
}