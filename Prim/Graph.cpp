#include "Graph.h"

bool Graph::addNode(int node) {
    if (hasNode(node))
        return false;

    Edge e;
    e.end = node;
    e.weight = 0;

    vector<Edge> v;
    v.push_back(e);
    adj.push_back(v);

    return true;
}

bool Graph::removeNode(int node) {
    if (!hasNode(node))
        return false;

    for (int i = 0; i < adj.size(); i++) {
        if (adj[i][0].end == node) {
            adj.erase(adj.begin() + i);
            break;
        }
    }

    for (int i = 0; i < adj.size(); i++) {
        for (int j = 0; j < adj[i].size(); j++) {
            if (adj[i][j].end == node) {
                adj[i].erase(adj[i].begin() + j);
                break;
            }
        }
    }
    return true;
}

bool Graph::hasLink(int start, int end) const {
    for (int i = 0; i < adj.size(); i++) {
        if (adj[i][0].end == start) {
            for (int j = 0; j < adj[i].size(); j++) {
                if (adj[i][j].end == end)
                    return true;
            }
            return false;
        }
    }
    return false;
}

bool Graph::hasNode(int node) const {
    for (int i = 0; i < adj.size(); i++)
        if (adj[i][0].end == node)
            return true;
    return false;
}

bool Graph::isEmpty() const {
    return adj.size() == 0;
}

bool Graph::addLink(int start, int end, int w) {
    if (hasLink(start, end))
        return false;

    addNode(start);
    addNode(end);

    for (int i = 0; i < adj.size(); i++)
        if (adj[i][0].end == start) {
            Edge e;
            e.end = end;
            e.weight = w;
            adj[i].push_back(e);
            break;
        }

    return true;
}

bool Graph::removeLink(int start, int end) {
    if (!hasLink(start, end))
        return false;

    for (int i = 0; i < adj.size(); i++) {
        if (adj[i][0].end == start) {
            for (int j = 0; j < adj[i].size(); j++) {
                if (adj[i][j].end == end)
                    adj[i].erase(adj[i].begin() + j);
            }
            return false;
        }
    }
}

vector<int> Graph::nodes() const {
    vector<int> nodes;

    for (int i = 0; i < adj.size(); i++) {
        nodes.push_back(adj[i][0].end);
    }

    return nodes;
}

vector<Edge> Graph::adj(int node) const {
    vector<Edge> nodes;

    if (hasNode(node)) {
        for (int i = 0; i < adj.size(); i++) {
            if (adj[i][0].end == node)
                for (int j = 1; j < adj[i].size(); j++) {
                    nodes.push_back(adj[i][j]);
                }
        }
    }
    return nodes;
}
