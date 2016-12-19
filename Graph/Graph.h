#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <algorithm>

#include "Vertex.h"

template <typename T>
class Graph {
public:
    void addVertex(const T&);
    void removeVertex(const T&);

    void addEdge(const T&, const T&);
    void removeEdge(const T&, const T&);

    Vertex<T>* findVertex(const T&);
    const Vertex<T>* findVertex(const T&) const;

    std::list<T> getVertices() const;

    bool hasVertex(const T&) const;
    bool hasEdge(const T&, const T&) const;

    bool isEmpty() const;

private:
    std::list<Vertex<T> > graph;

    typedef typename std::list<Vertex<T> >::iterator vertexIter;
    typedef typename std::list<Vertex<T> >::const_iterator constVertexIter;
};

template <typename T>
void Graph<T>::addVertex(const T& value) {
    if (!hasVertex(value)) {
        graph.push_back(Vertex<T>(value));
    }
}

template <typename T>
void Graph<T>::removeVertex(const T& value) {
    Vertex<T>* wantedVertex = findVertex(value);

    if (wantedVertex != 0) {
        graph.remove(*wantedVertex);
    }

    for (vertexIter iter = graph.begin(); iter != graph.end(); ++iter) {
        iter->removeChild(value);
    }
}

template <typename T>
void Graph<T>::addEdge(const T& startValue, const T& endValue) {
    addVertex(startValue);
    addVertex(endValue);

    Vertex<T>* addedStart = findVertex(startValue);
    addedStart->addChild(endValue);
}

template <typename T>
void Graph<T>::removeEdge(const T& startValue, const T& endValue) {
    Vertex<T>* wantedVertex = findVertex(startValue);

    if (wantedVertex != 0) {
        wantedVertex->removeChild(endValue);
    }
}

template <typename T>
Vertex<T>* Graph<T>::findVertex(const T& value) {
    vertexIter wantedVertex = std::find(graph.begin(), graph.end(), value);

    if (wantedVertex == graph.end()) {
        return 0;
    }

    return &(*wantedVertex);
}

template <typename T>
const Vertex<T>* Graph<T>::findVertex(const T& value) const {
    constVertexIter wantedVertex = std::find(graph.begin(), graph.end(), value);

    if (wantedVertex == graph.end()) {
        return 0;
    }

    return &(*wantedVertex);
}

template <typename T>
std::list<T> Graph<T>::getVertices() const {
    std::list<T>* vertices = new std::list<T>;

    for (constVertexIter iter = graph.begin(); iter != graph.end(); ++iter) {
        vertices->push_back(iter->getValue());
    }

    return *vertices;
}

template <typename T>
bool Graph<T>::hasVertex(const T& value) const {
    return findVertex(value);
}

template <typename T>
bool Graph<T>::hasEdge(const T& startValue, const T& endValue) const {
    const Vertex<T>* startVertex = findVertex(startValue);

    if (startVertex != 0) {
        return startVertex->hasChild(endValue);
    }

    return false;
}

template <typename T>
bool Graph<T>::isEmpty() const {
    for (constVertexIter iter = graph.begin(); iter != graph.end(); ++iter) {
        if (iter->hasChildren()) {
            return false;
        }
    }

    return true;
}

#endif
