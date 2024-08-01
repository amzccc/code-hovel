#include <iostream>

using std::cout;
using std::endl;

// 默认的策略
class DefaultPolice1 {
public:
    void operator()() {
        cout << "default police1\n";
    }
};

class DefaultPolice2 {
public:
    void operator()() {
        cout << "default police2\n";
    }
};
class DefaultPolice3 {
public:
    void operator()() {
        cout << "default police3\n";
    }
};
class DefaultPolice4 {
public:
    void operator()() {
        cout << "default police4\n";
    }
};

class DefaultPolices {
public:
    using P1 = DefaultPolice1;
    using P2 = DefaultPolice2;
    using P3 = DefaultPolice3;
    using P4 = DefaultPolice4;
};

// 使用虚继承，无论继承多少次都只会有一份数据
class DefaultArgs : virtual public DefaultPolices { };

// CRTP 策略设置的包装类，使得Selector可以继承多个相同策略类
template<typename Setter, int>
class SetterWrapper : public Setter { };

template<typename Setter1, typename Setter2, typename Setter3, typename Setter4>
class Selector : public SetterWrapper<Setter1, 1>,
    public SetterWrapper<Setter2, 2>,
    public SetterWrapper<Setter3, 3>,
    public SetterWrapper<Setter4, 4> { };

// 最终的产物，使用UseNamedTemplateArgs::Policies::xxx指定使用的策略
template<typename PolicySetter1 = DefaultArgs,
    typename PolicySetter2 = DefaultArgs,
    typename PolicySetter3 = DefaultArgs,
    typename PolicySetter4 = DefaultArgs>
class UseNamedTemplateArgs {
public:
    using Polices = Selector<PolicySetter1, PolicySetter2, PolicySetter3, PolicySetter4>;
};

// 定义一些模板来覆盖默认值
template<typename Police>
class Police1is : public DefaultArgs {
public:
    using P1 = Police;
};

template<typename Police>
class Police2is : public DefaultArgs {
public:
    using P2 = Police;
};

template<typename Police>
class Police3is : public DefaultArgs {
public:
    using P3 = Police;
};

template<typename Police>
class Police4is : public DefaultArgs {
public:
    using P4 = Police;
};

class CustomPolicy {
public:
    void operator()() {
        cout << "custom police\n";
    }
};

int main() {
    UseNamedTemplateArgs<Police1is<CustomPolicy>>::Polices::P1()();
    UseNamedTemplateArgs<Police1is<CustomPolicy>>::Polices::P2()();
    UseNamedTemplateArgs<Police1is<CustomPolicy>>::Polices::P3()();
    UseNamedTemplateArgs<Police1is<CustomPolicy>>::Polices::P4()();
    cout << "-------------------------------\n";
    UseNamedTemplateArgs<Police2is<CustomPolicy>>::Polices::P1()();
    UseNamedTemplateArgs<Police2is<CustomPolicy>>::Polices::P2()();
    UseNamedTemplateArgs<Police2is<CustomPolicy>>::Polices::P3()();
    UseNamedTemplateArgs<Police2is<CustomPolicy>>::Polices::P4()();
    cout << "-------------------------------\n";
    UseNamedTemplateArgs<Police3is<CustomPolicy>>::Polices::P1()();
    UseNamedTemplateArgs<Police3is<CustomPolicy>>::Polices::P2()();
    UseNamedTemplateArgs<Police3is<CustomPolicy>>::Polices::P3()();
    UseNamedTemplateArgs<Police3is<CustomPolicy>>::Polices::P4()();
    cout << "-------------------------------\n";
    UseNamedTemplateArgs<Police4is<CustomPolicy>>::Polices::P1()();
    UseNamedTemplateArgs<Police4is<CustomPolicy>>::Polices::P2()();
    UseNamedTemplateArgs<Police4is<CustomPolicy>>::Polices::P3()();
    UseNamedTemplateArgs<Police4is<CustomPolicy>>::Polices::P4()();

    return 0;
}