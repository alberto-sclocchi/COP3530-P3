#include "Graph.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <climits>
#include <set>

using namespace std;

void Graph::addEdge(int from, int to, int weight) {
    //add edge both ways, as it is an undirected graph
    Edge edge{weight, false};
    graph[from].push_back(make_pair(to, edge));
    graph[to].push_back(make_pair(from, edge));
}

void Graph::toggleEdge(int from, int to) {

    //toogle closed for first edge
    for(auto& edge : graph[from]) {
        if(edge.first == to) {
            edge.second.closed = !edge.second.closed;
        }
    }

    //toogle closed for second edge
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
    //return false if either vertices are not in the graph
    if(graph.find(a) == graph.end() || graph.find(b) == graph.end()) {
        return false;
    }

    //use DFS to check for s-t path 

    stack<int> s;
    unordered_set<int> visited;
    s.push(a);
    visited.insert(a);

    while (!s.empty()) {
        int current = s.top();
        s.pop();

        for (const auto& neighbor : getNeighbors(current)) {
            //return true if edge was found and it is not closed
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

    //use a map to track result -> vertex = {shortest_distance, predecessor};
    unordered_map<int, pair<int, int>> result;
    for (const auto& vertex : graph) {
        result[vertex.first] = {-1, -1};
    }

    if(graph.empty() || graph.find(source) == graph.end()) return result;

    int max_id = graph.rbegin()->first;
    vector<int> distances(max_id + 1, INT_MAX);
    vector<int> predecessors(max_id + 1, -1);
    unordered_set<int> visited;

    //set source distance to 0
    distances[source] = 0;

    //priority queue (min heap)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> active_vertices;
    active_vertices.push({0, source});

    while (!active_vertices.empty()) {
        //get top vertex -> shortest distance
        int currentVertex = active_vertices.top().second;
        active_vertices.pop();

        //check if already visited
        if (visited.find(currentVertex) != visited.end()) {
            continue;
        }

        visited.insert(currentVertex);

        for (const auto& neighbor : getNeighbors(currentVertex)) {
            if (!neighbor.second.closed) {
                int newDist = distances[currentVertex] + neighbor.second.time;
                //relaxation
                if (newDist < distances[neighbor.first]) {
                    distances[neighbor.first] = newDist;
                    predecessors[neighbor.first] = currentVertex;

                    //push in the priority queue
                    active_vertices.push({newDist, neighbor.first});
                }
            }
        }
    }

    //store result in the map to return
    for (const auto& vertex : graph) {
        int id = vertex.first;
        
        //if distance is still equal to infinity, then 
        //vertex is unreachable. Leave it as default. 
        if (distances[id] != INT_MAX) {
            result[id] = {distances[id], predecessors[id]};
        }
    }

    return result;
}

bool Graph::hasNode(int a) const {
    return graph.find(a) != graph.end();
}

vector<pair<int, Edge>> Graph::getNeighbors(int a) const {
    if (graph.find(a) != graph.end()) {
        return graph.at(a);
    }
    return {};
}

int Graph::mstCost(const set<int>& vertices) const {
    if (vertices.size() <= 1) return 0;

    std::unordered_set<int> visited;
    int total = 0;

    //priority queue (min heap)
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
    pq.push({0, *vertices.begin()});

    while (!pq.empty()) {
        auto top = pq.top();
        int weight = top.first;
        int vertex = top.second;
        pq.pop();

        //check if visited
        //continue if already visited
        if (visited.find(vertex) != visited.end()) continue;

        //add weight to the mst cost
        visited.insert(vertex);
        total += weight;

        for (const auto& neighbor : getNeighbors(vertex)) {
            //check if vertex was never visited before,
            //if it is part of the subgraph, and if it is not closed
            if (neighbor.second.closed) continue;                
            if (!vertices.count(neighbor.first)) continue;        
            if (visited.find(neighbor.first) != visited.end()) continue;
            
            pq.push({neighbor.second.time, neighbor.first});
        }
    }

    return total;
}
