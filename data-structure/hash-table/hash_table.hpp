/******************************************
 * @file		hash_table.hpp
 * @brief		散列表
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-03-17 11:43
 ******************************************/
#ifndef HASH_TABLE_H__
#define HASH_TABLE_H__

#include<vector>
#include<list>

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

template<typename Type>
inline size_t HashTable<Type>::myHash(const Type& x) const {
    static std::hash<Type> hf;
    return hf(x) % m_table.size();
}

template<typename Type>
inline HashTable<Type>::HashTable(int size) : m_table(size, {}) { }

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

#endif // !hash_table.hpp