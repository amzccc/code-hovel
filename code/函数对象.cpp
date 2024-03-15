//相比普通函数，仿函数更灵活，具有自己的状态，能作为模板参数传递，且执行效率更高
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <iterator>
#include <functional>

using namespace std;
using namespace std::placeholders;
//一个仿函数
class IntSequence {
private:
    int value;
public:
    IntSequence(int init): value(init) {}
    int operator () () {
        return ++value;
    }
};

//计算平均值的仿函数
class MeanValue {
private:
    long num;
    long sum;
public:
    MeanValue():num(0), sum(0) {}
    void operator() (int elem) {
        ++num;
        sum += elem;
    }
    double value() {
        return static_cast<double>(sum) / static_cast<double>(num);
    }
};

//bind调用成员函数
class Person {
    private:
    string name;
    public:
    Person(const string &n):name(n) {
    }
    void print() const {
        cout << name << endl;
    }
    void print2(const string &prefix) const {
        cout << prefix << name << endl;
    }
};

int main()
{
    list<int> coll;
    IntSequence seq(1);
    //模板中传递的是引用，会使仿函数中参数也发生变化
    generate_n<back_insert_iterator<list<int>>, int, IntSequence&> (back_inserter(coll), 4, seq);
    for(auto it: coll) {
        cout << it <<" ";
    }
    cout << endl;

    //使用默认模板参数，是赋值传递
    generate_n (back_inserter(coll), 4, IntSequence(42));
    for(auto it: coll) {
        cout << it <<" ";
    }
    cout << endl;

    generate_n(back_inserter(coll), 4, seq);
    for(auto it: coll) {
        cout << it <<" ";
    }
    cout << endl;

    generate_n(back_inserter(coll), 4, seq);
    for(auto it: coll) {
        cout << it <<" ";
    }
    cout << endl;
    cout << "--------------------------------------------\n";
    cout << "使用for_each()保存最终状态: \n";
    vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
    MeanValue mv = for_each(vec.begin(), vec.end(), MeanValue());
    cout << "mean value: " << mv.value() << endl;
    cout << "----------------------------------------------\n";
    cout <<"bind可以调用绑定对象的成员函数\n";
    vector<Person> vec1 = {Person("Tick"), Person("Trick"), Person("Track")};
    for_each (vec1.begin(), vec1.end(), bind(&Person::print, _1));
    cout << endl;
    for_each(vec1.begin(), vec1.end(), bind(&Person::print2, _1, "Person: "));
    cout << endl;
    bind(&Person::print2, _1, "This is: ") (Person("nico"));
    cout << "----------------------------------------------\n";
    cout << "Lambda: ->return [](){ }\n";
    //lambda更类似于隐函数，当一个函数对象偶尔用到时，使用lambda不用再写一个函数对象的类，更方便一点
    list<int> li {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(auto it: li) {
        cout << it <<" ";
    }
    cout << endl;
    list<int>::iterator pos;
    int count = 0;
    //mutable将参数声明为可变的，捕获列表采用赋值操作，导致多删除了一份
    pos = remove_if(li.begin(), li.end(), [count](int) mutable {    
                    return ++count == 3;
                });
    li.erase(pos, li.end());
    for(auto it: li) {
        cout << it <<" ";
    }
    cout << endl;
    list<int> li2 {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    //使用引用捕获，并不使用mutable可以正常实现
    pos = remove_if(li2.begin(), li2.end(), [&count](int) {    
                    return ++count == 3;
                });
    li2.erase(pos, li2.end());
    for(auto it: li2) {
        cout << it <<" ";
    }
    cout << endl;
}
