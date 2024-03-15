#include <iostream>
#include <string>
#include <vector>
#include <memory>

int main()
{
    using namespace std;
    
    //use shared_ptr        
    shared_ptr<string> ptr1(new string ("hello ptr"));
    shared_ptr<string> ptr2{new string ("hello ptr")};
    shared_ptr<string> ptr3 = make_shared<string> ("hello");        //这样使用是安全的,但直接使用=是不安全的
    //当然可以重定向一个shared_ptr
    shared_ptr<string> ptrreset = make_shared<string>("hello");
    ptrreset.reset(new string("new hello"));

    //智能指针可以传入第二个参数，当销毁时会调用该仿函数
    shared_ptr<string> ptr4(new string("nico"), [] (string *p){
                            cout << "delete " << *p << endl;
                            });
    //shared_ptr有个坑，shared_ptr可以指向arr[],但不能自己释放，
    //也就是说shared_ptr析构时调用的是delete，而不会调用delete[]
    //解决办法：可以将delete[]作为第二个参数传入
    shared_ptr<int> ptr_arr(new int[10], [](int* p){
                                delete[] p;
                            });
    //shared_ptr的循环引用问题和指向同一对象问题
    //循环引用
    class Ptr_B;
    class Ptr_A{
    public:
        //weak_ptr<Ptr_B> pb;       //改用weak_ptr可以避免循环引用
        shared_ptr<Ptr_B> pb;    
        Ptr_A(){}
        ~Ptr_A(){
            cout << "ptr_A析构" << endl;
        }
    };
    class Ptr_B{
    public:
        shared_ptr<Ptr_A> pa;    
        Ptr_B(){}
        ~Ptr_B(){
            cout << "ptr_B析构" << endl;
        }
    };

    shared_ptr<Ptr_A> a{new Ptr_A};
    shared_ptr<Ptr_B> b{new Ptr_B};
    a->pb = b;
    b->pa = a;                  //这段代码是不能正确执行的，pa和pb形成了循环引用，程序不知道谁先析构

    int *p = new int;
    //shared_ptr<int> p1(p);
    shared_ptr<int> p2(p);      //两个shared_ptr指向了同一个对象，会造成释放两次的bug，程序不执行

}