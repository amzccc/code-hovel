#include <iostream>

using std::cout;
using std::endl;

class ServerState {
public:
    virtual void connect() = 0;
};

class Established : public ServerState {
public:
    ~Established() = default;
    
    static Established& instance() {
        static Established instance;
        return instance;
    }

    void connect() override {
        cout << "connection is established.\n";
    }

private:
    Established() = default;
};

class Listening : public ServerState {
public:
    ~Listening() = default;
    
    static Listening& instance() {
        static Listening instance;
        return instance;
    }

    void connect() override {
        cout << "connection is listening.\n";
    }

private:
    Listening() = default;
};

class Closed : public ServerState {
public:
    ~Closed() = default;
    
    static Closed& instance() {
        static Closed instance;
        return instance;
    }

    void connect() override {
        cout << "connection is closed.\n";
    }

private:
    Closed() = default;
};

class Server {
public:

public:
    Server() : m_state(&Closed::instance()) { }

    void changeState(ServerState* s) {
        m_state = s;
    }

    void connect() {
        m_state->connect();
    }

private:
    ServerState* m_state;
};


int main() {
    Server s;
    s.connect();

    s.changeState(&Listening::instance());
    s.connect();

    s.changeState(&Closed::instance());
    s.connect();

    return 0;
}