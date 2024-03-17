#include <iterator>

/*
迭代器5种类型：           功能                      提供者
Output迭代器：          向前写入                    Ostream inserter
Input迭代器             向前读取一次                Istream
Forward迭代器           向前读取                    Forward_list  unordered_container   
Bidirectional迭代器     双向读取                    List  set  multiset  map  multimap
Random-access迭代器     随机读取                    Array  vector  deque  string  C-style array
*/

//自定义一个关联容器和无序容器的插入迭代器
template<typename T>
class asso_insert_iterator
    : public std::iterator<std::output_iterator_tag, typename T::value_type>
{
protected:
    T& container;
public:
    explicit asso_insert_iterator(T& c): container(c){};
    asso_insert_iterator<T>& operator = (const typename T::value_type& value) {
        container.insert(value);
        return *this;
    }
    asso_insert_iterator<T>& operator * () {
        return *this;
    }
    asso_insert_iterator<T>& operator ++ () {
        return *this;
    }
    asso_insert_iterator<T>& operator ++ (int) {
        return *this;
    }
};

template <typename T>
inline asso_insert_iterator<T> asso_inserter (T& c)
{
    return asso_insert_iterator<T> (c);
}