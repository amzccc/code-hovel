> 书中一些条款已经不太适用于c++11及以后，所以需要参考着看。
> 笔记思路：在梳理各个条目的基础上加入自己的一些主观理解（未必是对的）。

[toc]
# Effective C++
## C++是一个语言联邦
C++是个多重范型编程语言，同时支持过程形式、面向对象形式、函数形式、泛型形式、元编程形式的语言。所以最好将C++视为一个由相关语言组成的联邦而不是单一语言。
次语言主要有四个：
- C风格：区块、语句、预处理、内置数据类型、数组、指针等概念都继承于C。当C++以C的风格工作时，可能会体现出C的局限性，没有模板、没有异常、没有重载等。
- 面向对象的C++（Object-Oriented C++）：可以理解为最早期的C++形式 —— C with Class，具有类的特性（构造、析构等）、封装、继承、多态、virtual函数（动态绑定）等。
- Template C++：泛型编程部分，*这部分使得C++开始强烈区别于以前的C++*。
- STL：标准模板库，没啥好说的，六个组件：容器、迭代器、算法、函数对象（仿函数）、适配器、内存分配器。

## 尽量以const、enum、inline替换#define
这个条款的意思是，用编译器来代替预处理器的操作是更好的，#define不被看作是语言的一部分，只是在预处理阶段简单地进行内容的替换，容易出现不易察觉的错误，而且在调试时，无法对这个宏定义进行追踪。如果采用语言常量，就会被编译器记录到记号表中，另外用常量也比用#define的代码量小。
如果不想让别人获得一个pointer或者reference指向你的常量时，enum可以实现这种约束（*enum是枚举类，是不允许指针指向枚举类地址的*）。

==总结==
- **对于单纯常量，最好以const对象或enums替换#define。**
- **对于形似函数的宏，最好改用inline函数替换#defines。**

## 尽可能使用const
const可以用在类外部来修饰全局（global）常量或者命名空间（namespace）中的常量，或者修饰文件、函数、以及区块作用域中的静态对象。修饰指针时，可以指出指针本身`char* const ptr`、指针指向的对象`const char* ptr`、或者两者都（不）是const。
const用来约束函数返回值时，表示函数返回的是一个const对象；const放在函数后面时，表示在该函数中不能对函数所在类中的数据进行修改。

==总结==
- **根据需要将一些东西声明为const可以帮助编译器检测出错误用法。const可施加在任何作用域内的对象、函数参数、函数返回类型、成员函数本体**。
- **编译器强制实施bitwise constness，但在编写程序时应该确保“概念上的常量性”（conceptual constness）**。

> ==**bitwise constness**==：认为成员函数只有在不更改对象的任何成员变量的情况下才是const，也就是程序中的任何bit都不发生更改。
> 好处是编译器容易检测出程序中的错误，这也正是编译器所采用的const形式；不足在于，有时无法起到想要的const目的，例如，在一个类中只定义了指针，则指针的地址是明确的，当定义了一个const该类，并将指针指向一个对象时，却可以通过这个const的指针修改指向的对象，这有时会引起反直观的现象。
> ==**logical constness**==：认为一个const成员函数可以修改它所处理的对象内的某些this，但只有在客户端侦测不出时才能如此。最简单的就是利用mutable关键字解除const的约束。
- **当const和 non-const成员函数有着实质等价的实现时，令non-const版本用const版本可避免代码重复**。

## 确定对象被使用前已被初始化
在C++中，对于声明的对象是不保证其一定被初始化的，所以最好地做法是**在声明时显式地进行初始化操作**。
C++规定，**对于对象的成员变量的初始化动作发生在进入构造函数本体之前**。对于一种初始化操作——在构造函数中对成员变量进行赋值，显然不是最佳的选择，因为这种操作实际上是对成员变量进行了两次copy动作，一次在进入构造函数之前，一次在构造函数作用域内；所以更有效的做法是**使用初始化列表**，这样会在进入构造函数之前就完成了成员变量的初始化，只需要一次copy动作。
C++中有着固定的“成员初始化顺序”，基类总是更早于派生类被初始化，而类中的成员变量总是以声明的顺序被初始化。但不同编译单元内的对象的初始化次序并没有明确定义。
``` c++
//one.cpp
class FileSystem {
public:
    std::size_t numDisks() const;
};

extern FileSystem tfs;


//another.cpp
class Directory {
public:
    Directory(params);
};

Directory::Directory(params) {
    std::size_t disks = tfs.numDisks();
}
```
以上两个类如果处于不同的编译单元中，是无法得到正确结果的，就是由于无法确定两个编译单元的初始化顺序。
解决方式是：将每个非本地的静态对象（non-local static）搬到自己的专属函数内，声明为static，返回一个reference，指向它所含的对象。（在类的声明和调用之间加一层，没有什么是加一层解决不了的:）
``` c++
//one.cpp
class FileSystem {
public:
    std::size_t numDisks() const;
};

extern FileSystem tfs;

//这个函数用来替代tfs对象
FileSystem& tfs() {     
    static FileSystem fs;   //在调用函数的单元中定义并初始化一个local static对象
    return fs;      //然后返回一个指向上述对象的引用
}

//another.cpp
class Directory {
public:
    Directory(params);
};

Directory::Directory(params) {
    std::size_t disks = tfs().numDisks();       //改为调用tfs()返回的引用对象
}

Directory& tempDir() {      //用于其他编译单元调用本对象
    static Directory td;    
    return td;
}
```

