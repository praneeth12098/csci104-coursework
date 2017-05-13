#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the AVLNode class.
--------------------------------------------
*/

/**
* Constructor for an AVLNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
char AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node inherits from a base node.
*/
template<typename Key, typename Value>
AVLNode<Key, Value>* AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key,Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the AVLNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an AVL tree.
*/
template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    // Methods for inserting/erasing (removing) elements from the tree. 
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);

private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (AVLNode<Key, Value> *n);
    void rotateRight (AVLNode<Key, Value> *n);
    void rotateLeftRight(AVLNode<Key, Value> *n);
    void rotateRightLeft(AVLNode<Key, Value> *n);
    int max(int a, int b);
    int getHeight(AVLNode<Key, Value> *n);
    int findBalance(AVLNode<Key, Value> *n);
    void fixTree(AVLNode<Key, Value>* n);

    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
};

/*
--------------------------------------------
Begin implementations for the AVLTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the node and then balances the tree.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::insert(const std::pair<Key, Value>& keyValuePair)
{
    Node<Key, Value>* current = this->mRoot;  
    if (current == NULL)
    {
        this->mRoot = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second, NULL); 
    }
    else 
    {
        while (true) 
        {
            if(current->getKey() == keyValuePair.first)
            {
              current->setValue(keyValuePair.second); return;
            }
            else if(current->getKey() < keyValuePair.first) 
            {
              if (current->getRight()) current = current->getRight();
              else break;
            }
            else 
            {
              if(current->getLeft()) current = current->getLeft();
              else break;
            }
        }

        AVLNode<Key, Value>* newNode = new AVLNode<Key, Value>(keyValuePair.first, keyValuePair.second,
            static_cast<AVLNode<Key, Value>*>(current));

        if (current->getKey() < keyValuePair.first) current->setRight(newNode);
        else current->setLeft(newNode);

        fixTree(static_cast<AVLNode<Key, Value>*>(current));
    }
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::fixTree(AVLNode<Key, Value> *n)
{
    n->setBalance(findBalance(n));

    if(n->getBalance() == -2)
    {
        if(getHeight(n->getLeft()->getLeft()) >= getHeight(n->getLeft()->getRight())) rotateRight(n);
        else rotateLeftRight(n);
    }
    else if(n->getBalance() == 2)
    {
        if(getHeight(n->getRight()->getRight()) >= getHeight(n->getRight()->getLeft())) rotateLeft(n);
        else rotateRightLeft(n);
    }
    if(n->getParent() != NULL) fixTree(n->getParent());
    else this->mRoot = n;
}

/**
* Erase function for a given key. Finds the node, reattaches pointers, and then balances when finished.
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::erase(const Key& key)
{
    // TODO
    if(this->mRoot == NULL) return;

    Node<Key, Value> *n = this->mRoot; Node<Key, Value> *p = this->mRoot;
    Node<Key, Value> *toBeErased = NULL; Node<Key, Value> *c = this->mRoot;

    while(c != NULL)
    {
        p = n; n = c;
        if(key > n->getKey()) c = n->getRight();
        else c = n->getLeft();
        if(key == n->getKey()) toBeErased = n;
    }

    if(key)
    {
        toBeErased->setValue(n->getValue());
        if(n->getLeft() != NULL) c = n->getLeft();
        else c = n->getRight();
        Node<Key, Value> *temp = this->mRoot;
        if(temp->getKey() == key) temp = c;
        else
        {
            if(p->getLeft() == n) p->setLeft(c);
            else p->setRight(c);
            fixTree(static_cast<AVLNode<Key, Value>*>(p));
        }
    }
    else std::cout << "Key cannot be found!" << std::endl;
}

/**
* Rotates n down and to the left
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key, Value> *n)
{
    // TODO
    AVLNode<Key, Value> *right = n->getRight();

    right->setParent(n->getParent());
    n->setRight(right->getLeft());

    if(n->getRight() != NULL) n->getRight()->setParent(n);

    right->setLeft(n);
    n->setParent(right);

    if(right->getParent() != NULL)
    {
        if(right->getParent()->getRight() == n) right->getParent()->setRight(right);
        else right->getParent()->setLeft(right);
    }
    n->setBalance(findBalance(n));
    right->setBalance(findBalance(right));
}

/**
* Rotates n down and to the right
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRight (AVLNode<Key, Value> *n)
{
    // TODO
    AVLNode<Key, Value> *left = n->getLeft();

    left->setParent(n->getParent());
    n->setLeft(left->getRight());

    if(n->getLeft() != NULL) n->getLeft()->setParent(n);

    left->setRight(n);
    n->setParent(left);

    if(left->getParent() != NULL)
    {
        if(left->getParent()->getLeft() == n) left->getParent()->setLeft(left);
        else left->getParent()->setRight(left);
    }
    n->setBalance(findBalance(n));
    left->setBalance(findBalance(left));
}

/**
* Rotates Right then Left for one of the 4 base cases
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateLeftRight(AVLNode<Key, Value> *n)
{
    if(n == NULL) return;
    if(n->getLeft() == NULL) return;
    rotateLeft(n->getLeft());
    rotateRight(n);
}

/**
* Rotates Left then Right for one of the 4 base cases
*/
template<typename Key, typename Value>
void AVLTree<Key, Value>::rotateRightLeft(AVLNode<Key, Value> *n)
{
    if(n == NULL) return;
    if(n->getRight() == NULL) return;
    rotateRight(n->getRight());
    rotateLeft(n);
}

/**
* Gets the max of two integers
*/
template<typename Key, typename Value>
int AVLTree<Key, Value>::max(int a, int b)
{
    return (a > b)? a : b;
}

/**
* Gets the height of a node
*/
template<typename Key, typename Value>
int AVLTree<Key, Value>::getHeight(AVLNode<Key, Value> *n)
{
    if(n == NULL) return 0;
    else return 1 + max(getHeight(n->getLeft()), getHeight(n->getRight()));
}

/**
* Finds the balance factor of node n
**/
template<typename Key, typename Value>
int AVLTree<Key, Value>::findBalance(AVLNode<Key, Value> *n)
{
    int lHeight = 0;
    int rHeight = 0;
    if(n == NULL) return 0;
    if(n->getLeft() != NULL)
        lHeight = getHeight(n->getLeft());
    if(n->getRight() != NULL)
        rHeight = getHeight(n->getRight());
    return rHeight - lHeight;
}

/**
 * Given a correct AVL tree, this functions relinks the tree in such a way that
 * the nodes swap positions in the tree.  Balances are also swapped.
 */
template<typename Key, typename Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if(this->mRoot == n2) {
        this->mRoot = n1;
    }

}

/*
------------------------------------------
End implementations for the AVLTree class.
------------------------------------------
*/

#endif