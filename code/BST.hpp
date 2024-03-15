#include <iostream>
#include <string>
#include <stack>
#include <vector>

//二叉搜索树，实现增删改查
template<typename T>
class BinarySearchTree {
private:
    struct BinaryNode
    {
        T element;
        BinaryNode* left;
        BinaryNode* right;
        
        //构造
        BinaryNode(const T &theElement, BinaryNode* lt, BinaryNode* rt)
                : element(theElement), left(lt), right(rt) {}
        BinaryNode(T &&theElement, BinaryNode* lt, BinaryNode* rt)
            : element(theElement), left(lt), right(rt) {}
    };
    
    BinaryNode* root;

    //私有函数
    void insert(const T &x, BinaryNode* &t); //指针的引用 * &ptr 用于对指针的修改
    void insert(T &&x, BinaryNode* &t);
    void remove(const T &x, BinaryNode* &t);
    BinaryNode* findMin(BinaryNode* t) const;
    BinaryNode* findMax(BinaryNode* t) const;
    bool contains(const T &x, BinaryNode* t) const;
    void printTree(BinaryNode* t, std::ostream &out) const;
    void makeEmpty(BinaryNode* &t);
    BinaryNode* clone(BinaryNode* t) const;

public:
    //构造
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs);
    BinarySearchTree(const BinarySearchTree &&rhs);
    ~BinarySearchTree();

    //树的接口
    const T& findMin() const;
    const T& findMax() const;
    bool contains(const T &x) const;
    bool isEmpty() const;
    void printTree(std::ostream &out = std::cout) const;
    void makeEmpty();
    void insert(const T &x);
    void insert(T &&x);
    void remove(const T &x);

    //重载运算符
    BinarySearchTree &operator = (const BinarySearchTree &rhs);
    BinarySearchTree &operator = (const BinarySearchTree &&rhs);
};

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator = (const BinarySearchTree<T> &rhs) {
    root = clone(rhs.root);
}

template<typename T>
BinarySearchTree<T> &BinarySearchTree<T>::operator = (const BinarySearchTree<T> &&rhs) {
    root = clone(std::move(rhs).root);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree() {
    root = nullptr;
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &rhs):root(nullptr) {
    root = clone(rhs.root);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree &&rhs) {
    root = clone(std::move(rhs).root);
}

template<typename T>
typename BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::clone(BinarySearchTree<T>::BinaryNode* t) const {
    if(t == nullptr)
        return nullptr;
    else
        return new BinaryNode{t->element, clone(t->left), clone(t->right)};
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree() {
    makeEmpty();
}

template<typename T>
void BinarySearchTree<T>::makeEmpty() {
    makeEmpty(root);
}

template<typename T>
void BinarySearchTree<T>::makeEmpty(BinaryNode* &t) {
    if(t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

template<typename T>
void BinarySearchTree<T>::insert(const T &x, BinaryNode* &t) {
    if (t == nullptr)
        t = new BinaryNode{x, nullptr, nullptr};
    else if(x < t->element)
        insert(x, t->left);
    else if(x > t->element)
        insert(x, t->right);
    else;
}

template<typename T>
void BinarySearchTree<T>::insert(T &&x, BinaryNode* &t) {
    if (t == nullptr)
        t = new BinaryNode{std::move(x), nullptr, nullptr};
    x < t->element? insert(std::move(x), t->left):insert(std::move(x), t->right);
}

template<typename T>
void BinarySearchTree<T>::insert(const T &x) {
    insert(x, root);
}

template<typename T>
void BinarySearchTree<T>::remove(const T &x, BinaryNode* &t) {
    if(t == nullptr)
        return;
    if(x < t->element)
        remove(x, t->left);
    else if(x > t->element)
        remove(x, t->right);
    else if(t->left != nullptr && t->right != nullptr) {
        t->element = findMin(t->right)->element;
        remove(t->element, t->right);
    }
    else {
        BinaryNode* oldNode = t;
        t = (t->left != nullptr)? t->left: t->right;
        delete oldNode;
    }
}

template<typename T>
void BinarySearchTree<T>::remove(const T &x) {
    remove (x, root);
}

template<typename T>
bool BinarySearchTree<T>::contains(const T &x) const {
    return contains(x, root);
}

template<typename T>
bool BinarySearchTree<T>::contains(const T &x, BinaryNode* t) const {
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return constains(x, t->left);
    else if (x > t->element)
        return contains(x, t->right);
    else
        return true;
}

template<typename T>
typename BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::findMin(BinaryNode* t) const {
    if(t != nullptr)
        while(t->left != nullptr)
            t = t->left;
    return t;
}

template<typename T>
const T &BinarySearchTree<T>::findMin() const {
    return findMin(root)->element;
}

template<typename T>
typename BinarySearchTree<T>::BinaryNode* BinarySearchTree<T>::findMax(BinaryNode* t) const {
    if(t != nullptr)
        while(t->right != nullptr)
            t = t->right;
    return t;
}

template<typename T>
const T &BinarySearchTree<T>::findMax() const {
    return findMax(root)->element;
}

template<typename T>
bool BinarySearchTree<T>::isEmpty() const {
    if(root != nullptr)
        return false;
    return true;
}
template<typename T>
void BinarySearchTree<T>::printTree(BinaryNode* t, std::ostream &out) const {
    
}

template<typename T>
void BinarySearchTree<T>::printTree(std::ostream &out) const {
    printTree(root, out);
}