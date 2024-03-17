#include <iostream>
#include <utility>
#include <tuple>

using namespace std;

class Foo {
public:
    Foo (tuple<int, float>) {
        cout << "Foo::Foo(tuple)" << endl;
    }

    template <typename... Args>     //Foo实参数量不定的语法 Args...
    Foo (Args... args) {
        cout << "Foo::Foo(args...)" << endl;
    }
};

int main()
{
    //创建tuple t
    tuple<int, float> t(1, 2.22);

    //将tuple整体传递给Foo构造
    pair<int, Foo> p1(42, t);

    //将tuple中元素传递给Foo构造
    pair<int, Foo> p2(piecewise_construct, make_tuple(42), t);  //piecewise_construct可以理解是pair用tuple的元素构造的标识符
                                                            
}