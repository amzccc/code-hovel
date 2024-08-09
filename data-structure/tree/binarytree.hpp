/******************************************
 * @file		tree.h
 * @brief		数据结构——树
 * @author		cheng wentao
 * @version		v1.0.0
 * @date		2024-02-18 23:36
 ******************************************/
#ifndef TREE_H__
#define TREE_H__

#include <iostream>
#include <string>
#include <stack>

template<typename T>
struct BinaryNode {
    T data;

    BinaryNode<T>* left{ nullptr };
    BinaryNode<T>* right{ nullptr };    
};

template<typename T>
class BinaryTree {
public:
    BinaryTree() = default;

    virtual ~BinaryTree();

    // 先序遍历
    virtual void preOrder(BinaryNode<T>* root = nullptr, std::ostream& out = std::cout) final;

    // 后序遍历
    virtual void postOrder(BinaryNode<T>* root = nullptr, std::ostream& out = std::cout) final;

    // 中序遍历
    virtual void middleOrder(BinaryNode<T>* root = nullptr, std::ostream& out = std::cout) final;

private:
    virtual void clear(BinaryNode<T>* node) final;

public:
    BinaryNode<T>* m_root{ nullptr };
};

template<typename T>
inline BinaryTree<T>::~BinaryTree() {
    clear(m_root);
}

template<typename T>
inline void BinaryTree<T>::preOrder(BinaryNode<T>* root, std::ostream& out) {
    std::stack<BinaryNode<T>*> nodes;
    nodes.push(root == nullptr ? m_root : root);
    BinaryNode<T>* cur;
    while(!nodes.empty()) {
        cur = nodes.top();
        nodes.pop();
        out << cur->data << " ";
        if(cur->right != nullptr) {
            nodes.push(cur->right);
        }
        if(cur->left != nullptr) {
            nodes.push(cur->left);
        }
    }
}

template<typename T>
inline void BinaryTree<T>::postOrder(BinaryNode<T>* root, std::ostream& out) {
    std::stack<BinaryNode<T>*> nodes;
    nodes.push(root == nullptr ? m_root : root);
    std::stack<BinaryNode<T>*> print_nodes;
    BinaryNode<T>* cur;
    while(!nodes.empty()) {
        cur = nodes.top();
        nodes.pop();
        print_nodes.push(cur);
        if(cur->left != nullptr) {
            nodes.push(cur->left);
        }
        if(cur->right != nullptr) {
            nodes.push(cur->right);
        }
    }
    while(!print_nodes.empty()) {
        out << print_nodes.top()->data << " ";
        print_nodes.pop();
    }
}

template<typename T>
inline void BinaryTree<T>::middleOrder(BinaryNode<T>* root, std::ostream& out) {
    std::stack<BinaryNode<T>*> nodes;
    BinaryNode<T>* cur = root == nullptr ? m_root : root;
    while(!nodes.empty() || cur != nullptr) {
        while(cur != nullptr) {
            nodes.push(cur);
            cur = cur->left;
        }
        out << nodes.top()->data << " ";
        cur = nodes.top()->right;
        nodes.pop();
    }
}

template<typename T>
inline void BinaryTree<T>::clear(BinaryNode<T>* node) {
    if(node == nullptr) {
        return;
    }
    else {
        clear(node->left);
        clear(node->right);
        delete node;
    }
    node = nullptr;
}

#endif // !tree.h