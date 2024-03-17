# 散列（hash）

散列是一种能够以常数平均时间执行插入、删除和查找的技术。但是散列无法做到元素间的有序。

## 基本想法

散列的基本想法就是将元素按照一定的规则处理后，映射到散列表中的某个位置，比如是0到tablesize - 1的某个数，这样就可以保证能够快速的找到元素位置。这种映射就叫做**散列函数**（哈希函数）。但是要保证任意两个不同的元素也能够被映射到不同的位置是几乎不可能实现的，因为在数学逻辑中，等于是将一个大的集合映射到一个小的集合中，两个不同大小的集合要实现一对一的映射关系是不可能的。
那么剩下的问题就是如果出现了冲突要怎么解决，以及如果来确定散列表的大小。

## 散列函数

最容易想到的散列函数莫过于直接使用元素值来和tablesize取模，但如果元素具有某些不理想的性质，就不是那么好了。比如tablesize取10，而元素恰好很多个位上是0，那么直接取模就是一个坏的选择。相对好的方法是控制表的大小是一个素数，例如tablesize取11，那对于上述的元素也可以很好的平均分配位置。
另外，如果元素是不可以直接运算的，比如是字符串类型，那么散列函数的设计就需要考虑更多的因素，比如可以取字符的ASCII码，或者用字符串的字符数量等等，但这些都不是很好的选择。写出一个散列函数并不难，但是写出一个好的散列函数其实是非常困难的。好的散列函数能做到的是尽可能**快而均匀**的将元素分配到散列表中。一个散列函数能被称为好的散列函数，一定是在某种使用场景下，结合了场景的特性设计出来的。

在c++11之后，散列函数可以使用模板对象来表示。
```c++
template<typename Key>
class hash {
public:
    size_t operator()(const Key& x) const;
};
```
这个模板提供了如`int`和`string`这种标准类型的默认实现，也可以通过重载来实现自定义的散列函数，例如：
```c++
template<>
class hash<std::string> {
public:
    size_t operator()(const std::string& key) {
        size_t hashVal = 0;
        for(char ch : key) {
            hashVal = 37 * hashVal + ch;
        }
        return hashVal;
    }
};
```

## 分离链接法

分离散列表是一种解决冲突的做法，其做法是将冲突的元素以链表的形式串起来，标准库中的`unordered_map`就是采用了这种方式。这种方式对空间的要求比较大，因为这些表双向链接且浪费空间，如果空间比较吃紧，那么最好还是不要使用这种形式。

![分离链接表](/images/chaining_hash_table.jpg)

为了执行一次搜索，先使用散列函数确定是在哪一个链表中，然后再在这个链表中执行一次遍历查找。执行插入时，也是先通过散列函数找到要插入的链表，并且检查是否已经有了该元素，如果没有那么就将这个新元素插入到开头位置。
> 为什么是开头位置？这是基于这样一种事实：往往新插入的元素最有可能在不久就被访问到。

```c++
template<typename Type>
class HashTable {
public:
    explicit HashTable(int size = 101);

    bool contains(const Type& x) const;

    void makeEmpty();

    bool insert(const Type& x);

    bool insert(Type&& x);

    bool remove(const Type& x);

private:
    bool rehash();

    size_t myHash(const Type& x) const;

private:
    std::vector<std::list<Type>> m_table;
    int m_size;
};
```
类型`size_t`是系统定义的无符号整型，用于表示对象的大小。因此，可用于存储数组的下标。通过调用散列函数对象生成一个`size_t`类型的值，然后换算成散列表适当的数组下标，正如`myHash`的实现所要做的。
```c++
template<typename Type>
inline size_t HashTable<Type>::myHash(const Type& x) const {
    static std::hash<Type> hf;
    return hf(x) % m_table.size();
}
```
下面要实现散列表的插入和移除等操作，首要的前提是元素必须支持相等运算符操作(operator==)，因为散列表的插入和删除操作都需要判断当前的元素是否存在。
```c++
template<typename Type>
inline bool HashTable<Type>::contains(const Type& x) const {
    auto& which_list = m_table[myHash(x)];
    return std::find(which_list.begin(), which_list.end(), x) != std::end(which_list);
}

template<typename Type>
inline void HashTable<Type>::makeEmpty() {
    for(auto list : m_table) {
        list.clear();
    }
}

template<typename Type>
inline bool HashTable<Type>::insert(const Type& x) {
    auto& which_list = m_table[myHash(x)];
    if(std::find(which_list.begin(), which_list.end(), x) == std::end(which_list)) {
        return false;
    }
    which_list.push_back(x);
    if(++m_size > m_table.size()) {
        rehash();
    }
    return true;
}

template<typename Type>
inline bool HashTable<Type>::remove(const Type& x) {
    auto& which_list = m_table[myHash(x)];
    auto iter = std::find(which_list.begin(), which_list.end(), x);
    if(iter == std::end(which_list)) {
        return false;
    }
    which_list.erase(iter);
    --m_size;
    return true;
}
```

除了使用链表外，也可以使用其他的合理的方案来解决冲突，比如一棵树甚至是另一个散列表都可。不过我们期望的是，如果散列表足够大，而散列函数又是好的，那么每个链表都是比较短的，也就没有必要再去尝试复杂的手段了。
散列表中定义了一个概念叫做负载因子（load factor），表示散列表中的元素个数和该表大小的比值。如果我们将其记作是λ，那么每条链表的平均长度为λ，执行一次查找的代价就是计算散列函数值的常数时间加上遍历对应链表的时间，一次失败的查找平均需要遍历的就是λ个节点，一次成功的查找则平均需要遍历1+(λ/2)个节点。于是能够得到这样的结论，*散列表的大小其实并不重要，重要的是负载因子*。在分离链接法的散列表中的一般做法都是将表的大小大致和元素的个数差不多(即让λ≈1)，当负载因子超过了1时，就执行一次`rehash`的过程，扩大散列表的大小。

## 不使用链表的散列表

分离链接法的缺点在于使用到了一些链表，而链表在给新元素分配地址时是需要相对较长时间的，这就拖慢了散列表的速度。另外一种不使用链表解决冲突的方式是尝试表中的另外的一些单元，直到找到一个空的单元为止，例如对于表中单元h<small>0</small>(x),h<small>1</small>(x),h<small>2</small>(x) ...,相继被尝试，其中h<small>i</small>(x) = (hash(x) + f(i)) mod tablesize, `f(i)`是解决冲突的方法。这种表称作*探测散列表*，一般来说，这种表的所需大小要比分离链接散列表大，其负载因子λ应该低于0.5。

### 线性探测法

顾名思义，线性探测法就是解决冲突的方法`f`是i的线性函数，最典型的就是`f(i)=i`，相当于在出现冲突是，依次尝试下一个单元以找出一个空的单元。但是这样做并不是一个好办法，首先是依次遍历的耗时较多，更糟糕的是，采用这种方法容易导致即使表比较空，仍会使数据相对集中到一个区域，称为`一次聚集`。

### 平方探测法

平方探测法是为了消除线性探测法中一次聚集问题的冲突解决方法，即冲突解决函数`f(i)`是以平方的形式进行探测。

### 双散列

## 再散列(rehash)

## 常数时间访问的散列表

## 通用散列

## 磁盘上的散列