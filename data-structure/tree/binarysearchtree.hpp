/******************************************
 * @file		binarysearchtree.h
 * @brief		二叉搜索树
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-02-22 22:43
 ******************************************/
#ifndef BINARYSEARCHTREE_H__
#define BINARYSEARCHTREE_H__

#include "binarytree.hpp"

/**
 * @brief 二叉搜索树     
 * 对于树中的每个节点，左子树的值都小于当前节点的值，右子树的值都大于当前节点的值
 *
 * @tparam T 二叉搜索树存储的值的类型
 */
template<typename T>
class BinarySearchTree : private BinaryTree<T> {
public:
    enum class Order : char {
        pre,
        middle,
        post
    };

    virtual ~BinarySearchTree() = default;

    void insert(const T& val);

    void insert(T&& val);

    void remove(const T& val);

    void printTree(std::ostream& out = std::cout, Order ord = Order::pre) const;

    const T& findMin() const;

    const T& findMax() const;

    bool contains(const T& x) const;

    bool isEmpty() const;

    void clear();

private:
    void insert(const T& val, BinaryNode<T>* node);

    void insert(T&& val, BinaryNode<T>* node);

    void remove(const T& val, BinaryNode<T>* node);

    BinaryNode<T>* findMin(BinaryNode<T>* node) const;

    BinaryNode<T>* findMax(BinaryNode<T>* node) const;

    bool constains(const T& val, BinaryNode<T>* node) const;
};

template<typename T>
inline bool BinarySearchTree<T>::contains(const T& x) const {
    return constains(val, m_root);
}

template<typename T>
inline bool BinarySearchTree<T>::isEmpty() const {
    return m_root == nullptr;
}

template<typename T>
inline void BinarySearchTree<T>::clear() {
    clear(m_root);
}

template<typename T>
inline void BinarySearchTree<T>::insert(const T& val, BinaryNode<T>* node) {
    if(node == nullptr) {
        node = new BinaryNode<T>;
        node->data = val;
        return;
    }
    if(val > node->data) {
        insert(val, node->right);
    }
    else if(val < val->data) {
        insert(val, node->left);
    }
}

template<typename T>
inline void BinarySearchTree<T>::insert(T&& val, BinaryNode<T>* node) {
    if(node == nullptr) {
        node = new BinaryNode<T>;
        node->data = std::move(val);
        return;
    }
    if(val > node->data) {
        insert(std::forward(val), node->right);
    }
    else if(val < val->data) {
        insert(std::forward(val), node->left);
    }
}

template<typename T>
inline void BinarySearchTree<T>::remove(const T& val, BinaryNode<T>* node) {
    if(node == nullptr) {
        return;
    }
    if(val < node->data) {
        remove(val, node->left);
    }
    else if(val > node->data) {
        remove(val, node->right);
    }
    else if(node->left != nullptr && node->right != nullptr) {
        // 有两个儿子，先找到右儿子的最小值，然后交换
        node->data = findMin(node->right)->data;
        remove(node->data, node->right);
    }
    else {
        // 只有一个儿子，把儿子提上来就行了
        BinaryNode<T> old = node;
        node = node->left != nullptr ? node->left : node->right;
        delete old;
    }
}

template<typename T>
inline BinaryNode<T>* BinarySearchTree<T>::findMin(BinaryNode<T>* node) const {
    if(node->left != nullptr) {
        return findMin(node->left);
    }
    return node;
}

template<typename T>
inline BinaryNode<T>* BinarySearchTree<T>::findMax(BinaryNode<T>* node) const {
    if(node->right != nullptr) {
        return node->right;
    }
    return node;
}

template<typename T>
inline bool BinarySearchTree<T>::constains(const T& val, BinaryNode<T>* node) const {
    if(node == nullptr) {
        return false;
    }
    if(val < node->data) {
        return constains(val, node->left);
    }
    else if(val > node->data) {
        return constains(val, node->right);
    }
    return true;
}

template<typename T>
inline void BinarySearchTree<T>::insert(const T& val) {
    insert(val, m_root);
}

template<typename T>
inline void BinarySearchTree<T>::insert(T&& val) {
    insert(val, m_root);
}

template<typename T>
inline void BinarySearchTree<T>::remove(const T& val) {
    remove(val, m_root);
}

template<typename T>
inline void BinarySearchTree<T>::printTree(std::ostream& out, Order ord) const {
    if(ord == Order::pre) {
        preOrder(m_root, out);
    }
    else if(ord == Order::middle) {
        middleOrder(m_root, out);
    }
    else {
        postOrder(m_root, out);
    }
}

template<typename T>
inline const T& BinarySearchTree<T>::findMin() const {
    return find(m_root)->data;
}

template<typename T>
inline const T& BinarySearchTree<T>::findMax() const {
    return find(m_root)->data;
}

#endif // !binarysearchtree.h