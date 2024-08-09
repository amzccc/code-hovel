#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <math.h>

class BinarySearchTree {
private:
    struct AvlNode
{
    int element;
    AvlNode* left;
    AvlNode* right;
    int height;

    AvlNode(const int &x, AvlNode* lt, AvlNode *rt, int h = 0)
            :element(x), left(lt), right(rt), height(h) {}
    AvlNode(const int &&x, AvlNode* lt, AvlNode *rt, int h = 0)
            :element(std::move(x)), left(lt), right(rt), height(h) {}
};
    
    AvlNode* root;
    static const int ALLOWED_IMBALANCE = 1;
    //私有函数
    void insert(const int &x, AvlNode* &t);
    void insert(int &&x, AvlNode* &t);
    void remove(const int &x, AvlNode* &t);
    AvlNode* findMin(AvlNode* t) const;
    AvlNode* findMax(AvlNode* t) const;
    bool contains(const int &x, AvlNode* t) const;
    void printTree(AvlNode* t, std::ostream &out) const;
    void makeEmpty(AvlNode* &t);
    AvlNode* clone(AvlNode* t) const;
    void balance(AvlNode* &t);
    void rotateWithLeftChild(AvlNode* &k2);
    void doubleWithLeftChild(AvlNode* &k3);
    void rotateWithRightChild(AvlNode* &k2);
    void doubleWithRightChild(AvlNode* &k3);
    int height(AvlNode* t) const {
        return t ==nullptr? -1:t->height;
    }

public:
    //构造
    BinarySearchTree();
    BinarySearchTree(const BinarySearchTree &rhs);
    BinarySearchTree(const BinarySearchTree &&rhs);
    ~BinarySearchTree();

    //树的接口
    const int &findMin() const;
    const int &findMax() const;
    bool contains(const int &x) const;
    bool isEmpty() const;
    void printTree(std::ostream &out = std::cout) const;
    void makeEmpty();
    void insert(const int &x);
    void insert(int &&x);
    void remove(const int &x);
    

    
};


BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}


BinarySearchTree::BinarySearchTree(const BinarySearchTree &rhs):root(nullptr) {
    root = clone(rhs.root);
}


BinarySearchTree::BinarySearchTree(const BinarySearchTree &&rhs) {
    root = clone(std::move(rhs).root);
}

BinarySearchTree::AvlNode* BinarySearchTree::clone(AvlNode* t) const {
    if(t == nullptr)
        return nullptr;
    else
        return new AvlNode {t->element, clone(t->left), clone(t->right)};
}


BinarySearchTree::~BinarySearchTree() {
    makeEmpty();
}


void BinarySearchTree::makeEmpty() {
    makeEmpty(root);
}


void BinarySearchTree::makeEmpty(AvlNode* &t) {
    if(t != nullptr) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
    }
    t = nullptr;
}

void BinarySearchTree::insert(const int &x, AvlNode* &t) {
    if (t == nullptr)
        t = new AvlNode {x, nullptr, nullptr};
    else if(x < t->element)
        insert(x, t->left);
    else if(x > t->element)
        insert(x, t->right);
    
    balance(t);
}

void BinarySearchTree::insert(int &&x, AvlNode* &t) {
    if (t == nullptr)
        t = new AvlNode
{std::move(x), nullptr, nullptr};
    x < t->element? insert(std::move(x), t->left):insert(std::move(x), t->right);
}


void BinarySearchTree::insert(const int &x) {
    insert(x, root);
}

void BinarySearchTree::remove(const int &x, AvlNode* &t) {
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
        AvlNode* oldNode = t;
        t = (t->left != nullptr)? t->left: t->right;
        delete oldNode;
    }
}

void BinarySearchTree::remove(const int &x) {
    remove (x, root);
}

bool BinarySearchTree::contains(const int &x) const {
    return contains(x, root);
}

bool BinarySearchTree::contains(const int &x, AvlNode* t) const {
    if (t == nullptr)
        return false;
    else if (x < t->element)
        return contains(x, t->left);
    else if (x > t->element)
        return contains(x, t->right);
    else
        return true;
}


BinarySearchTree::AvlNode* BinarySearchTree::findMin(AvlNode* t) const {
    if(t != nullptr)
        while(t->left != nullptr)
            t = t->left;
    return t;
}

const int &BinarySearchTree::findMin() const {
    return findMin(root)->element;
}


BinarySearchTree::AvlNode* BinarySearchTree::findMax(AvlNode* t) const {
    if(t != nullptr)
        while(t->right != nullptr)
            t = t->right;
    return t;
}


const int &BinarySearchTree::findMax() const {
    return findMax(root)->element;
}

bool BinarySearchTree::isEmpty() const {
    if(root != nullptr)
        return false;
    return true;
}

void BinarySearchTree::printTree(AvlNode* t, std::ostream &out) const {
    
}

void BinarySearchTree::printTree(std::ostream &out) const {
    printTree(root, out);
}

void BinarySearchTree::balance(AvlNode* &t) {
    if(t == nullptr)
        return;
    if(height(t->left) - height(t->right) > ALLOWED_IMBALANCE) {
        if(height(t->left->left) >= height(t->left->right))
            rotateWithLeftChild(t);
        else
            doubleWithLeftChild(t);
    }
    else if(height(t->right) - height(t->left) > ALLOWED_IMBALANCE) {
        //if(height(t->right->right) >= height(t->right->left))
            //rotateWithRightChild(t);
        //else
            //doubleWithRightChild(t);
    }
    t->height = std::max(height(t->left), height(t->right)) + 1;
}

void BinarySearchTree::rotateWithLeftChild(AvlNode* &k2) {
    AvlNode* k1 = k2->left;
    k2->left = k1->right;
    k1->right = k2;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->height = std::max(height(k1->left), k2->height) + 1;
    k2 = k1;
}

void BinarySearchTree::doubleWithLeftChild(AvlNode* &k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}