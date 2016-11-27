#ifndef NODE_H
#define NODE_H

template<typename K, typename V>
class BinaryTree;

template<typename K, typename V>
class BinSearchTree;

template<typename K, typename V>
class Node {
    K key;
    V value;
    Node<K, V>* left;
    Node<K, V>* right;

    Node(const K& _key, const V& _value, Node<K, V>* _left = NULL,
            Node<K, V>* _right = NULL) : key(_key), value(_value),
    left(_left), right(_right) {
    }

    friend class BinaryTree<K, V>;
    friend class BinSearchTree<K, V>;
};

#endif