==总结==
- **为内置型对象进行手动初始化，因为C++不保证它们的初始化**。
- **构造函数最好使用初始化列表的方式，而不是在构造函数本体内使用赋值操作。初始化列表中列出的成员变量，最好其排列顺序和声明次序相同**。
- **为免除“跨编译单元的初始化次序”问题，用local static对象来替换non-local static对象**。

## 了解C++默默编写并调用哪些函数
对于创建的一个类，如果没有自己声明对应的函数，则编译器会自动声明（编译器版本）一个拷贝构造函数、一个拷贝赋值操作符函数、一个析构函数，如果没有声明任何构造函数，还会声明一个default构造函数，且这些函数权限都是public的。
> 需要注意的是，默认生成的拷贝函数只会进行浅拷贝；默认生成的赋值操作会拒绝对类的引用成员或const成员进行修改。

## 若不想使用编译器自动生成的函数，就应该明确拒绝
- **将不需要的函数声明为private，可以防止编译器自动生成，但这种方法是不安全的,因为成员函数和友元函数仍可能错误地使用到**；
- **把不需要的函数声明在一个基类的private中，然后继承这个基类是一种更好的做法**。

> C++11以后可以使用**delete**关键字来标记不会使用的函数。

## 为多态基类声明virtual析构函数
当派生类对象经由一个基类对象的指针被析构时，如果基类的析构函数不是virtual的，往往会产生错误——结果是未定义的，实际执行时通常发生的是对象的基类部分被析构了，而派生部分且没被销毁，于是造成“局部销毁”，使得资源泄露、破坏数据机构、调试时浪费大量时间等。
virtual函数的实现需要对象必须携带一些信息，决定在运行期调用哪一个virtual函数。这份信息通常由一个虚函数指针（vptr）来指出，vptr指向一个由函数指针构成的数组，称为虚表（virtual table）；每一个虚函数的类都有一个对应的虚表，当对象调用某一个virtual函数，实际上被调用的函数取决于该对象的vptr所指向的那个虚表——编译器在其中寻找适当的函数指针。
析构函数的运作方式是，最深层派生的类其析构函数会被先调用，然后是其每一个基类的析构函数。
> 对于定义为virtual的析构函数，派生类的虚表中，派生类的析构函数地址和其父类的析构函数地址是在同一个位置，也就是说，是嵌套的关系，所以在析构派生类对象时，会首先进入这个派生类的析构函数中，然后调用父类的析构函数析构掉父类，再析构掉派生类的部分。

``` c++
#include <iostream>
using namespace std;

class A {
    int a;
public:
    A(): a(1) {
        cout << "A construct" << endl;
    }

    void foo() {
        cout << "A foo" << endl;
    }

    virtual ~A() {
        cout << "A destory" << endl;
    }
};

class AA: public A {
public:
    AA() {
        cout << "AA construct" << endl;
    }

    void foo() {
        cout << "AA foo" << endl;
    }

    virtual ~AA() {
        cout << "AA destory" << endl;
    }
};

int main()
{
    AA aa;
    aa.foo();   //子类会覆盖父类的相同函数
    return 0;
}

/* 结果
A construct
AA construct
AA foo
AA destory
A destory
*/
```

==总结==
- **带有多态性质的基类应该声明一个virtual析构函数，如果class带有任何的virtual函数，他就应该拥有一个virtual析构函数**。
- **如果类的设计目的不是作为基类使用，或者不是为了具备多态性，就不该声明virtual析构函数**。

## 别让异常逃离析构函数
- **析构函数绝对不要吐出异常。如果一个被析构函数调用的函数可能抛出异常，析构函数应该捕捉任何异常，然后吞下它们（不传播）或结束程序**。
- **如果客户需要对某个操作函数运行期间抛出的异常作出反应，那么class应该提供一个普通函数（而不是在析构函数中）执行该操作**。

## 绝不在构造和析构过程中调用virtual函数
因为在派生类对象的构造过程中，基类的成分会在派生类自身成分之前被构造出来，所以如果在构造函数中调用了virtual函数，调用的就会是基类的版本，甚至有可能是一个纯虚函数（如果是纯虚函数反而还好，因为系统会直接中止程序；一旦调用的是有过实现的虚函数版本，程序会继续运行，但会让你困惑为什么调用了错误的版本，这更令人痛苦），这显然是不正确的。
同样的道理也适用于析构函数。

## 令operator= 返回一个reference to *this
这一条款主要是可以满足链式编程的需要。
```c++
int x, y, z;
x = y = z = 15; //赋值连锁形式
//等价于
x = (y = (z = 15));
//因此类也应该尽量满足这种编写习惯的要求，在赋值后返回本身
```

## 在operator= 中处理“自我赋值”
``` c++
class Bitmap;
class Wideget {
private:
    Bitmap* pb;

public:
    Widget& operator= (const Widget &rhs) {
        delete pb;      //释放掉自己原有的指针
        pb = new Bitmap(*rhs.pb);   //重新指向参数的内容
        return *this;
    }
};
```
如果rhs就是自身的话，上述的赋值操作就会释放掉参数中的相关对象，使得指针指向了一个被删除的对象，这是明显错误的。
为阻止这种错误，就会通过一个“认同测试”来达到“自我赋值”的目的：
``` c++
Widget& Widget::operator= (const Widget &rhs) {
    if(this == &rhs) 
        return *this;   //认同测试
    
    delete pb;
    pb = new Bitmap(*rhs.pb);
    return *this;
}
```
另一种方法：**让operator=具备“异常安全性”往往自动获得“自我赋值安全”的回报**，也就是说，再复制pb所指的东西前，不要先删除pb；
``` c++
Widget& Widget::operator= (const Widget &rhs) {
    Bitmap* pOrig = pb;     //记住原先的pb
    pb = new Bitmap(*rhs.pb);
    delete pOrig;   //删除原来的pb
    return *this;
}
```
还有一种常见又够好的的方法是，生成一份参数的副本，然后和*this进行交换，虽然牺牲了一些清晰性，但将复制的动作从函数体内移动到函数参数构造阶段，可以令编译器生成更高效的代码。

