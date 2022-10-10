#ifndef REDBLACKTREE_REDBLACKTREE_H
#define REDBLACKTREE_REDBLACKTREE_H

#include "Exeptions.h"
#include "SinglyOrderedList.h"

template<class T>
class RedBlackTree
{
private:

    enum Color { Black, Red };

    template <class T>
    struct Node
    {
        T key_;
        Color color_;
        Node<T>* left_;
        Node<T>* right_;
        Node<T>* parent_;
        SinglyOrderedList<T> translate_;

        Node(T k, Color c, Node* p, Node* l, Node* r) :
                key_(k), color_(c), parent_(p), left_(l), right_(r) { }

    };

    Node<T>* root_;

    void leftRotate(Node<T>* x);

    void rightRotate(Node<T>* y);

    void insert(Node<T>* node);

    void InsertFixUp(Node<T>* node);

    void doClear(Node<T>* &node);

    void removeNode(Node<T>*node);

    void removeFixUp(Node<T>* node, Node<T>* parent);

    Node<T>* searchNode(Node<T>*node, T key) const;

    void print(Node<T>* node) const;

    void inOrder(Node<T>* tree) const;

    void addTranslate(Node<T>* node, T translate) const;

    void searchTranslate(Node<T>* node) const;

    void deleteTranslate(Node<T>* node, std::size_t num) const;

public:
    RedBlackTree();

    ~RedBlackTree();

    void insert(T key);

    bool remove(T key);

    bool search(T key);

    void print();

    void inOrder();

    bool addTranslate(T key,T translate);

    bool searchTranslate(T key);

    bool deleteTranslate(T key, std::size_t num);
};

template<class T>
RedBlackTree<T>::RedBlackTree() {
    root_ = nullptr;
}

template<class T>
RedBlackTree<T>::~RedBlackTree() {
    doClear(root_);
}

template<class T>
void RedBlackTree<T>::leftRotate(Node<T>* x) {
    Node<T>*y = x->right_;
    x->right_ = y->left_;

    if (y->left_ != nullptr) {
        y->left_->parent_ = x;
    }

    y->parent_ = x->parent_;
    if (x->parent_ == nullptr) {
        root_ = y;
    }
    else {
        if (x == x->parent_->left_) {
            x->parent_->left_ = y;
        }
        else {
            x->parent_->right_ = y;
        }
    }
    y->left_ = x;
    x->parent_ = y;
}

template<class T>
void RedBlackTree<T>::rightRotate(Node<T>*y) {
    Node<T>*x = y->left_;
    y->left_ = x->right_;

    if (x->right_ != nullptr) {
        x->right_->parent_ = y;
    }

    x->parent_ = y->parent_;
    if (y->parent_ == nullptr) {
        root_ = x;
    }
    else {
        if  (y == y->parent_->right_) {
            y->parent_->right_ = x;
        }
        else {
            y->parent_->left_ = x;
        }
    }
    x->right_ = y;
    y->parent_ = x;
}

template<class T>
void RedBlackTree<T>::insert(T key)
{
    if(search(key)){
        throw WrongRepeatingWord();
    }
    else {
        insert(new Node<T>(key, Red, nullptr, nullptr, nullptr));
    }
}

template<class T>
void RedBlackTree<T>::insert(Node<T>* node)
{
    Node<T> *x = root_;
    Node<T> *y = nullptr;

    while (x != nullptr)
    {
        y = x;
        if (node->key_ > x->key_) {
            x = x->right_;
        }
        else {
            x = x->left_;
        }
    }

    node->parent_ = y;

    if(y != nullptr)
    {
        if (node->key_ > y->key_) {
            y->right_ = node;
        }
        else {
            y->left_ = node;
        }
    }
    else {
        root_ = node;
    }

    node->color_ = Red;
    InsertFixUp(node);
}

