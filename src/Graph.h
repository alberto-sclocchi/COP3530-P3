#pragma once
#include <map>
#include <utility>
#include <vector>
#include <unordered_map>
#include <set>

struct Edge {
    int time;
    bool closed;
};


class Graph {
private:
    std::map<int, std::vector<std::pair<int, Edge>>> graph;
public:
    void addEdge(int a, int b, int time);

    void toggleEdge(int a, int b);
    int  getEdgeStatus(int a, int b) const;
    bool hasNode(int a) const;
    std::vector<std::pair<int, Edge>> getNeighbors(int a) const;

    std::unordered_map<int, std::pair<int,int>> dijkstra(int source) const;
    bool isConnected(int a, int b) const;             
    int mstCost(const std::set<int>& vertices) const;  
};