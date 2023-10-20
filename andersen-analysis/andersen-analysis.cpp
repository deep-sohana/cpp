
#include "SVF-LLVM/LLVMUtil.h"
#include "SVF-LLVM/SVFIRBuilder.h"
#include "WPA/Andersen.h"
#include "andersen-analysis.h"
using namespace SVF;
using namespace llvm;
using namespace std;


void AndersenPTA::solveWorklist(){
    processAllAddr();

    // Keep solving until workList is empty.
    while (!isWorklistEmpty())
    {
        NodeID p = popFromWorklist();

        for (NodeID o : getPts(p))
        {
            for (ConstraintEdge *edge : consCG->getConstraintNode(p)->getStoreInEdges())
            {
                const StoreCGEdge *store = SVFUtil::cast<StoreCGEdge>(edge);
                NodeID q = store->getSrcID();

                if(addCopyEdge(q, o))
                    pushIntoWorklist(o);
            } 

            for (ConstraintEdge *edge : consCG->getConstraintNode(p)->getLoadOutEdges())
            {
                const LoadCGEdge *load = SVFUtil::cast<LoadCGEdge>(edge);
                NodeID q = load->getDstID();

                if(addCopyEdge(o, q))
                    pushIntoWorklist(q);
            }
        }

        for (ConstraintEdge *edge : consCG->getConstraintNode(p)->getDirectOutEdges())
        {
            const CopyCGEdge *copy = SVFUtil::cast<CopyCGEdge>(edge);
            NodeID x = copy->getDstID();
            
            if(unionPts(x, p))
                pushIntoWorklist(x);
        }
    }
}

// Process all address constraints to initialize pointers' points-to sets
void AndersenPTA::processAllAddr(){
    for (ConstraintGraph::const_iterator nodeIt = consCG->begin(), nodeEit = consCG->end(); nodeIt != nodeEit; nodeIt++)
    {
        ConstraintNode *cgNode = nodeIt->second;
        for (ConstraintEdge* edge : cgNode->getAddrInEdges()) {
            const AddrCGEdge *addr = SVFUtil::cast<AddrCGEdge>(edge);
            NodeID dst = addr->getDstID();
            NodeID src = addr->getSrcID();
            if (addPts(dst, src))
                pushIntoWorklist(dst);
        }
    }
}
