#include <iostream>
#include <list>

using std::cout;
using std::endl;

class Subject;

class Observer {
public:
    virtual ~Observer() = default;

    virtual void update(Subject* changedobj) = 0;

protected:
    Observer() = default;
};

class Subject {
public:
    virtual ~Subject() = default;

    virtual void attach(Observer* observer) {
        m_observers.push_front(observer);
    }

    virtual void notify() {
        for(auto observer : m_observers) {
            observer->update(this);
        }
    }

protected:
    explicit Subject(const std::string& name) : m_name(name) { }

private:
    std::list<Observer*> m_observers{};

public:
    std::string m_name;
};

class Data : public Subject {
public:
    explicit Data(const std::string& name) : Subject(name) { };
    
    void change() {
        notify();
    }
};

class PieChart : public Observer {
public:
    void update(Subject* changedobj) {
        cout << changedobj->m_name << " changed, PieChart update\n";
    }
};

class BarChart : public Observer {
public:
    void update(Subject* changedobj) {
        cout << changedobj->m_name << " changed, BarChart update\n";
    }
};

class LineChart : public Observer {
public:
    void update(Subject* changedobj) {
        cout << changedobj->m_name << " changed, LineChart update\n";
    }
};

int main() {
    Data data("data");
    PieChart pie;
    BarChart bar;
    LineChart line;
    data.attach(&pie);
    data.attach(&bar);
    data.attach(&line);
    data.change();
    
    return 0;
}