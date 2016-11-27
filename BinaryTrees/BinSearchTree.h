#ifndef BINSEARCHTREE_H
#define BINSEARCHTREE_H

#include "BinaryTree.h"

template<typename K, typename V>
class BinSearchTree : public BinaryTree<K, V> {
public:
    BinSearchTree();
    BinSearchTree(const K&, const V&, const BinSearchTree<K, V>&, const BinSearchTree<K, V>&);

    bool find(const K&) const;
    V& findAndReturn(const K&);
    void insertNode(const K&, const V&);
    void deleteNode(const K&);
private:
    bool find(const Node<K, V>*&, const K&) const;
    V& findAndReturn(Node<K, V>*&, const K&);
    void insertNode(Node<K, V>*&, const K&, const V&);
    void deleteNode(Node<K, V>*&, const K&);
};

template<typename K, typename V>
BinSearchTree<K, V>::BinSearchTree() : BinaryTree<K, V>() {
}

template<typename K, typename V>
BinSearchTree<K, V>::BinSearchTree(const K& key,
        const V& value, const BinSearchTree<K, V>& leftTree,
        const BinSearchTree<K, V>& rightTree)
: BinaryTree<K, V>(key, value, leftTree, rightTree) {
}

template<typename K, typename V>
bool BinSearchTree<K, V>::find(const K& key) const {
    return find(BinaryTree<K, V>::root, key);
}

template<typename K, typename V>
bool BinSearchTree<K, V>::find(const Node<K, V>*& node, const K& key) const {
    if (node == NULL) {
        return false;
    } else if (key < node->key) {
        return find(node->left, key);
    } else if (node->key < key) {
        return find(node->right, key);
    } else {
        return true;
    }
}

template<typename K, typename V>
V& BinSearchTree<K, V>::findAndReturn(const K& key) {
    return findAndReturn(BinaryTree<K, V>::root, key);
}

template<typename K, typename V>
V& BinSearchTree<K, V>::findAndReturn(Node<K, V>*& node, const K& key) {
    if (node == NULL) {
        throw KeyNotFoundError();
    }
    if (key < node->key) {
        return findAndReturn(node->left, key);
    } else if (node->key < key) {
        return findAndReturn(node->right, key);
    } else {
        return node->value;
    }
}

template<typename K, typename V>
void BinSearchTree<K, V>::insertNode(const K& key, const V& value) {
    insertNode(BinaryTree<K, V>::root, key, value);
}

template<typename K, typename V>
void BinSearchTree<K, V>::insertNode(Node<K, V>*& node, const K& key, const V& value) {
    if (node == NULL) {
        node = new Node<K, V>(key, value);
    } else if (key < node->key) {
        insertNode(node->left, key, value);
    } else if (key > node->key) {
        insertNode(node->right, key, value);
    } else {
        node->value = value;
    }
}

template<typename K, typename V>
void BinSearchTree<K, V>::deleteNode(const K& key) {
    deleteNode(BinaryTree<K, V>::root, key);
}

template<typename K, typename V>
void BinSearchTree<K, V>::deleteNode(Node<K, V>*& node, const K& key) {
    if (node == NULL) {
        return;
    }

    if (key < node->key) {
        deleteNode(node->left, key);
    } else if (key > node->key) {
        deleteNode(node->right, key);
    } else {
        Node<K, V>* helpNode;
        if (node->left == NULL) {
            helpNode = node->right;
            delete node;
            node = helpNode;
        } else if (node->right == NULL) {
            helpNode = node->left;
            delete node;
            node = helpNode;
        } else {
            helpNode = node->right;
            while (helpNode->left) {
                helpNode = helpNode->left;
            }

            node->key = helpNode->key;
            node->value = helpNode->value;
            deleteNode(node->right, helpNode->key);
        }
    }
}

#endif