==总结==
- **确保当对象自我赋值时 operator=有良好的行为。其中技术包括比较“来源对象”和“目标对象”的地址，精心周到的语句顺序，以及copy-and-swap**。
- **确定任何函数如果操作一个以上的对象，而其中多个对象是同一个对象时，其行为仍然正确**。

## 复制对象时勿忘其每一个成分
对于自定义的copying函数一定要当心，因为编译器不会对自定义的copying函数结果是否正确进行检查。
- **copying函数应该确保复制“对象内的所有成员变量”及“所有base class成分”**。
- **不要尝试以某个copying函数实现另一个copying函数。应该将通用的部分放进第三个函数中，并由两个copying函数共同调用**。

## 以对象管理资源
把资源放进对象内，就可以依赖C++的“析构函数自动调用机制”确保资源被释放。
- **为防止资源泄露，应该使用RAII对象，在构造函数中获得资源并在析构函数中释放资源**。
- **C++11以后引入了智能指针，能够一定程度帮助解决资源泄露问题**。

## 在资源管理类中小心coping行为
- **复制RAII对象必须一并复制它所管理的资源，所以资源的coping行为决定RAII对象的coping行为**。
- **普遍而常见的RAII class coping行为是，抑制coping、施加引用计数法。不过其他行为也都可能被实现**。

## 在资源管理类中提供对原始资源的访问
- **APIs往往要求访问原始资源，所以每一个RAII class应该提供一个“取得其所管理的资源”的方法**。
- **对原始资源的访问可能经由显示转换或隐式转换。一般而言，显示转换比较安全，但隐式转换对客户比较方便。

## 成对使用new和delete时要采取相同形式
- **如果在new表达式中使用[ ]，必须在相应的delete表达式中也使用[ ]。

## 以独立语句将newed对象置入智能指针
在C++中，对于一行语句，其执行次序是不明确的，所以如果将多个调用放在一句中，可能会导致不易察觉的错误，尤其是涉及资源管理类时。
- **以独立语句将newed对象存储于智能指针内。如果不这样做，一旦异常被抛出，有可能导致难以察觉的资源泄露。**

## 让接口容易被正确使用，不易被误用
- **好的接口很容易被正确使用，不容易被误用。应该在所有接口中努力达成这些性质**。
- **“促进正确使用”的办法包括接口的一致性，以及与内置类型的行为兼容**。
- **“阻止误用”的办法包括建立新类型、限制类型上的操作，束缚对象值，以及消除客户的资源管理责任**。

## 设计class犹如设计type
好的type应该有着自然的语法、直观的语义，以及一或多个高效实现品。
设计高效的classes，必须面对以下的提问，这些问题会导致你的设计规范：
1. **新type的对象应该如何被创建和销毁？** 这会影响到构造函数、析构函数、以及内存分配函数和释放函数的设计。
2. **对象的初始化和对象的赋值该有什么样的差别？** 决定了构造函数和赋值操作符的行为，及其间的差异。
3. **新type的对象如果以值传递，意味着什么？** copy构造函数定义了一个type的值传递该如何实现（是否会有深拷贝问题？）。
4. **什么是新type的“合法值”？** 这些数值集决定了你的class必须维护的约束条件，也就决定了成员函数所需要进行的错误检查工作。它也影响函数抛出的异常，以及函数异常明细列（很少使用）。
5. **新的type需要配合某个继承图系吗？** 如果有继承关系，就要考虑到继承对新类型的影响。
6. **新type需要什么样的转换？** 如果希望允许T1类型的对象可以隐式转换为T2类型的对象，就必须在T1类内写一个类型转换函数或在T2类内写一个可被单一实参调用的构造函数。如果只允许显式构造函数存在，就得写出专门负责执行转换的函数，且不得为类型转换操作符或者可被单一实参调用的构造函数。
```c++
class toint {
private:
    size_t val;

public:
    toint() = default;
    toint(int& v): val(v) {};   //单一实参调用的构造
    operator int() {
        return val;
    }
    toint& operator= (const int v) {
        val = v;
        return *this;
    }
};

int main()
{
    toint INT;
    INT = 42;   //调用operator=
    cout << INT << endl;    //隐式调用int(),等价于显示调用INT.operator int()
    int a = (int)INT;       //调用int(),等价于显示调用INT.operator int()
    cout << a << endl;
    toint INT2(INT);    //首先调用INT2的单实参构造，单实参应该是int类型，于是INT隐式转换成int类型
    cout << INT2 << endl;
    return 0;
}
```
7. **什么样的操作符和函数对此新type而言是合理的？** 这个问题答案决定class中会声明哪些函数，其中哪些是member函数。
8. **什么样的标准函数已更改驳回？** 不应在类中使用的标准函数可以声明为private。
9. **谁该取用新type的成员？** 决定成员的权限（private、protected、public），以及哪些classes或函数是友元（友元应该是尽量避免的，因为他会破坏类的封装）。
10. **什么是新type的“未声明接口”？** （不太理解）
11. **新type有多么一般化？** 定义的新type如果可以具有普遍的适应性，最好的方法应该是定义为一个模板类。
12. **是否真的需要一个新type？** 如须必要，勿增实体。

