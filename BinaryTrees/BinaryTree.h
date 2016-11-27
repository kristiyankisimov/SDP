#ifndef BINARYTREE_H
#define BINARYTREE_H

#include<iostream>

#include "Node.h"
#include "TreeExceptions.h"

template<typename K, typename V>
class BinaryTree {
public:
    BinaryTree();
    BinaryTree(const BinaryTree<K, V>&);
    virtual ~BinaryTree();
    BinaryTree(const K&, const V&, const BinaryTree<K, V>&, const BinaryTree<K, V>&);

    BinaryTree<K, V>& operator=(const BinaryTree<K, V>&);

    V& getRootData() const;

    BinaryTree<K, V> getLeftTree();
    BinaryTree<K, V> getRightTree();

    void inorder();
    void preorder();
    void postorder();

    bool isEmpty() const;
    bool isLeaf() const;

    int height();
protected:
    Node<K, V>* root;
private:

    BinaryTree(Node<K, V>*& node) {
        copyTree(root, node);
    }
    void copyTree(Node<K, V>*&, const Node<K, V>*&);
    void deleteTree(Node<K, V>*&);
    int height(Node<K, V>*&);
    void inorder(Node<K, V>*&);
    void preorder(Node<K, V>*&);
    void postorder(Node<K, V>*&);
};

template<typename K, typename V>
BinaryTree<K, V>::BinaryTree() : root(NULL) {
}

template<typename K, typename V>
BinaryTree<K, V>::BinaryTree(const BinaryTree<K, V>& other) {
    if (!other.root) {
        root = NULL;
    } else {
        copyTree(root, other.root);
    }
}

template<typename K, typename V>
BinaryTree<K, V>::BinaryTree(const K& key, const V& value, const BinaryTree<K, V>& leftTree,
        const BinaryTree<K, V>& rightTree) {
    root = new Node<K, V>(key, value);
    copyTree(root->left, leftTree.root);
    copyTree(root->right, rightTree.root);
}

template<typename K, typename V>
BinaryTree<K, V>::~BinaryTree() {
    deleteTree(root);
}

template<typename K, typename V>
BinaryTree<K, V>& BinaryTree<K, V>::operator=(const BinaryTree<K, V>& other) {
    if (this != &other) {
        if (root != NULL) {
            deleteTree(root);
        }

        if (!other.root) {
            root = NULL;
        } else {
            copyTree(root, other.root);
        }
    }
    return *this;
}

template<typename K, typename V>
V& BinaryTree<K, V>::getRootData() const {
    if (root != NULL) {
        return root->value;
    }
    throw EmptyTreeError();
}

template<typename K, typename V>
BinaryTree<K, V> BinaryTree<K, V>::getLeftTree() {
    if (root != NULL) {
        return BinaryTree<K, V>(root->left);
    } else {
        return BinaryTree<K, V>();
    }
}

template<typename K, typename V>
BinaryTree<K, V> BinaryTree<K, V>::getRightTree() {
    if (root != NULL) {
        return BinaryTree<K, V>(root->right);
    } else {
        return BinaryTree<K, V>();
    }
}

template<typename K, typename V>
void BinaryTree<K, V>::inorder() {
    inorder(root);
    std::cout << std::endl;
}

template<typename K, typename V>
void BinaryTree<K, V>::inorder(Node<K, V>*& node) {
    if (node != NULL) {
        inorder(node->left);
        std::cout << "(" << node->key << ", " << node->value << ") ";
        inorder(node->right);
    }
}

template<typename K, typename V>
void BinaryTree<K, V>::preorder() {
    preorder(root);
    std::cout << std::endl;
}

template<typename K, typename V>
void BinaryTree<K, V>::preorder(Node<K, V>*& node) {
    if (node != NULL) {
        std::cout << "(" << node->key << ", " << node->value << ") ";
        preorder(node->left);
        preorder(node->right);
    }
}

template<typename K, typename V>
void BinaryTree<K, V>::postorder() {
    postorder(root);
    std::cout << std::endl;
}

template<typename K, typename V>
void BinaryTree<K, V>::postorder(Node<K, V>*& node) {
    if (node != NULL) {
        postorder(node->left);
        postorder(node->right);
        std::cout << "(" << node->key << ", " << node->value << ") ";
    }
}

template<typename K, typename V>
bool BinaryTree<K, V>::isEmpty() const {
    return root == NULL;
}

template<typename K, typename V>
bool BinaryTree<K, V>::isLeaf() const {
    if (root != NULL) {
        return root->left == NULL && root->right == NULL;
    }
    throw EmptyTreeError();
}

template<typename K, typename V>
int BinaryTree<K, V>::height() {
    return height(root);
}

template<typename K, typename V>
int BinaryTree<K, V>::height(Node<K, V>*& node) {
    if (node == NULL) {
        return 0;
    }
    int rightHeight = height(node->right);
    int leftHeight = height(node->left);
    return 1 + (rightHeight >= leftHeight ? rightHeight : leftHeight);
}

template<typename K, typename V>
void BinaryTree<K, V>::copyTree(Node<K, V>*& node, const Node<K, V>*& other) {
    if (!other) {
        node = NULL;
    } else {
        node = new Node<K, V>(other->key, other->value);
        copyTree(node->left, other->left);
        copyTree(node->right, other->right);
    }
}

template<typename K, typename V>
void BinaryTree<K, V>::deleteTree(Node<K, V>*& node) {
    if (node != NULL) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

#endif
