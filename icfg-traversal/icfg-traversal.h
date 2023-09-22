
#ifndef ICFG_TRAVERSAL_H_
#define ICFG_TRAVERSAL_H_

#include "SVF-LLVM/LLVMUtil.h"
#include "SVF-LLVM/SVFIRBuilder.h"
using namespace SVF;

class ICFGTraversal
{

public:

    ICFGTraversal(SVFIR *p) : pag(p) {}

    virtual void printICFGPath(std::vector<const ICFGNode *> &path);

    void DFS(std::set<const ICFGNode *> &visited, std::vector<const ICFGNode *> &path, std::stack<const SVFInstruction *> &callstack, const ICFGNode *src, const ICFGNode *dst);
    
    // Identify source nodes on ICFG (i.e., call instruction with its callee function named 'src')
    virtual std::set<const CallICFGNode *> &identifySources()
    {
        for (const CallICFGNode *cs : pag->getCallSiteSet())
        {
            const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
            if (fun->getName() == "source")
            {
                sources.insert(cs);
            }
        }
        return sources;
    }

    // Identify sink nodes on ICFG (i.e., call instruction with its callee function named 'sink')
    virtual std::set<const CallICFGNode *> &identifySinks()
    {
        for (const CallICFGNode *cs : pag->getCallSiteSet())
        {
            const SVFFunction *fun = SVFUtil::getCallee(cs->getCallSite());
            if (fun->getName() == "sink")
            {
                sinks.insert(cs);
            }
        }
        return sinks;
    }
    std::set<std::string>& getPaths(){
        return paths;
    }

protected:
    std::set<const CallICFGNode *> sources;
    std::set<const CallICFGNode *> sinks;
    std::set<std::string> paths;
    SVFIR *pag;
};

#endif
