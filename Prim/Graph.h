#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int end;
    int weight;
};

class Graph {
public:
    bool addNode(int node);
    bool removeNode(int node);

    bool addLink(int start, int end, int weight);
    bool removeLink(int start, int end);

    bool isEmpty() const;

    bool hasNode(int node) const;
    bool hasLink(int start, int end) const;

    vector<int> nodes() const;
    vector<Edge> adj(int code) const;
private:
    vector<vector<Edge> > adj;
};

#endif