**Class的设计就是type的设计。在定义一个新type之前，请确定已经考虑过上述的问题**。

## 用pass-by-reference-to-const替换pass-by-value
以值传递可能是一种开销非常大的操作，尤其是对于自定义的对象（如果是内置数据类型，值传递开销比引用要小，因为引用传递使用的还是指针）。
- **尽量以引用传递替换以值传递。前者通常效率更高，且可避免切割问题**。
- **以上规则并不适用于内置类型，以及STL的迭代器和函数对象。对它们而言，以值传递反而更加合适**。

## 必须返回对象时，不要妄想返回其reference
**绝不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回pointer或reference指向一个local static对象而有可能同时需要多个这样的对象**。

## 将成员变量声明为private
- **切记将成员变量声明为private。这可赋予客户访问数据的一致性、可细微划分访问控制、允诺约束条件获得保证，并提供class作者以充分的实现弹性**。
- **protected并不比public更具封装性**。

## 宁以non-member、non-friend替换member函数
与直觉相悖的是，member函数带来的封装性比non-member函数要更低，所以，提供非成员函数的版本能有更大的包裹弹性，以及较低的编译相依性。

## 若所有参数都需要类型转换，请为此采用non-member函数
如果你需要为某个函数的所有参数（包括被this指针所指的那个隐喻参数）进行类型转换，那么这个函数必须是个non-member。

## 考虑写出一个不抛异常的swap函数
swap函数原本是STL的一部分，而后成为异常安全性编程的脊柱，以及用来处理自我赋值可能性的一个常见机制。
> 缺省情况下，会调用std::swap算法，只要你的模板类型T支持coping，这种方法通过临时变量进行交换，往往效率不高。

对于复杂的交换，使用交换指针的方式（pimp）效率会更高，所以需要对swap函数进行特化。
有效的做法是在类中声明一个swap函数，然后再在std的命名空间中写出一个std::swap（）的特化版本。
```c++
//针对Widget设计的类
class WidgetImpl {
private:
    //要存储的数据
    int a, b, c;
    std::vector<double> v;
};

class Widget {
public:     
    Widget(const Widget &rhs);
    Widget& operator= (const Widget &rhs) {
        //...
        *pImpl = *(rhs.pImpl);
        //...
        return *this;
    }

    //添加一个swap函数
    void swap(Widget &other) {
        using std::swap;
        swap(pImpl, other.pImpl);
    } 

private:
    WidgetImpl* pImpl;  //swap时用来交换的指针
};

namespace std {
    //std::swap的特化版本
    template<>
    void swap<Widget> (Widget &a, Widget &b) {
        a.swap(b);
    }
}
```
当调用到swap函数时，特化版本比模板的优先级更高，所以会调用std::swap的特化版本，进而实现class内部指针的交换。
但是，如果要实现一个自定义的swap模板函数，由于std命名空间禁止添加新的模板函数，所以需要声明一个非成员函数版本的swap，让它来调用成员函数版的swap。
- **当std::swap对你的类型效率不高时，提供一个swap成员函数，并确定这个函数不抛出异常**。
- **如果提供了一个member swap，也该提供一个non-member swap用来调用前者。对于classes，也请特化std::swap**。
- **调用swap时应针对std::swap使用using声明式，然后调用swap并不带任何“命名空间资格修饰”**。
- **为“用户定义类型”进行std templates全特化是好的，但千万不要尝试在std内加入某些对std而言全新的东西**。

## 尽可能延后变量定义式的出现时间
当定义了一个变量而其类型带有一个构造函数或析构函数时，当程序的控制流到达这个变量的定义式时，你就得承受构造成本；当离开其作用域时，就得承受析构成本，即使这个变量始终未被使用过，所以应该尽可能避免这种情况。
对于循环而言，需要具体分析：
> A方法定义于循环外，成本是：一个构造函数 + 一个析构函数 + n个赋值操作；
> B方法定义于循环内，成本是：n个构造函数 + n个析构函数

如果classes的一个赋值成本低于一组构造析构成本，则A的效率更高，否则B的做法更好。此外A使用的变量作用域更大，有时会对程序的可理解性和易维护性造成冲突。因此，一般采用B的方法，除非明确知道赋值成本比构造析构成本低，而且该部分代码是效率高度敏感的。
## 尽量少做转型动作
C++提供四种新式转型：const_cast<T>(expression)、dynamic_cast<T>(expression)、static_cast<T>(expression)、reinterpret_cast<T>(expression)。
- 如果可以，尽量避免转型，特别是在注重效率的代码中避免dynamic_cast。如果有个设计需要转型，试着发展无需转型的替代设计。
- 如果转型是必要的，试着将它隐藏于某个函数背后。客户随后可以调用该函数，而不需将转型放进他们自己的代码内。
- 宁可使用C++风格的转型，不要使用旧时转型。前者很容易辨识出来，而且也比较有着分门别类的职掌。

## 避免返回handles指向对象内部成分
对象的“内部”一般是指成员变量，但不被公开的成员函数也应该包括在其中。因此，也应该留心不要返回它们的句柄（handles），意味着你绝对不该令成员函数返回一个指针指向“访问级别较低”的成员函数。如果那么做，会使后者的实际访问级别提高到如同前者。
- **避免返回handles(包括引用、指针、迭代器)指向对象内部**。遵守这个条款可增加封闭性，帮助const成员函数的行为像个const，并将发生“虚吊号码牌”——指向的对象不存在，的可能性降至最低。