template<class T>
void RedBlackTree<T>::InsertFixUp(Node<T>* node)
{
    Node<T>* parent;
    parent = node->parent_;
    while (node != root_ && parent->color_ == Red)
    {
        Node<T>* greatParent = parent->parent_;
        if (greatParent->left_ == parent)
        {
            Node<T>*uncle = greatParent->right_;
            if (uncle != nullptr && uncle->color_ == Red)
            {
                parent->color_ = Black;
                uncle->color_ = Black;
                greatParent->color_ = Red;
                node = greatParent;
                parent = node->parent_;
            }
            else
            {
                if (parent->right_ == node)
                {
                    leftRotate(parent);
                    swap(node, parent);
                }
                rightRotate(greatParent);
                greatParent->color_ = Red;
                parent->color_ = Black;
                break;
            }
        }
        else
        {
            Node<T>*uncle = greatParent->left_;
            if (uncle != nullptr && uncle->color_ == Red)
            {
                greatParent->color_ = Red;
                parent->color_ = Black;
                uncle->color_ = Black;

                node = greatParent;
                parent = node->parent_;
            }
            else
            {
                if (parent->left_ == node)
                {
                    rightRotate(parent);
                    swap(parent, node);
                }
                leftRotate(greatParent);
                parent->color_ = Black;
                greatParent->color_ = Red;
                break;
            }
        }
    }
    root_->color_ = Black;
}

template<class T>
void RedBlackTree<T>::doClear(Node<T>* &node)
{
    if (node == nullptr) {
        return;
    }

    doClear(node->left_);
    doClear(node->right_);

    delete node;
    node = nullptr;
}

template<class T>
bool RedBlackTree<T>::remove(T key)
{
    Node<T>*deleteNode = searchNode(root_, key);

    if (deleteNode != nullptr) {
        removeNode(deleteNode);
        return true;
    }
    else{
        return false;
    }
}

template<class T>
void RedBlackTree<T>::removeNode(Node<T>*node)
{
    if(node == root_){
        root_ = nullptr;
        delete node;
        return;
    }

    Node<T> *child, *parent;
    Color color;

    if (node->left_ != nullptr && node->right_ != nullptr)
    {
        Node<T> *replace = node;

        replace = node->right_;
        while (replace->left_ != nullptr)
        {
            replace = replace->left_;
        }

        if (node->parent_ != nullptr)
        {
            if (node->parent_->left_ == node) {
                node->parent_->left_ = replace;
            }
            else {
                node->parent_->right_ = replace;
            }
        }

        else {
            root_ = replace;
        }

        child = replace->right_;
        parent = replace->parent_;
        color = replace->color_;


        if (parent == node) {
            parent = replace;
        }
        else
        {

            if (child != nullptr)
                child->parent_ = parent;
            parent->left_ = child;

            replace->right_ = node->right_;
            node->right_->parent_ = replace;
        }
        replace->parent_ = node->parent_;
        replace->color_ = node->color_;
        replace->left_ = node->left_;
        node->left_->parent_ = replace;
        if (color == Black) {
            removeFixUp(child, parent);
        }

        delete node;
        return;
    }

    if (node->left_ != nullptr) {
        child = node->left_;
    }
    else {
        child = node->right_;
    }

    parent = node->parent_;
    color = node->color_;
    if (child)
    {
        child->parent_ = parent;
    }

    if (parent)
    {
        if (node == parent->left_)
            parent->left_ = child;
        else
            parent->right_ = child;
    }
    else {
        RedBlackTree::root_ = child;
    }

    if (color == Black)
    {
        removeFixUp(child, parent);
    }
    delete node;

}

