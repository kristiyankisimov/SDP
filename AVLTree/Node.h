#ifndef NODE_H
#define NODE_H

template <typename K, typename V>
class AVLTree;

template <typename K, typename V>
class Node {
    K key;
    V value;

    int height;

    Node* left;
    Node* right;

    Node(const K&, const V&);

    bool isLeaf() const;
    int balance() const;
    void reloadHeight();

    friend class AVLTree<K, V>;
};

template <typename K, typename V>
Node<K, V>::Node(const K& _key, const V& _value) : key(_key), value(_value),
height(1), left(NULL), right(NULL) {
}

template <typename K, typename V>
bool Node<K, V>::isLeaf() const {
    return left == NULL && right == NULL;
}

template <typename K, typename V>
int Node<K, V>::balance() const {
    int leftHeight = (left != NULL ? left->height : 0);
    int rightHeight = (right != NULL ? right->height : 0);
    return rightHeight - leftHeight;
}

template <typename K, typename V>
void Node<K, V>::reloadHeight() {
    int leftHeight = (left != NULL ? left->height : 0);
    int rightHeight = (right != NULL ? right->height : 0);
    height = 1 + (leftHeight >= rightHeight ? leftHeight : rightHeight);
}

#endif
