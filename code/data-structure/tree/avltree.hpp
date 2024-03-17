/******************************************
 * @file		avltree.hpp
 * @brief		avl树
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-03-08 23:18
 ******************************************/
#ifndef AVLTREE_H__
#define AVLTREE_H__

#include <memory>

using std::shared_ptr;

template<typename T>
struct Node {
    T value;
    shared_ptr<Node<T>> left{ nullptr };
    shared_ptr<Node<T>> right{ nullptr };
    int height{ 0 };

    explicit Node(T val) : value(val) { }
    virtual ~Node() = default;
};

template<typename T>
class AvlTree {
public:
    AvlTree() = default;
    explicit AvlTree(T val);
    virtual ~AvlTree() = default;

    shared_ptr<Node<T>> root() const;

    void insert(const T& val);

    void remove(const T& val);
    
private:
    void insert(const T& val, shared_ptr<Node<T>>& node);

    void remove(const T& val, shared_ptr<Node<T>>& node);

    void balance(shared_ptr<Node<T>>& node);

    void rotateWithLeftChild(shared_ptr<Node<T>>& node);

    void rotateWithRightChild(shared_ptr<Node<T>>& node);

    void doubleRotateWithLeftChild(shared_ptr<Node<T>>& node);

    void doubleRotateWithRightChild(shared_ptr<Node<T>>& node);

    int high(const shared_ptr<Node<T>>& node) const;

    shared_ptr<Node<T>> findMin(shared_ptr<Node<T>>& node);

private:
    shared_ptr<Node<T>> m_root{ nullptr };
};

#endif // !avltree.hpp

template<typename T>
inline AvlTree<T>::AvlTree(T val) : m_root{std::make_shared<Node>(val)} { }

template<typename T>
inline shared_ptr<Node<T>> AvlTree<T>::root() const {
    return m_root;
}

template<typename T>
inline void AvlTree<T>::insert(const T& val) {
    insert(val, m_root);
}

template<typename T>
inline void AvlTree<T>::remove(const T& val) {
    remove(val, m_root);
}

template<typename T>
inline int AvlTree<T>::high(const shared_ptr<Node<T>>& node) const {
    return node == nullptr ? -1 : node->height;
}

template<typename T>
inline shared_ptr<Node<T>> AvlTree<T>::findMin(shared_ptr<Node<T>>& node) {
    if(node->left == nullptr) {
        return node;
    }
    return findMin(node->left);
}

template<typename T>
inline void AvlTree<T>::insert(const T& val, shared_ptr<Node<T>>& node) {
    if(node == nullptr) {
        node = std::make_pair<Node<T>>(val);
    }
    else if(val < node->value) {
        insert(val, node->left);
    }
    else if(val > node->value) {
        insert(val, node->right);
    }
    balance(node);
}

template<typename T>
inline void AvlTree<T>::remove(const T& val, shared_ptr<Node<T>>& node) {
    if(node == nullptr) {
        return;
    }
    if(val < node->value) {
        remove(val, node->left);
    }
    else if(val > node->value) {
        remove(val, node->right);
    }
    else if(node->left != nullptr && node->right != nullptr) {
        // 两个子的情况
        node->value = findMin(node->right)->value;
        remove(node->value, node->right);
    }
    else {
        // 只有一个子
        node = node->left == nullptr ? node->right : node->left;
    }
    balance(node);
}

template<typename T>
inline void AvlTree<T>::balance(shared_ptr<Node<T>>& node) {
    if(node == nullptr) {
        return;
    }
    if(high(node->left) - high(node->right) > 1) {
        high(node->left->left) >= high(node->left->right) ?
            rotateWithLeftChild(node) : doubleRotateWithLeftChild(node);
    }
    else if(high(node->right) - high(node->left) > 1) {
        high(node->right->left) >= high(node->right->right) ?
            doubleRotateWithRightChild(node) : rotateWithRightChild(node);
    }
    node->height = std::max(high(node->left), high(node->right)) + 1;
}

template<typename T>
inline void AvlTree<T>::rotateWithLeftChild(shared_ptr<Node<T>>& node) {
    auto tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    node->height = std::max(high(node->left), high(node->right)) + 1;
    tmp->height = std::max(high(tmp->left), high(tmp->right)) + 1;
    node = tmp;
}

template<typename T>
inline void AvlTree<T>::rotateWithRightChild(shared_ptr<Node<T>>& node) {
    auto tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    node->height = std::max(high(node->left), high(node->right)) + 1;
    tmp->height = std::max(high(tmp->left), high(node->right)) + 1;
    node = tmp;
}

template<typename T>
inline void AvlTree<T>::doubleRotateWithLeftChild(shared_ptr<Node<T>>& node) {
    rotateWithRightChild(node->left);
    rotateWithLeftChild(node);
}

template<typename T>
inline void AvlTree<T>::doubleRotateWithRightChild(shared_ptr<Node<T>>& node) {
    rotateWithLeftChild(node->right);
    rotateWithRightChild(node);
}






