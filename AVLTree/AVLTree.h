#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include "AVLTreeException.h"

#include <iostream>

template <typename K, typename V>
class AVLTree {
public:
    AVLTree();
    AVLTree(const AVLTree&);
    ~AVLTree();
    AVLTree& operator=(const AVLTree&);

    void insert(const K&, const V&);
    void remove(const K&);

    V& find(const K&);

    int getSize() const;
    int getHeight() const;
    bool isEmpty() const;

    void inorder();
private:
    Node<K, V>* root;
    int size;

    void insert(Node<K, V>*&, const K&, const V&);

    void findAndRemove(Node<K, V>*&, const K&);
    bool remove(Node<K, V>*&);
    void removeMinAndSwap(Node<K, V>*&, Node<K, V>*&);

    V& find(Node<K, V>*&, const K&);

    void rotateLeft(Node<K, V>*&);
    void rotateRight(Node<K, V>*&);
    void balance(Node<K, V>*&);

    void copy(const AVLTree&);
    void copy(Node<K, V>*&, const Node<K, V>*&);
    void del(Node<K, V>*&);

    void inorder(Node<K, V>*&);
};

template <typename K, typename V>
AVLTree<K, V>::AVLTree() : root(NULL), size(0) {
}

template <typename K, typename V>
AVLTree<K, V>::AVLTree(const AVLTree& other) {
    copy(other);
}

template <typename K, typename V>
AVLTree<K, V>::~AVLTree() {
    del(root);
}

template <typename K, typename V>
AVLTree<K, V>& AVLTree<K, V>::operator=(const AVLTree& other) {
    if (this != &other) {
        del(root);
        copy(other);
    }
    return *this;
}

template <typename K, typename V>
void AVLTree<K, V>::insert(const K& key, const V& value) {
    insert(root, key, value);
    ++size;
}

template <typename K, typename V>
void AVLTree<K, V>::remove(const K& key) {
    findAndRemove(root, key);
    --size;
}

template <typename K, typename V>
V& AVLTree<K, V>::find(const K& key) {
    return find(root, key);
}

template <typename K, typename V>
int AVLTree<K, V>::getSize() const {
    return size;
}

template <typename K, typename V>
int AVLTree<K, V>::getHeight() const {
    return root != NULL ? root->height : 0;
}

template <typename K, typename V>
bool AVLTree<K, V>::isEmpty() const {
    return root == NULL;
}

template <typename K, typename V>
void AVLTree<K, V>::insert(Node<K, V>*& node, const K& key, const V& value) {
    if (node == NULL) {
        node = new Node<K, V>(key, value);
        return;
    }
    
    if (key < node->key) {
        insert(node->left, key, value);
        node->reloadHeight();
    } else if (key > node->key) {
        insert(node->right, key, value);
        node->reloadHeight();
    } else {
        node->value = value;
        --size;
        return;
    }
    balance(node);
}

template <typename K, typename V>
void AVLTree<K, V>::findAndRemove(Node<K, V>*& node, const K& key) {
    if (node == NULL) {
        throw KeyNotFoundError();
    }

    if (key < node->key) {
        findAndRemove(node->left, key);
        node->reloadHeight();
    } else if (key > node->key) {
        findAndRemove(node->right, key);
        node->reloadHeight();
    } else {
        if (remove(node)) {
            return;
        }
    }

    balance(node);
}

template <typename K, typename V>
bool AVLTree<K, V>::remove(Node<K, V>*& node) {
    if (node->isLeaf()) {
        delete node;
        node = NULL;
        return true;
    } else if (node->left == NULL || node->right == NULL) {
        Node<K, V>* left = node->left;
        Node<K, V>* right = node->right;
        delete node;
        node = left == NULL ? right : left;
        return true;
    } else {
        removeMinAndSwap(node->right, node);
        node->reloadHeight();
        return false;
    }
}

template <typename K, typename V>
void AVLTree<K, V>::removeMinAndSwap(Node<K, V>*& minNode, Node<K, V>*& swapNode) {
    if (minNode->left == NULL) {
        swapNode->key = minNode->key;
        swapNode->value = minNode->value;

        Node<K, V>* right = minNode->right;

        delete minNode;

        minNode = right;
        return;
    } else {
        removeMinAndSwap(minNode->left, swapNode);
        minNode->reloadHeight();
    }

    balance(minNode);
}

template <typename K, typename V>
V& AVLTree<K, V>::find(Node<K, V>*& node, const K& key) {
    if (node != NULL) {
        if (key < node->key) {
            return find(node->left, key);
        } else if (node->key < key) {
            return find(node->right, key);
        } else {
            return node->value;
        }
    } else {
        throw KeyNotFoundError();
    }
}

template <typename K, typename V>
void AVLTree<K, V>::rotateLeft(Node<K, V>*& node) {
    Node<K, V>* helpNode = node->right;

    node->right = helpNode->left;
    helpNode->left = node;

    node->reloadHeight();
    helpNode->reloadHeight();

    node = helpNode;
}

template <typename K, typename V>
void AVLTree<K, V>::rotateRight(Node<K, V>*& node) {
    Node<K, V>* helpNode = node->left;

    node->left = helpNode->right;
    helpNode->right = node;

    node->reloadHeight();
    helpNode->reloadHeight();

    node = helpNode;
}

template <typename K, typename V>
void AVLTree<K, V>::balance(Node<K, V>*& node) {
    if (node->balance() == -2) {
        if (node->left->balance() == 1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    } else if (node->balance() == 2) {
        if (node->right->balance() == -1) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
}

template <typename K, typename V>
void AVLTree<K, V>::copy(const AVLTree& other) {
    size = other.size;
    copy(root, other.root);
}

template <typename K, typename V>
void AVLTree<K, V>::copy(Node<K, V>*& node, const Node<K, V>*& other) {
    if (other != NULL) {
        node = new Node<K, V>(*other);
        copy(node->left, other->left);
        copy(node->right, other->right);
    } else {
        node = NULL;
    }
}

template <typename K, typename V>
void AVLTree<K, V>::del(Node<K, V>*& node) {
    if (node != NULL) {
        del(node->left);
        del(node->right);
        delete node;
    }
}

template <typename K, typename V>
void AVLTree<K, V>::inorder() {
    inorder(root);
    std::cout << std::endl;
}

template <typename K, typename V>
void AVLTree<K, V>::inorder(Node<K, V>*& node) {
    if (node) {
        inorder(node->left);
        K left = node->left ? node->left->key : K();
        K right = node->right ? node->right->key : K();
        std::cout << "[" << node->key << "(" << left << ", " << right << ")]" << " ";
        inorder(node->right);
    }
}
#endif