## 为“异常安全”而努力是值得的
满足“异常安全”的函数在抛出异常时需要满足两个条件：
1. 不泄露任何资源；
2. 不允许数据破坏。

异常安全函数提供以下三个保证之一：
- 基本承诺：如果异常被抛出，程序内的任何事物仍然保持在有效状态下。
- 强烈保证：如果异常被抛出，程序状态不改变。如果函数成功，就是完全成功，如果函数失败，程序会回复到“调用函数之前”的状态。
- 不抛掷保证：承诺绝不抛出异常，因为它们总是能够完成它们原先承诺的功能。

==总结==
- **异常安全函数即使发生异常也不会泄露资源或允许任何数据结构破坏。这样的函数区分为三种可能的保证：基本型、强烈型、不抛异常型**。
- **“强烈保证”往往能够以copy-and-swap实现出来，但“强烈保证”并非对所有函数都可实现或具备现实意义**。
- **函数提供的“异常安全保证”通常最高只等于其所调用之各个函数的“异常安全保证”中的最弱者**。

## 透彻了解内联的里里外外
内联函数通常一定被置于头文件内，因为大多数构建环境在编译过程中进行内联，而为了将一个“函数调用”替换为”被调用函数的本体”，编译器必须知道那个函数长什么样子。某些构建环境可以在link期完成内联，少数构建环境可在运行期完成内联。在大多数C++程序中，内联都是编译期行为。
inline关键字应该看作是对编译器的建议，也就是说一个看似inline的函数是否真的是inline，取决于你的构建环境，主要取决于编译器。编译器一般会拒绝将一个复杂的函数进行内联操作。大多数编译器提供了一个诊断级别：如果它们无法将你要求的函数内联，会给出一个警告。
- **将大多数inlining限制在小型、被频繁调用的函数身上。这可使日后的调用过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化**。
- **不要只因为function templates出现在头文件，就将它们声明为inline**。

## 将文件间的编译依存关系降至最低
也就是说，应该降低各个编译文件之间的耦合性，对于一个文件，其头文件中的内容被修改后，会导致每一个引入和使用这个文件的其他文件都得重新编译，这种连锁的编译往往是灾难性的。
所以更好的做法是“接口与实现分离”，将class分割为两个classes，一个提供结构，另一个负责实现该接口。（联系设计模式的依赖倒置原则——面向接口编程，而不要面向具体实现编程）。
这种分离的关键在于以“声明的依存性”替换“定义的依存性”：现实中让头文件尽可能自我满足，如果做不到，则让它与其它文件内的声明式（而非定义式）相依。
> **如果使用object references或object pointers可以完成任务，就不要使用objects**。
> **尽量以class声明式替换class定义式**。
> **为声明式和定义式提供不同的头文件**。这些文件必须保持一致性，如果有个声明式被改变了，两个文件都得改变。因此程序库客户应该总是#include一个声明文件而非前置声明若干函数，程序库作者也应该提供这两个头文件。
- **支持“编译依存性最小化”的一般构想是：相依于声明式，不要相依于定义式。基于此构想的两个手段是handles classes和interfaceclasses**。
- **程序库头文件应该以“完全且仅有声明式”的形式存在。这种做法不论是否涉及templates都适用**。

## 确定你的public继承塑膜出is-a关系
公开继承意味着“is-a（是一种）”的关系，如果你令class D以public形式继承class B，你便是告诉C++编译器说，每一个类型为D的对象同时也是一个类型为B的对象，反之不成立。意思是，B比D表现出更一般化的概念，而D比B表现出更特殊化的概念。
**is-a**并非是唯一存在于classes之间的关系。另两个常见的关系是**has-a**（有一个）和**is-implemented-in-terms-of**（根据某物实现出）。把这些相互关系误塑为is-a的关系是C++中常见的错误设计，所以在设计继承关系时，需要仔细思考甄别父类与子类间的关系。

- **“public继承”意味着is-a。适用于base classes身上的每一件事情一定也适用于derived classes身上，因为每一个derived class对象也都是一个base class对象**。

## 避免遮掩继承而来的名称
- **derived classes内的名称会遮掩base classes内的名称。在public继承下从来没有人希望如此**。
- **为了让被遮掩的名称再见天日，可使用using声明式或转交函数**。

## 区分接口继承和实现继承
public继承实际上可由两部分组成：函数接口继承或函数实现继承。
> 成员函数的接口总是被继承。
> 声明一个pure virtual函数的目的是为了让derived classes只继承函数接口。
> 声明简朴的非纯虚函数的目的，是为了让derived classes继承该函数的接口和缺省实现。也就是说，对于继承类来说，如果有必要你可以对继承而来的虚函数进行覆写，如果没有必要，你也可以退而使用父类的实现。
> 声明non-virtual函数的目的是为了令derived classes继承函数的接口及一份强制性实现。

- **接口继承和实现继承不同。在public继承之下，derived classes总是继承base class的接口**。
- **pure virtual函数只具体指定接口继承**。
- **非纯虚函数具体指定接口继承及缺省实现继承**。
- **non-virtual函数指定具体接口继承以及强制性实现继承**。

## 考虑virtual函数以外的其他选择
> 使用non-virtual interface手法，那是Template Method设计模式的一种特殊形式。它以public non-virtual成员函数包裹较低访问性的virtual函数。
> 将virtual函数替换为“函数指针成员变量”，这是Strategy设计模式的一种分解表现形式。
> 以std::function成员变量替换virtual函数，因而允许使用任何可调用物搭配一个兼容于需求的签名式。
> 将继承体系内的virtual函数替换为另一个继承体系内的virtual函数。这是Strategy设计模式的传统实现手法。

