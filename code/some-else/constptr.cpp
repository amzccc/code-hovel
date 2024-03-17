#include <iostream>

int main ()
{
    const double pi = 3.14;

    // double *ptr = pi;  //error 
    const double *ptr = &pi;
    // *ptr = 1;     //error
  

    int ri = 10;
    
    //指向常量的指针可指向变量
    const int five = 5;
    const int *ptr2 = &five;
    ptr2 = &ri;     //但不能通过指向常量的指针改变指向的变量

    //常量指针
    int num = 1;
    std::cout << "initial: num = " << num << std::endl;
    int *const cptr = &num;
    
    const int cnum = 2;
    const int *const cptr2 = &cnum;
    //常量指针即指针存放的地址不变，指向的对象能否改变取决于对象的属性
    std::cout << "change num by *ptr" << std::endl;
    *cptr = 3;
    // *cptr2 = 4;  //error
    std::cout << "const int *cptr = " << *cptr << std::endl;
    std::cout << "num = " << num << std::endl;

    /*
    指向常量的指针(type const *ptr) 和 常量指针(type *const ptr) 是不同的概念
    指向常量的指针 —— 底层const     指向的是一个常量对象，不能通过底层const指针修改该对象，但底层const指针可以重新指向新对象
    常量指针 —— 顶层const       表示指针本身是个常量，一旦指向一个对象就不可在更改，如果允许可以通过顶层const指针来修改指向的对象的值

    顶层const表示任意对象是常量 ------- 本身是const；
    底层const与指针和引用等复合类型的基本类型部分有关 ------- 指向的是个const
    */


    //常量引用可以指向变量，但不能通过该引用修改指向的变量
    const int &r = ri;   




    return 0;
}