template<class T>
void RedBlackTree<T>::removeFixUp(Node<T>* node, Node<T>*parent)
{
    Node<T>*otherNode;
    while ((!node) || node->color_ == Black && node != root_)
    {
        if (parent->left_ == node)
        {
            otherNode = parent->right_;
            if (otherNode->color_ == Red)
            {
                otherNode->color_ = Black;
                parent->color_ = Red;
                leftRotate(parent);
                otherNode = parent->right_;
            }
            else
            {
                if (!(otherNode->right_) || otherNode->right_->color_ == Black)
                {
                    otherNode->left_->color_=Black;
                    otherNode->color_ = Red;
                    rightRotate(otherNode);
                    otherNode = parent->right_;
                }
                otherNode->color_ = parent->color_;
                parent->color_ = Black;
                otherNode->right_->color_ = Black;
                leftRotate(parent);
                node = root_;
                break;
            }
        }
        else
        {
            otherNode = parent->left_;
            if (otherNode->color_ == Red)
            {
                otherNode->color_ = Black;
                parent->color_ = Red;
                rightRotate(parent);
                otherNode = parent->left_;
            }
            if ((!otherNode->left_ || otherNode->left_->color_ == Black) &&
                (!otherNode->right_ || otherNode->right_->color_ == Black))
            {
                otherNode->color_ = Red;
                node = parent;
                parent = node->parent_;
            }
            else
            {
                if (!(otherNode->left_) || otherNode->left_->color_ == Black)
                {
                    otherNode->right_->color_ = Black;
                    otherNode->color_ = Red;
                    leftRotate(otherNode);
                    otherNode = parent->left_;
                }
                otherNode->color_ = parent->color_;
                parent->color_ = Black;
                otherNode->left_->color_ = Black;
                rightRotate(parent);
                node = root_;
                break;
            }
        }
    }
    if (node) {
        node->color_ = Black;
    }
}

template<class T>
bool RedBlackTree<T>::search(T key)
{
    return (searchNode(root_, key) != nullptr);
}

template<class T>
typename RedBlackTree<T>::template Node<T>* RedBlackTree<T>::searchNode(Node<T>*node, T key) const
{
    if (node == nullptr || node->key_ == key) {
        return node;
    }
    else {
        if (key > node->key_) {
            return searchNode(node->right_, key);
        }
        else {
            return searchNode(node->left_, key);
        }
    }
}

template<class T>
void RedBlackTree<T>::print() {
    if (root_ == nullptr) {
        throw ErrorEmptyTree();
    }
    else {
        print(root_);
    }
}

template<class T>
void RedBlackTree<T>::print(Node<T>* node)const {
    if (node == nullptr) {
        return;
    }

    if (node->parent_ == nullptr) {
        std::cout << node->key_ << "(" << node->color_ << ") is root_" << std::endl;
    }
    else if(node->parent_->left_ == node){
        std::cout << node->key_ << "(" << node->color_ << ") is " << node->parent_->key_ << "'s "
        << "left_ child" << std::endl;
    }
    else{
        std::cout << node->key_ << "(" << node->color_ << ") is " << node->parent_->key_ << "'s "
        << "right_ child" << std::endl;
    }
    print(node->left_);
    print(node->right_);
}

template<class T>
void RedBlackTree<T>::inOrder() {
    if (root_ == nullptr) {
        std::cout << "Tree is empty!" << std::endl;
    }
    else {
        inOrder(root_);
    }
}

template<class T>
void RedBlackTree<T>::inOrder(Node<T>* tree)const {
    if (tree != nullptr) {
        inOrder(tree->left_);
        std::cout << tree->key_ << ":" << std::endl;
        tree->translate_.print();
        std::cout << std::endl;
        inOrder(tree->right_);
    }
}


template<class T>
void RedBlackTree<T>::addTranslate(Node<T>* node, T translate) const{
    node->translate_.insertItem(translate);
}

template<class T>
bool RedBlackTree<T>::addTranslate(T key,T translate){
    if(!search(key)){
        return false;
    }

    addTranslate(searchNode(root_, key),translate);
    return true;
}

template<class T>
bool RedBlackTree<T>::searchTranslate(T key){
    if(!search(key)){
        return false;
    }

    searchTranslate(searchNode(root_, key));
    return true;
}

template<class T>
void RedBlackTree<T>::searchTranslate(Node<T>* node) const{
    node->translate_.print();
}

template<class T>
bool RedBlackTree<T>::deleteTranslate(T key, std::size_t num) {
    if(!search(key)){
        return false;
    }

    deleteTranslate(searchNode(root_, key), num);
    return true;
}

template<class T>
void RedBlackTree<T>::deleteTranslate(Node<T>* node, std::size_t num) const{
    node->translate_.deleteItem(num);
}
#endif //REDBLACKTREE_REDBLACKTREE_H