## 绝不重新定义继承而来的non-virtual函数

## 绝不重新定义继承而来的缺省参数值
> 对象的静态绑定是它在程序中被声明时所采用的类型。
> 对象的动态绑定则是指“目前所指对象的类型”，也就是说，动态类型可以表现出一个对象将会有什么行为。
``` c++
//一个用来描述几何形状的class
class Shape {
public:
    enum ShapeColor {Red, Green, Blue};
    //所有形状都必须提供一个函数，用来绘出自己
    virtual void draw(ShapeColor color = Red) const = 0;
};

class Rectangle : public Shape {
public:
    //赋予不同的缺省参数值，非常糟糕！
    virtual void draw(ShapeColor color = Green) const;
};

class Circle : public Shape {
public:
    virtual void draw(ShapeColor color) const;
    //注意：以上这么写则当客户以对象调用此函数，一定要指定参数值，因为静态绑定下这个函数并不从其base继承缺省参数值
    //但若使用指针或引用调用此函数，可以不指定参数值，因为动态绑定下这个函数会从其base继承缺省参数值
};

int main()
{
    Shape* ps;                      //静态类型为Shape*
    Shape* pc = new Circle;         //静态类型为Shape*
    Shape* pr = new Rectangle;      //静态类型为Shape*

    ps = pc;                        //ps的动态类型是Circle*    
    ps = pr;                        //ps的动态类型是Rectangle*
    pc->draw(Shape::Red);           //调用Circle::draw(Shape::Red)
    pr->draw(Shape::Red);           //调用Rectangle::draw(Shape::Red)
    pr->draw();                     //调用Rectangle::draw(Shape::Red)  
}
```
virtual函数是动态绑定的，而缺省参数值却是静态绑定，意思是你可能会在“调用一个定义于derived class内的virtual函数”的同时，却使用base class为它所指定的缺省参数值，如上述程序中的pr->draw()。
但不幸的是，pr的动态类型是Rectangle*，所以调用的是Rectangle的virtual函数，这是我们所预期的，但是Rectangle::draw函数的缺省参数值我们重新设定为了Green，但由于pr的静态类型是Shape*，所以这一调用的缺省参数值来自Shape class而非Rectangle class！所以这个函数的调用是非常诡异的，由Shape class和Rectangle class的draw声明式各出一半力。
所以：
- **绝对不要重新定义一个继承而来的缺省参数值，因为缺省参数值都是静态绑定，而virtual函数——你唯一应该覆写的东西——却是动态绑定的**。

## 通过复合塑模出has-a或“根据某物实现出”
- **复合的意义和public继承完全不同。复合是在类中包含另一个类**。
- **在应用域，复合意味着has-a。在实现域，复合意味着is-implemented-in-terms-of**。
## 明智而审慎地使用private继承
> private继承的规则：
> 1. 编译器不会自动将一个derived class对象转换为一个base class对象。
> 2. 由private base class继承而来的所有成员，在derived class中都会编程private属性。

private继承意味着只有实现部分被继承，接口部分应略去。如果D以private形式继承B，意思是D对象根据B对象实现而得，再没有其他内涵了。

- **private继承意味着is-implemented-in-terms-of。它通常比复合的级别低。但是当derived class需要访问protected base class的成员，或需要重新定义继承而来的virtual函数时，这么设计是合理的**。
- **和复合不同，private继承可以造成empty base最优化。这对致力于“对象尺寸最小化”的程序库开发者而言，可能更重要**。

## 明智而审慎地使用多重继承
> C++用来解析重载函数调用的规则：在看到是否有个函数可取用之前，C++首先确认这个函数对此调用是最佳匹配。找出最佳匹配函数后才检验其可取用性。
> 在多重继承中，不同基类中的同名函数有着相同的匹配程度，没有所谓的最佳匹配，所以其可用性也就从未被编译器审查。若一定要调用，就要指明调用的是哪一个基类中的函数。
> 另外，如果出现菱形继承，更是要命，因为继承类对同一个基类存在两份同名复制，这种情况下，就令它成为一个virtual base class。为了这样做，必须把所有直接继承自它的classes采用“virtual继承”。

从正确的观点来看，public继承应该总是virtual的。但是，virtual继承总会带来更大的体积，而且访问速度也会较慢。

- **多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual继承的需要**。
- **virtual继承会增加大小、速度、初始化（及赋值）复杂度等成本。如果virtual base classes不带任何数据，将是最具实用价值的情况**。
- **多重继承的确有正当用途。其中一个情节涉及“public继承某个Interface class”和“private继承某个协助实现的class”的两相组合**。

## 了解隐式接口和编译器多态
Templates及泛型编程，与面向对象有根本上的不同。在此世界中显式接口和运行期多态仍然存在，但重要性降低。反倒是隐式接口和编译器多态移到前头了。

- **classes和templates都支持接口和多态**。
- **对classes而言接口是显式的，以函数签名为中心。多态则是通过virtual函数发生于运行期**。
- **对templates参数而言，接口是隐式的，奠基于有效表达式。多态则是通过template具现化和函数重载解析发生于编译期**。

## 了解typename的双重意义
- **声明template参数时，关键字typename等于class**。
- **使用关键字typename标识嵌套从属类型名称；但不得在base class lists（基类列）或member initialization list（初始化列）内以它作为base class修饰符**。

