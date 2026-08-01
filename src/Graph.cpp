#include "Graph.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

void Graph::addEdge(int from, int to, int weight) {
    Edge edge{weight, false};
    graph[from].push_back(make_pair(to, edge));
    graph[to].push_back(make_pair(from, edge));
}

void Graph::toggleEdge(int from, int to) {
    for(auto& edge : graph[from]) {
        if(edge.first == to) {
            edge.second.closed = !edge.second.closed;
        }
    }

    for(auto& edge : graph[to]) {
        if(edge.first == from) {
            edge.second.closed = !edge.second.closed;
        }
    }
}

int Graph::getEdgeStatus(int from, int to) const {
    auto it = graph.find(from);
    if (it != graph.end()) {
        for (const auto& edge : it->second) {
            if (edge.first == to) {
                return edge.second.closed ? 1 : 0;
            }
        }
    }
    return -1; //edge does not exist
}


bool Graph::isConnected(int a, int b) const {
    if(graph.find(a) == graph.end() || graph.find(b) == graph.end()) {
        return false;
    }
    stack<int> s;
    unordered_set<int> visited;
    s.push(a);
    visited.insert(a);
    while (!s.empty()) {
        int current = s.top();
        s.pop();

        vector<pair<int, Edge>> neighbors = graph.at(current);

        for (const auto& neighbor : neighbors) {
            if(neighbor.first == b && !neighbor.second.closed) {
                return true;
            }
            if (!neighbor.second.closed && visited.find(neighbor.first) == visited.end()) {
                s.push(neighbor.first);
                visited.insert(neighbor.first);
            }
        }
    }
    return false;
}

