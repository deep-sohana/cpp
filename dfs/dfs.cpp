#include "dfs.h"
#include <string>
using namespace std;


void GraphTraversal::printPath(std::vector<const Node *> &path)
{
    if (path.empty()) {
        return; 
    }

    string pathStr = "START: ";
    for (size_t i = 0; i < path.size(); ++i) {
        pathStr += to_string(path[i]->getNodeID()) + "->";
    }
    pathStr += "END";

    paths.insert(pathStr);
};


void GraphTraversal::DFS(set<const Node *> &visited, vector<const Node *> &path, const Node *src, const Node *dst)
{
    visited.insert(src);
    path.push_back(src);

    if (src == dst) {
        printPath(path);
    } else {
        for (const Edge *edge : src->getOutEdges()) {
            const Node *neighbor = edge->getDst();
            if (visited.find(neighbor) == visited.end()) {
                DFS(visited, path, neighbor, dst);
            }
        }
    }

    path.pop_back();
    visited.erase(src);
}