## 学习处理模板化基类内的名称
- **可在derived class templates内通过“this->”指涉base class templates内的成员名称，或藉由一个明白写出的“base class资格修饰符”完成**。

## 将于参数无关的代码抽离templates
- **templates生成多个classes和多个函数，所以任何template代码都不该与某个造成膨胀的template参数产生相依关系**。
- **因非类型模板参数而造成的代码膨胀，往往可消除，做法是以函数参数或class成员变量替换template参数**。
- **因类型参数而造成的代码膨胀，往往可降低，做法是让带有完全相同二进制表述的具现类型共享实现码**。

## 运用成员函数模板接受所有兼容类型
- 使用成员函数模板生成“可接受所有兼容类型”的函数。
- 如果声明了member templates用于“泛化copy构造”或“泛化assignment操作”，你还是需要声明正常的copy构造函数和copy assignment操作符。

## 需要类型转换时请为模板定义非成员函数
- 当编写一个class template，而它所提供的“与此template相关的”函数支持“所有参数的隐式类型转换”时，请将那些函数定义为“class template内部的friend函数”。

## 请使用traits classes表现类型信息
traits并不是C++关键字或一个预先定义好的构件，它们是一种技术，也是一个C++程序员共同遵守的协议。这个技术的要求之一是，它对内置类型和用户自定义类型的表现必须一样好。
以iterator_traits为例，运作方式是，针对每一个类型IterT，在struct iterator_traits< IterT>内一定声明某个typedef名为iterator_category。这个typedef用来确认IterT的迭代器分类。
iterator_traits以两个部分实现上述所言。首先它要求每一个“用户自定义的迭代器类型”必须嵌套一个typedef，名为iterator_category，用来确认适当的卷标结构。例如deque的迭代器可随机访问，所以一个针对deque迭代器而设计的class看起来如下：
``` c++
template<...>   //省略了模板参数声明
class deque {
public:
    class iterator {
    public:
        typedef random_access_iterator_tag iterator_category;
        ...
    };
    ...
};
```
至于iterator_traits，只是鹦鹉学舌般地响应iterator class地嵌套式typedef：
```c++
template <typename IterT>
struct iterator_traits {
    typedef typename IterT::iterator_category iterator_category;
    ...
};
```
以上这种形式对于自定义地类型行得通，但对指针是行不通的，因为指针不能嵌套typedef。所以有iterator_traits的第二部分专门来处理指针。
为了支持指针迭代器，iterator_traits特别针对指针类型提供一个偏特化版本。由于指针的行径与random access迭代器类似，所以iterator_traits为指针指定的迭代器类型是：
```c++
template <typename IterT> 
struct iterator_traits<IterT*> {
    typedef random_access_iterator_tag iterator_category;
    ...
};
```
现在可以实现一个traits class了：
1. 确认若干你希望将来可取得的类型相关信息。
2. 为该信息选择一个名称。
3. 提供一个template和一组特化版本，内含你希望支持的类型相关信息。

使用一个traits class的方式：
1. 建立一组重载函数或函数模板，彼此间的差异只在于各自的traits参数。令每个函数实现码与其接收的traits信息相对应。
2. 建立一个控制函数或函数模板，它调用上述那些函数并传递traits class所提供的信息。

## 认识template元编程
Template metaprogramming（模板元编程）是编写template-based C++程序并执行于编译期的过程。也就是说，是以C++写成、执行于C++编译器内的程序。一旦TMP程序结束执行，其输出，也就是从templates具现出来的若干C++源码，便会一如往常地被编译。
TMP有两个厉害之处。第一，它让某些事情更容易。如果没有它，某些事情将是困难的，甚至是不可能的。第二，可将工作从运行期转移到编译期。这产生的明显好处在于，可以提前发现错误，以及可以使程序更加高效。代价则是编译时间变长了。
```c++
//在编译期计算阶乘
template<unsigned n>
struct Factorial {
    enum {value = n * Factorial<n - 1>::value};
};

template<>
struct Factorial<0> {
    enum{value = 1};
};

int main()
{
    std::cout << Factorial<5>::value;
}
```

- **TMP可将工作由运行期提前到编译期，因而得以实现早期错误侦测和更高的执行效率**。
- **TMP可被用来生成“基于政策选择组合”的客户定制代码，也可用来避免生成对某些特殊类型并不适合的代码**。

## 了解new-handler的行为
当operator new无法满足某一内存分配需求时，它会抛出异常。
当operator new抛出异常以反映一个未获满足的内存需求之前，它会先调用一个客户指定的错误处理函数，及所谓的new-handler。为了指定这个“用以处理内存不足”的函数，客户必须调用set_new_handler，那是声明于< new>的标准程序库函数:
```c++
namespace std {
    typedef void (*new_handler)();
    new_handler set_new_handler(new_handler p) thorw();
}
```

一个良好的new-handler函数必须做到以下事情:
1. 让更多内存可被使用。企图使operator new的下一次内存分配动作可能成功。实现此策略的一个做法是，程序一开始执行就分配一大块内存，然后当new-handler第一次被调用，将它们分配给程序使用。
2. 安装另一个new-handler。如果当前这个new-handler无法取得更多可用内存，或者它知道另外哪个new-handler有这个能力，就可以安装另外那个new-handler来替换自己（只要调用set_new_handler）。
3. 卸除new-handler。传递nullptr给set_new_handler，意指没有安装任何new-handler，则operator new会在内存分配不成功时抛出异常。
4. 抛出bad_alloc的异常。这样的异常不会被operator new捕获，从而会被传播到内存索求处。
5. 不返回。通常调用abort或exit。

