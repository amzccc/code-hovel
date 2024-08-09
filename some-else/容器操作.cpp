#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <list>
#include <forward_list>
#include <map>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

class Person
{
private:
    int age;
    std::string name;
public:
    Person(std::string name, int age):name(name),age(age){};
    int getAge() const
    {
        return age;
    }
    //重载==和<
    friend bool operator< (const Person &a, const Person &b)
    {
        return (a.name < b.name);
    }

    friend bool operator== (const Person &a, const Person &b)
    {
        return (a.name == b.name);
    }
};

//自定义哈希函数
class myhash
{
public:
    int operator() (const Person &a)
    {
        return a.getAge();
    }
};

int main()
{
    using namespace std;
    int n, elem;

    //*******************************************************************
    //动态数组vector
    //创建初始化
    vector<int> vec;     //初始化，内容为空
    vector<int> v2(vec); //v2是v1的副本
    vector<int> v3(n, elem);   //v3包含了n个i；
    vector<int> v4(n);      //v4包含了n个0；
    vector<int> v5(vec.begin(), vec.end());     //利用迭代器初始化
    //常用函数
    //iterator操作
    vec.begin();     //返回vector的首元素地址  cbegin/rbegin/crbegin
    vec.end();       //返回vector的末元素的下一个元素的地址  cend/rend/crend
    //capacity容量
    vec.empty();     //判断vector是否为空，空返回true
    vec.size();     //返回vector中元素个数
    vec.max_size();     //返回vector可容纳的最大元素数
    vec.resize(n);     //调整vector大小，使其包含n个元素
    vec.capacity();     //返回当前为vector分配的空间大小，以元素数表示
    vec.reserve(n);     //要求vector至少包含n个元素
    vec.shrink_to_fit();    //要求vector减小其容量以适应其大小
    //元素访问
    vec.at(n);      //返回n处元素的引用，与下标操作符不同，at函数会检查是否越界，超出则抛出out_of_range异常
    vec.front();    //返回vector的第一个元素
    vec.back();     //返回vector的最后一个元素
    vec.data();     //返回指向vector第一个元素的指针
    //内容修改
    vec.assign(10,100);     //将新内容分配给vector，替换当前内容，并相应修改大小（给vec10个100）    
                            //assign(it.b(), it.e())    assign(initializer_list<> il)
    vec.push_back(1);   //将数据插入vector末尾
    vec.pop_back();     //删除vector最后一个元素
    vector<int>::iterator pos = vec.begin();
    vec.insert(pos, elem);     //在pos前插入元素elem,返回指向新添加元素的迭代器    
                                //inser(pos, n, elem)     insert(pos, b, e)     insert(pos, il)
    vec.swap(v2);       //交换两vector所有元素      swap(v2, v3);
    vec.erase(pos);     //移除一个或一段元素    erase(it.b, it.e)
    vec.clear();     //清空vector    
    vec.emplace(pos, 10);     //指定位置直接调用构造函数生成一个元素 emplace(p, args) args是构造函数参数
    vec.emplace_back(10);      //在尾部构造生成一个元素
    //遍历方式
    //支持下标遍历和迭代器遍历


    //*******************************************************************
    //双端队列deque
    //deque基本与vector一样使用，但增加了前向的操作
    deque<int> deq;
    deq.push_front(elem);
    deq.pop_front();


    //*********************************************************************
    //list
    //创建初始化 同vector
    list<int> li;       //创建空list
    list<int> li2(li);       
    //基本操作同vector
    li.push_front(elem);    //在头部添加一个元素    list支持头部插入和删除
    li.emplace_front(pos, 10);
    li.pop_front();     //删除头部元素
    li.merge(li2);      //合并list
    li.reverse();       //把list列表倒转
    li.unique();        //删除list中的重复元素
    //list不支持下标操作


    //*****************************************************************
    //单向列表forward_list
    forward_list<int> fli;
    //单向列表不能向前查找，因此没有list的前向操作
    forward_list<int>::iterator it = fli.begin();
    fli.insert_after(it, elem);    //forward_list只能向后插入，不能向前插入
    fli.emplace_after(it, 10);      //向后构造
    fli.erase_after(it);        //向后删除


    //*******************************************************************
    /*适配器
    stack<T>是一个默认封装了deque容器的适配器模板，默认实现的是后入先出的压入栈
                也可以用vector和list作为容器；
    queue<T>是一个默认封装了deque容器的适配器模板，默认实现的是先入先出的队列
                也可以使用list作为容器；
    priority_queue<T>是一个封装了vector容器的适配器模板，默认实现的是一个会对元素排序，保证最大元素总在队列最前面的队列
                也可以使用deque作为容器；
    */
    //栈stack
    stack<int, vector<int>> stk;    //可以把容器作为第二个参数来重载默认容器类型
    stk.empty();        //stack是否为空
    stk.size();         //返回stack中元素数目
    stk.emplace(pos, 10);   //构造元素
    stk.push(elem);       //压入栈
    stk.top();      //返回栈顶元素，但不将元素弹出栈***
    stk.pop();      //删除栈顶元素，但不返回该元素***


    //队列queue
    queue<int> q;
    q.empty();
    q.size();
    q.push(elem);   
    q.emplace(pos, 10);
    q.pop();        //删除queue的首元素，但不返回该元素***
    q.front();      //返回首元素，但不删除***
    q.back();       //返回尾元素，但不删除
    

    //优先级队列priority_queue
    priority_queue<int> pq;
    pq.empty();
    pq.size();
    pq.push(elem);
    pq.emplace(pos, 10);
    pq.top();       //返回最高优先级元素，但不删除***
    pq.pop();       //删除最高优先级元素，但不返回***


    //******************************************************************
    //关联容器map set
    /*
    有序：基于红黑树
    map:保存键值对                      set：只保存关键词
    multimap:关键词可重复的map          multiset:关键词可重复的set
    
    无序：基于哈希函数
    unordered_map:哈希函数组织的map；   unordered_set:哈希函数组织的set
    unordered_multimap:关键词可重复     unordered_set:关键词可重复
    */
    //map
    map<string, int> mp;
    map<string, int> mp2 = {{"a", 1}, {"b", 2}, {"c", 3}};  //利用初始化列表
    map<string, int> mp3 = {pair<string, int>("a", 1), make_pair("b", 2)};  //利用pair结构和make_air函数
    mp.insert(make_pair("d", 4));       //向map插入元素
    mp.insert(mp2.begin(), mp2.end());      //利用迭代器插入
    mp["e"] = 5;        //map可以用下标操作
    mp.erase("a");      //删除关键词为a的元素，返回一个size_type值，表示删除的数目
    map<string, int>::iterator p;
    mp.erase(p);        //删除迭代器p指向的元素，并返回指向p之后元素的迭代器
    mp.erase(mp.begin(), mp.end());
    mp.find("k");       //返回指向第一个关键词为k的迭代器，没有返回尾后迭代器
    mp.count("k");      //返回关键词等于k的元素数目
    mp.lower_bound("k");    //返回指向第一个关键词不小于k的元素的迭代器,只适用有序关联容器
    mp.upper_bound("k");    //大于
    mp.equal_range("k");    //等于
    p->first;       //返回迭代器指向的元素的关键词
    p->second;      //返回迭代器指向的元素的值


    //无序map
    unordered_map<string, int> ump;
    ump.bucket_count();     //正在使用的桶的数目
    ump.max_bucket_count();     //容器能容纳的最多的桶的数目
    ump.bucket_size(n);      //第n个桶中有多少个元素
    ump.bucket("k");        //关键词为k的元素在哪个桶
    unordered_map<string, int>::local_iterator lit;     //可以用来访问桶中元素的迭代器类型
    ump.begin(n);       //桶n的首元素迭代器
    ump.load_factor();      //每个桶的平均元素数量，返回float值
    ump.max_load_factor();      //试图维护的平均的桶的大小，返回float值。ump会在需要时添加新的桶，使load_factor <= max_load_factor
    ump.rehash(n);      //重组存储，使bucket_count >= n,且bucket_count > size / max_load_factor
    ump.reserve(n);     //重组存储，使ump可以保存n个元素且不必rehash

    //在使用map和set保存自定义的类时，需要自定义比较器，如果是无序容器还需要自定义哈希函数
    //即有序容器需要重载<或者>, 无序容器需要重载==和自定义哈希函数，重载的参数必须为const
    //例如存储自定义的Person类
    map<Person, int> mymp{pair<Person, int>({"zhangsan", 10}, 1), pair<Person, int>({"lisi", 20},2)};
    unordered_map<Person, int, myhash> myump{pair<Person, int>({"zhangsan", 30}, 3), pair<Person, int>({"lisi", 40},4)};


    //*****************************************************************************************
    //string
    //构造方法
    string s;
    string str();       //空白字符
    string str(const char& str);       //拷贝初始化
    string str(const char *s);      //数组字符赋值
    string str(int n, char c);      //使用n个字符c初始化
    //重载了=
    //string& operator=(const char *s);
    //string& operator=(const string &s);	    //字符串赋值
    //string& operator=(char c);	    //字符赋值
    string& assign(const char *s);	    //字符数组赋值
    string& assign(const char *s, int n);	//字符数组前n个赋值
    string& assign(const string &s);	//字符串赋值
    string& assign(int n, char c);	    //n个字符赋值
    string& assign(const string &s, int start, int n);	    //字符串从start位到n个赋值
    //操作方法
    //os << s       //写入os流并返回os
    //is << s
    //getline(is, s);     //从is中读取一行给s，返回is
    //s[n];       //返回string的第n个字符
    //s = s1 + s2;    //拼接字符串
    //重载了=、 +、 ==、 !=、<、<=、>=、>等比较
    //重载了+=
    // string& operator+=(const char* str); //重载+=操作符
    // string& operator+=(const char c); //重载+=操作符
    // string& operator+=(const string& str); //重载+=操作符
    // string& append(const char *s); //把字符串s连接到当前字符串结尾
    // string& append(const char *s, int n); //把字符串s的前n个字符连接到当前字符串结尾
    // string& append(const string &s); //同operator+=(const string& str)
    // string& append(const string &s, int pos, int n); //字符串s中从pos开始的n个字符连接到字符串结尾
    //查找操作
    int find(const string& str, int pos = 0) ; //查找str第一次出现位置，从pos开始查找
    int find(const char* s, int pos = 0) ; //查找s第一次出现位置，从pos开始查找
    int find(const char* s, int pos, int n) ; //从pos位置查找s的前n个字符第一次位置
    int find(const char c, int pos = 0) ; //查找字符c第一次出现位置
    int rfind(const string& str, int pos = 0) ; //查找str最后一次位置，从pos开始查找
    int rfind(const char* s, int pos = 0) ; //查找s最后一次出现位置，从pos开始查找
    int rfind(const char* s, int pos, int n) ; //从pos查找s的前n个字符最后一次位置
    int rfind(const char* c, int pos = 0) ; //查找字符c最后一次出现位置
    //替换
    string& replace(int pos, int n, const string& str); //替换从pos开始n个字符为字符串str
    string& replace(int pos, int n, const char* s); //替换从pos开始的n个字符为字符串s
    //插入和删除
    string& insert(int pos, const char* s); //插入字符串
    string& insert(int pos, const string& str); //插入字符串
    string& insert(int pos, int n, char c); //在指定位置插入n个字符c
    string& erase(int pos, int n = 0); //删除从pos开始的n个字符
    //子字符串
    string substr(int pos=0, int n = 0); //返回由pos开始的n个字符组成的字符串
    //转换为c风格
    const char *cstr = s.c_str();

    //容器内类型        以vector为例
    vector<string>::value_type;     //获得容器元素类型  关联容器map获得的是pair类型
    vector<string>::reference;      //获得元素的引用类型
    vector<int>::pointer;       //指向元素的指针
    vector<char>::size_type;     //表示容器大小，无符号整型
    vector<double>::difference_type;       //带符号整型，用来定义距离
    //关联容器内
    map<int, char>::key_type;       //key的类型
    map<int, char>::mapped_type;    //value的类型
    map<int, char>::key_compare;    //获得关联容器比较准则的类型
    map<int, char>::value_compare;   //整个元素的比较准则的类型，map中仅比较两元素的key
    unordered_map<int, char>::hasher;   //获得hashing函数的类型
    unordered_map<int, char>::local_iterator;   //获得无序容器内bucket迭代器的类型
    vector<char>::allocator_type;     //获得分配器类型
}


