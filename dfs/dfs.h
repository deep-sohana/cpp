
#ifndef DFS_H_
#define DFS_H_
#include <iostream>
#include <set>
#include <vector>
//declare
class Node;
class Edge;

class Node
{
private:
    int nodeID;
    std::set<const Edge *> outEdges; // outgoing edges of this node

public:
    // constructor
    Node(int i) { 
        nodeID = i; 
    }

    // Get the private attribute nodeID
    int getNodeID() const { 
        return nodeID; 
    }

    // Get the private attribute outEdges 
    std::set<const Edge *> getOutEdges() const { 
        return outEdges; 
    }

    // Add an edge into outEdges
    void addOutEdge(const Edge *edge) { 
        outEdges.insert(edge); 
    }
};

class Edge
{
private:
    Node *src;  // source node of the edge
    Node *dst;  // target node of the edge

public:
    // Constructor
    Edge(Node *s, Node *d) : src(s), dst(d){
    }
    // Get the source node
    Node *getSrc() const { 
        return src; 
    }

    // Get the target node
    Node *getDst() const { 
        return dst; 
    }
};

class Graph
{
private:
    std::set<const Node *> nodes;   // a set of nodes on the graph

public:
    Graph(){};
    // Get all the nodes of the graph
    std::set<const Node *> &getNodes() { 
        return nodes; 
    }
    // Add a node into the graph
    void addNode(const Node *node) { 
        nodes.insert(node);
    }
};


class GraphTraversal
{
public:
    // Constructor
    GraphTraversal(){};
    // Destructor
    ~GraphTraversal(){};

    void printPath(std::vector<const Node *> &path);

    void DFS(std::set<const Node *> &visited, std::vector<const Node *> &path, const Node *src, const Node *dst);

    // Retrieve all paths (a set of strings) during graph traversal
    std::set<std::string>& getPaths(){
        return paths;
    } 

private:
    std::set<std::string> paths;
};

#endif