C++不支持class专属的new-handlers，但可以自己实现出这种行为。只需令每一个class提供自己的set_new_handler和operator new即可。
```c++
class Widget {
public:
    static std::new_handler set_new_handler(std::new_handler p) throw();
    static void* operator new(std::size_t size) throw(std::band_alloc);
private:
    static std::new_handler currentHandler;
};

std::new_handler Widget::currentHandler = nullptr;    //静态成员需要在类外初始化

std::new_handler Widget::set_new_handler(std::new_handler p) throw() {
    std::new_handler oldHandler = currentHandler;
    currentHandler = p;
    return oldHandler;
}
```
最后，Widget的operator new做以下事情：
1. 调用标准的set_new_handler，告知Widget的错误处理函数。这会将Widget的new-handler安装为global new-handler。
2. 调用global operator new，执行实际的内存分配。如果分配失败，global operator new会调用Widget的new-handler，因为那个函数才刚被安装为global new-handler。如果global operator new最终无法分配足够内存，会抛出一个bad_alloc异常。在此情况下，Widget的operator new必须恢复原本的global new-handler，然后再传播该异常。为确保原本的new-handler总是能够被重新安装回去，Widget将global new-handler视为资源，运用资源管理对象防止资源泄露。
3. 如果global operator new能够分配足够一个Widget对象所用的内存，Widget的operator new会返回一个指针，指向分配所得。Widget析构函数会管理global new-handler，它会自动将Widget的operator new被调用前的那个global new-handler恢复回来。

```c++
class NewHandlerHolder {
public:
    explicit NewHandlerHolder(std::new_handler nh): handler(nh) {}
    
    ~NewHandlerHolder() {
        std::set_new_handler(handler);
    }

private:
    std::new_handler handler;
    NewHandlerHolder(const NewHandlerHolder&);  //阻止copying
    NewHandlerHolder& operator= (const NewHandlerHolder&);
};

//通过上面的资源管理类来实现operator new
void* Widget::operator new (std::size_t size) throw(std::bad_alloc) {
    NewHandlerHolder h(std::set_new_handler(currentHandler));   //安装Widget的new_handler
    return ::operator new(size);    //分配内存或抛出异常
}   //恢复global new-handler
```
于是，Widget的客户可以类似以下的方式使用其new-handling：
```c++
#include <new>

void OutofMem();    //函数声明，用于Widget对象分配失败时被调用

int main()
{
    Widget::set_new_handler(OutofMem);
    Widget* pw1 = new Widget;   //如果分配失败，调用outofmem
    std::string* ps = new std::string;  //如果内存分配失败，调用global new-handling函数（如果有的话）
    Widget::set_new_handler(nullptr);   //卸载new-handler
    Widget* pw2 = new Widget;   //如果内存分配失败，立刻抛出异常（因为此时class Widget并没有专属的new-handler函数）
}
```

- **set_new_handler允许客户指定一个函数，再内存分配无法获得满足时被调用**。
- **Nothrow new是一个颇为局限的工具，因为它只适用于内存分配；后继的构造函数调用还是可能抛出异常**。

## 了解new和delete的合理替换时机
可能会出于以下原因重载new或delete：
1. 为了检测运用错误。
2. 为了收集动态分配内存的使用统计信息。
3. 为了增加分配和归还的速度。
4. 为了降低缺省内存管理器带来的空间额外开销。
5. 为了弥补缺省分配器中的非最佳齐位。
6. 为了将相关对象成簇集中。
7. 为了获得非传统的行为。

## 编写new和delete时许固守常规
- operator new应该内含一个无穷循环，并在其中尝试分配内存，如果它无法满足内存需求，就该调用new-handler。它也应该有能力处理0bytes申请。Class专属版本则还应该处理“比正确大小更大的（错误）申请”。
- operator delete应该在收到null指针时不做任何事。Class专属版本则还应该处理“比正确大小更大的（错误）申请”。

## 写了placement new也要写placement delete
在C++中，可以详细将new分为三类，一个是new关键字，一个是operator new，还有一个是placement new。
new关键字也就是常说的new operator，和operator new的区别在于：
> new operator：指在编写C++代码时使用的关键字，如A* a = new A;
> operator new：是一个操作符，并且可以被重载。

对于`A* a = new A;`这句代码，实际上是发生了三个动作：
1. 调用operator neW(sizeof(A))分配内存。这一操作就是通过operator new(size_t)来完成。如果class A重载了operator new，那么就会调用A::operator new(size_t)，否则调用全局的::operator new(size_t)。
2. 调用class A的构造函数。
3. 返回分配的指针，并将其赋给a。

对于operator new有以下三种形式:
```c++
//失败时抛出异常std::bad_alloc
void* operator new(std::size_t size) throw(std::bad_alloc);

//失败时不刨出异常
void* operator new(std::size_t size, const std::nothrow_t &nothrow_value) throw();

//这就是所谓placement new，在ptr指定的位置进行内存分配
void* operator new(std::size_t size size, void* ptr) throw();

A* a = new A;   //调用第一种
A* a = new(std::nothrow) A;     //调用第二种
char buf[1024];
A* a = new(buf) A;      //调用第三种
```
与之相应的，在重载了placement new函数后，也应该明确地写出一个与之对应的placement delete函数。否则会导致内存的泄露。
另外，当声明了placement new和placement delete后，确保不要无意识地遮掩了它们的正常版本。

