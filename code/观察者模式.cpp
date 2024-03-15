#include <iostream>
#include <vector>
using namespace std;

template <typename Tparam>
class SlotBase 
{
public:
    virtual void slotFunction(Tparam param) = 0;
    virtual ~SlotBase() = default;
};

template <typename Trecv, typename Tparam>  //Trecv是接收类
class Slot: public SlotBase<Tparam> 
{
private:
    Trecv* m_ptr_recv;    //定义一个接收者的指针，在构造时初始化
    void (Trecv::*m_func)(Tparam param);    //定义一个接收者类中的成员函数指针

public:
    Slot(Trecv* pObj, void(Trecv::*func)(Tparam)) {
        this->m_ptr_recv = pObj;
        this->m_func = func;    //使用类外的接收者类的对象指针与接收者类中的成员函数指针进行初始化
    }
    void slotFunction(Tparam param) override{
        (m_ptr_recv->*m_func)(param);   //成员对象指针调用类内的成员函数
    }
};

template <typename Tparam>
class Signal
{
private:
    vector<SlotBase<Tparam>*> sgn_vec;

public:
    template<typename Trecv>
    void addSlot(Trecv* pObj, void (Trecv::*func)(Tparam)) {
        sgn_vec.emplace_back(new Slot<Trecv, Tparam>(pObj, func));
    }

    void operator() (Tparam param) {
        for(auto p: sgn_vec) {
            p->slotFunction(param);
        }
    }
};

class Recver1
{
public:
    void func1(int param) {
        cout << "这是Recver1中的方法，参数为：" << param << endl;
    }
};

class Recver2
{
public:
    void func2(int param) {
        cout << "这是Recver2中的方法，参数为：" << param << endl;
    }
};

class SendObj
{
public:
    Signal<int> valueChange;
public:
    void testSignal(int value) {
        valueChange(value);
    }
};

#define connect(sender, signal, recver, method) (sender)->signal.addSlot(recver, method)

int main()
{
    Recver1* r1 = new Recver1;
    Recver2* r2 = new Recver2;
    SendObj* sd = new SendObj;

    connect(sd, valueChange, r1, &Recver1::func1);
    connect(sd, valueChange, r2, &Recver2::func2);
    sd->testSignal(42);    

    return 0;
}