#pragma once
#include <map>
#include <utility>
#include <vector>

struct Edge {
    int time;
    bool closed;
};


class Graph {
private:
    std::map<int, pair<int, Edge>> edges;   
public:
    void addEdge(int a, int b, int time);

    bool toggleEdge(int a, int b);          
    int  getEdgeStatus(int a, int b) const; 

    bool dijkstra(int source) const;
    bool hasNode(int id) const;
    bool isConnected(int a, int b) const;             
    int mstCost(int source) const;  
};