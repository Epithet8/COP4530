#ifndef _BST_CPP
#define _BST_CPP

#include <iostream>
#include <sstream>
#include "bst.h"

using namespace std;
using namespace cop4530;

template <typename T>
BST<T>::BST(int th){
    threshold_value = th;
    root = NULL;
}

template <typename T>
BST<T>::BST(const string input, int th){
    threshold_value = th;
    root = NULL;
    buildFromInputString(input);
}

template <typename T>
BST<T>::BST(const BST& rhs){ // copy constructor
    threshold_value = rhs.threshold_value;
    root = NULL;
    root = clone(rhs.root);
}

template <typename T>
BST<T>::BST(BST&& rhs){ // move constructor
    // todo
    threshold_value = rhs.threshold_value;
    root = rhs.root;
    rhs.root = NULL;
}

template <typename T>
BST<T>::~BST(){ // destructor
    makeEmpty(root);
}

template <typename T>
const BST<T>& BST<T>::operator=(const BST& rhs){ // copy assignment
    if(root != rhs.root){
        makeEmpty(root);
        root = clone(rhs.root);
    }
    return *this;
}

template <typename T>
const BST<T>& BST<T>::operator=(BST&& rhs){ // move assignment
    if(root != rhs.root){
        makeEmpty(root);
        root = rhs.root;
    }
    rhs.root = NULL;
    return *this;
}

template <typename T>
void BST<T>::printInOrder(BSTNode<T>* t) const{
    if(t != NULL){
        printInOrder(t->left);
        cout << t->data << " ";
        printInOrder(t->right);
    }
}

template <typename T>
void BST<T>::printLevelOrder(BSTNode<T>* t, int lev) const{
    if(t != NULL){
        if(lev == 1){
            cout << t->data << " ";
        }else if(lev > 1){
            printLevelOrder(t->left, lev - 1);
            printLevelOrder(t->right, lev -1);
        }
    }
}

template <typename T>
int BST<T>::numOfNodes(BSTNode<T>* t) const{
    if(t == NULL){
        return 0;
    }
    int cnt = 1;
    cnt += numOfNodes(t->left);
    cnt += numOfNodes(t->right);
    return cnt;
}

template <typename T>
int BST<T>::height(BSTNode<T>* t) const{
    if(t == NULL){
        return 0;
    }
    int lht = height(t->left);
    int rht = height(t->right);
    return max(lht, rht) + 1;
}

template <typename T>
void BST<T>::makeEmpty(BSTNode<T>* &t){
    if(t == NULL){
        return;
    }
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
    t = NULL;
}

template <typename T>
BSTNode<T>* BST<T>::insert(const T& v, BSTNode<T>* &t){
    if(t == NULL){
        t = new BSTNode<T>();
        t->data = v;
        t->visits = 0;
        t->left = NULL;
        t->right = NULL;
        return t;
    }else if(v < t->data){
        t->left = insert(v, t->left);
    }else if(v > t->data){
        t->right = insert(v, t->right);
    }
    return t;
}

template <typename T>
BSTNode<T>* BST<T>::insert(T&& v, BSTNode<T>* &t){
    if(t == NULL){
        t = new BSTNode<T>();
        t->data = move(v);
        t->visits = 0;
        t->left = NULL;
        t->right = NULL;
        return t;
    }else if(v < t->data){
        t->left = insert(move(v), t->left);
    }else if(v > t->data){
        t->right = insert(move(v), t->right);
    }
    return t;
}

