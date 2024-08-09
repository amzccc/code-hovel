#include <iostream>

using std::cout;
using std::endl;

enum class ReqType : char {
    null,
    type1,
    type2,
    type3
};

class ChainHandler {
public:
    ChainHandler(ChainHandler* successor, ReqType type)
        : m_successor(successor), m_type(type) { }

public:
    virtual void handleReq(ReqType req) = 0;

protected:
    virtual void nextHandler(ReqType req) {
        if(m_successor != nullptr) {
            m_successor->handleReq(req);
        }
    }

protected:
    ReqType m_type{ ReqType::null };

private:
    ChainHandler* m_successor{ nullptr };
};

class Chain1 : public ChainHandler {
public:
    Chain1(ChainHandler* successor, ReqType type)
        : ChainHandler(successor, type) { }

    void handleReq(ReqType req) override {
        if(req == m_type) {
            cout << "Chain1" << endl;
        }
        else {
            nextHandler(req);
        }
    }
};

class Chain2 : public ChainHandler {
public:
    Chain2(ChainHandler* successor, ReqType type)
        : ChainHandler(successor, type) { }

    void handleReq(ReqType req) override {
        if(req == m_type) {
            cout << "Chain2" << endl;
        }
        else {
            nextHandler(req);
        }
    }
};

class Chain3 : public ChainHandler {
public:
    Chain3(ChainHandler* successor, ReqType type)
        : ChainHandler(successor, type) { }

    void handleReq(ReqType req) override {
        if(req == m_type) {
            cout << "Chain3" << endl;
        }
        else {
            nextHandler(req);
        }
    }
};

int main() {
    Chain1 c1(nullptr, ReqType::type1);
    Chain2 c2(&c1, ReqType::type2);
    Chain3 c3(&c2, ReqType::type3);

    c3.handleReq(ReqType::type3);
    c3.handleReq(ReqType::type2);
    c3.handleReq(ReqType::type1);

    return 0;
}