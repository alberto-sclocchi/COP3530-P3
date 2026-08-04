#pragma once
#include <map>
#include <utility>
#include <vector>
#include <unordered_map>

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

    std::unordered_map<int, std::pair<int,int>> dijkstra(int source) const;
    bool isConnected(int a, int b) const;             
    int mstCost(int source) const;  
};