template <typename T>
void BST<T>::remove(const T& v, BSTNode<T>* &t, BSTNode<T>* &parent){
    // general note: t eventually points at node containing v, do not understand how or why, but went with it
    if(t == NULL){
        return;
    }
    if(t->data == v){
        // leaf node
        if(t->left == NULL && t->right == NULL){
            BSTNode<T>* ot = t;
            if(parent->left == t){
                parent->left = NULL;
            }else if(parent->right == t){
                parent->right = NULL;
            }else{
                // root
                root = NULL;
            }
            delete ot;
            ot = NULL;
        // has left child only
        }else if(t->left != NULL && t->right == NULL){
            BSTNode<T>* ot = t;
            if(parent->left == t){
                parent->left = t->left;
            }else if(parent->right == t){
                parent->right = t->left;
            }else{
                root = t->left;
            }
            delete ot;
            ot = NULL;
        // has right child only
        }else if(t->left == NULL && t->right != NULL){
            BSTNode<T>* ot = t;
            if(parent->left == t){
                parent->left = t->right;
            }else if(parent->right == t){
                parent->right = t->right;
            }else{
                root = t->right;
            }
            delete ot;
            ot = NULL;
        // has two children
        }else{
            BSTNode<T>* ot = t;
            //find replacement node, largest of the smaller, iteratively
            BSTNode<T>* replace = t->left;
            BSTNode<T>* replparent = t;
            while(replace->right != NULL){
                replparent = replace;
                replace = replace->right;
            }
            // fix replacement parent
            // replacement is a leaf
            if(replace->left == NULL && replace->right == NULL){
                if(replparent->left == replace){
                    replparent->left = NULL;
                }else if(replparent->right == replace){
                    replparent->right = NULL;
                }else{
                    // not sure should get here
                }
            // replacement has left child only
            }else if(replace->left != NULL && replace->right == NULL){
                if(replparent->left == replace){
                    replparent->left = replace->left;
                }else{
                    replparent->right = replace->left;
                }
            // replacement has right child only
            }else if(replace->left == NULL && replace->right != NULL){
                if(replparent->left == replace){
                    replparent->left = replace->right;
                }else{
                    replparent->right = replace->right;
                }
            }else{
                // should never get here since replacement will not have two children
            }
            // connect parent to largest of the smaller
            if(parent->left == t){
                parent->left = replace;
            }else if(parent->right == t){
                parent->right = replace;
            }else{
                // root
                root = replace;
            }
            // connect replacement to removed's left and right
            if(ot->left != replace){
                replace->left = ot->left;
            }
            if(ot->right != replace){
                replace->right = ot->right;
            }
            delete ot;
            ot = NULL;
        }
    }else{
        remove(v, t->left, t);
        remove(v, t->right, t);
    }
    return;
}

template <typename T>
bool BST<T>::contains(const T& v, BSTNode<T>* &t){
    if(t == NULL){
        return false;
    }
    if(t->data == v){
        t->visits++;
        return true;
    }else if(v < t->data){
        return contains(v, t->left);
    }else if(v > t->data){
        return contains(v, t->right);
    }else{  
        return false;
    }
}

template <typename T>
BSTNode<T>* BST<T>::clone(BSTNode<T>* t) const{
    if(t != NULL){
        BSTNode<T>* node = new BSTNode<T>();
        node->data = t->data;
        node->visits = t->visits;
        node->left = clone(t->left);
        node->right = clone(t->right);
        return node;
    }
    return NULL;
}

template <typename T>
void BST<T>::buildFromInputString(const string input){
    if(!empty()){
        makeEmpty(root);
    }
    int s = 0;
    int e = input.find(" ");
    string str;
    T v;
    while(e != -1){
        str = input.substr(s, e - s);
        stringstream ss(str);
        ss >> v;
        insert(v, root);     
        s = e + 1;
        e = input.find(" ", s);
    }
    str = input.substr(s);
    stringstream ss(str);
    ss >> v;
    insert(v, root);
}

template <typename T>
bool BST<T>::empty(){
    if(root == NULL){
        return true;
    }
    return false;
}

template <typename T>
void BST<T>::printInOrder() const{
    if(root != NULL){
        printInOrder(root);
    }
    cout << endl;
}

template <typename T>
void BST<T>::printLevelOrder() const{
    int ht = height(root);
    if(ht > 0){
        for(int i=1; i<=ht; i++){
        printLevelOrder(root, i);
        } 
    }
    cout << endl;
}

template <typename T>
int BST<T>::numOfNodes() const{
    return numOfNodes(root);
}

template <typename T>
int BST<T>::height() const{
    // the recursion starts counting 1, the test program seems to want to start counting at 0
    return height(root) - 1;
}

template <typename T>
void BST<T>::makeEmpty(){
    makeEmpty(root);
}

template <typename T>
void BST<T>::insert(const T& v){
    insert(v, root);
}

template <typename T>
void BST<T>::insert(T&& v){
    insert(move(v), root);    
}

template <typename T>
void BST<T>::remove(const T& v){
    remove(v, root, root);
}

template <typename T>
bool BST<T>::contains(const T& v){
    return contains(v, root);
}

#endif