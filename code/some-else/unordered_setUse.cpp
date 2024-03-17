#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>

using namespace std;

/*
假设有一个Person类，创建一个可存储Person类的unordered_set，由于Person不是默认存储类型，
需要自定义哈希函数和重载==
*/
class Person
{
public:
    Person(string name, int age):name(name),age(age){};
    string getName() const;
    int getAge() const;

private:
    string name;
    int age;
};

//自定义哈希函数
class hash_func
{
public:
    int operator() (const Person &a) const
    {
        return a.getAge();
    }
};

//重载==
    bool operator== (const Person &a, const Person &b)
    {
        return (a.getAge() == b.getAge());
    }

//还可以自定义比较规则，直接不用==
class mycmp
{
public:
    bool operator()(const Person &a, const Person &b) const
    {
        return((a.getAge() == b.getAge()) && (a.getName() == b.getName())); 
    }
};

int main()
{
    //使用自定义hash_func，比较规则选择equal_to<key>，前提重载了==
    unordered_set<Person, hash_func> myset1{{"zhangsan", 40}, {"zhangsan", 40},
                                                {"lisi", 40}, {"lisi", 30}};
    //使用自定义hash_func和mycmp比较规则
    unordered_set<Person, hash_func, mycmp> myset2 {{"zhangsan", 40}, {"zhangsan", 40},
                                                {"lisi", 40}, {"lisi", 30}};
    cout << "myset1:\n";
    for(auto iter = myset1.begin(); iter != myset1.end();iter++)
        cout << iter->getName() << " " << iter->getAge() << endl;
    cout << "myset2:\n";
    for(auto iter = myset2.begin(); iter != myset2.end(); iter++)
        cout << iter->getName() << " " << iter->getAge() << endl; 
    return 0;
}

string Person::getName() const
{
    return name;
}

int Person::getAge() const
{
    return age;
}