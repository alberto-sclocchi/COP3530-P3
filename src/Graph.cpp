#include "Graph.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <climits>

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

unordered_map<int, pair<int,int>> Graph::dijkstra(int source) const{
    unordered_map<int, pair<int, int>> result;
    for (const auto& vertex : graph) {
        result[vertex.first] = {-1, -1};
    }

    int max_id = graph.rbegin()->first;
    vector<int> distances(max_id + 1, INT_MAX);
    vector<int> predecessors(max_id + 1, -1);
    unordered_set<int> visited;

    distances[source] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> active_vertices;
    active_vertices.push({0, source});

    while (!active_vertices.empty()) {
        int currentVertex = active_vertices.top().second;
        active_vertices.pop();

        if (visited.find(currentVertex) != visited.end()) {
            continue;
        }

        visited.insert(currentVertex);

        for (const auto& neighbor : graph.at(currentVertex)) {
            if (!neighbor.second.closed) {
                int newDist = distances[currentVertex] + neighbor.second.time;
                if (newDist < distances[neighbor.first]) {
                    distances[neighbor.first] = newDist;
                    predecessors[neighbor.first] = currentVertex;
                    active_vertices.push({newDist, neighbor.first});
                }
            }
        }
    }

    for (const auto& vertex : graph) {
        int id = vertex.first;
        if (distances[id] != INT_MAX) {
            result[id] = {distances[id], predecessors[id]};
        }
    }

    return result;
}
