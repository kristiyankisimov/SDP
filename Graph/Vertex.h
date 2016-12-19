#ifndef VERTEX_H
#define VERTEX_H

#include <list>
#include <algorithm>

template <typename T>
class Vertex {
public:
    Vertex(const T&);

    void addChild(const T&);
    void removeChild(const T&);

    T* findChild(const T&);
    const T* findChild(const T&) const;

    T getValue() const;
    std::list<T> getChildren() const;

    bool hasChild(const T&) const;
    bool hasChildren() const;

    bool operator==(const T&) const;

private:
    T value;
    std::list<T> children;

    typedef typename std::list<T>::iterator childIter;
    typedef typename std::list<T>::const_iterator constChildIter;
};

template <typename T>
Vertex<T>::Vertex(const T& _value) : value(_value) {
}

template <typename T>
void Vertex<T>::addChild(const T& value) {
    if (!hasChild(value)) {
        children.push_back(value);
    }
}

template <typename T>
void Vertex<T>::removeChild(const T& value) {
    children.remove(value);
}

template <typename T>
T* Vertex<T>::findChild(const T& value) {
    childIter wantedChild = std::find(children.begin(), children.end(), value);

    if (wantedChild == children.end()) {
        return NULL;
    }

    return &(*wantedChild);
}

template <typename T>
const T* Vertex<T>::findChild(const T& value) const {
    constChildIter wantedChild = std::find(children.begin(), children.end(), value);

    if (wantedChild == children.end()) {
        return NULL;
    }

    return &(*wantedChild);
}

template <typename T>
T Vertex<T>::getValue() const {
    return value;
}

template <typename T>
std::list<T> Vertex<T>::getChildren() const {
    return children;
}

template <typename T>
bool Vertex<T>::hasChild(const T& value) const {
    return findChild(value) != NULL;
}

template <typename T>
bool Vertex<T>::hasChildren() const {
    return children.size() > 0;
}

template <typename T>
bool Vertex<T>::operator==(const T& otherValue) const {
    return value == otherValue;
}

#endif
