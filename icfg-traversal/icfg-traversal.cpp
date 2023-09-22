
#include <set>
#include "icfg-traversal.h"
#include <iostream>
using namespace SVF;
using namespace std;


void ICFGTraversal::printICFGPath(std::vector<const ICFGNode *> &path)
{
     if (path.empty()) {
        return; // No path exists.
    }

    string pathStr = "START: ";
    for (size_t i = 0; i < path.size(); ++i) {
        pathStr += to_string(path[i]->getId()) + "->";
    }
    pathStr += "END";

    paths.insert(pathStr);
}


void ICFGTraversal::DFS(std::set<const ICFGNode *> &visited, std::vector<const ICFGNode *> &path, std::stack<const SVFInstruction*> &callstack, const ICFGNode *src, const ICFGNode *dst)
{
    visited.insert(src);
    path.push_back(src);

    if (src == dst) {
        printICFGPath(path);
    } else {
        for (const ICFGEdge *edge: src->getOutEdges()){
            const ICFGNode *neighbour = edge->getDstNode();

            if(visited.find(neighbour) == visited.end()){
                if(edge->isIntraCFGEdge()) {
                    DFS(visited, path, callstack, neighbour, dst);
                } else if (edge->isCallCFGEdge()) {
                    const CallCFGEdge *callEdge = SVFUtil::dyn_cast<CallCFGEdge>(edge);
                    callstack.push(callEdge->getCallSite());
                    DFS(visited, path, callstack, neighbour, dst);
                } else if (edge->isRetCFGEdge()) {
                    const RetCFGEdge *retEdge = SVFUtil::dyn_cast<RetCFGEdge>(edge);
                    if (!callstack.empty() && callstack.top() == retEdge->getCallSite()) {
                        callstack.pop();
                        DFS(visited, path, callstack, neighbour, dst);
                    } 
                }                
            }
        }
    }

    path.pop_back();
    visited.erase(src);
}