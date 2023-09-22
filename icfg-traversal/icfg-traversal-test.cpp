
#include <iostream>
#include "icfg-traversal.h"

void Test1()
{

    std::vector<std::string> moduleNameVec = {"./Assignment-2/testcase/bc/test1.ll"};

    SVFModule *svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
 
    /// Build Program Assignment Graph (SVFIR)
    SVFIRBuilder builder(svfModule);
    SVFIR *pag = builder.build();
    ICFG *icfg = pag->getICFG();
 
    icfg->dump("./Assignment-2/testcase/dot/test1.ll.icfg");
    std::vector<const ICFGNode *> path;
    std::stack<const SVFInstruction *>callstack;
    std::set<const ICFGNode *> visited;
    ICFGTraversal *gt = new ICFGTraversal(pag);
    for (const CallICFGNode *src : gt->identifySources())
    {
        for (const CallICFGNode *snk : gt->identifySinks())
        {
            gt->DFS(visited, path, callstack, src, snk);
        }
    }
    std::set<std::string> expected = {"START: 16->1->2->END"};
    assert(expected == gt->getPaths() && "test1 failed!");
    std::cout << "test1 passed!" << "\n";
    SVFIR::releaseSVFIR();
    LLVMModuleSet::releaseLLVMModuleSet();
    delete gt;
}

void Test2()
{

    std::vector<std::string> moduleNameVec = {"./Assignment-2/testcase/bc/test2.ll"};

    SVFModule *svfModule = LLVMModuleSet::getLLVMModuleSet()->buildSVFModule(moduleNameVec);
 
    /// Build Program Assignment Graph (SVFIR)
    SVFIRBuilder builder(svfModule);
    SVFIR *pag = builder.build();
    ICFG *icfg = pag->getICFG();
    
    icfg->dump("./Assignment-2/testcase/dot/test2.ll.icfg");
    std::vector<const ICFGNode *> path;
    std::set<const ICFGNode *> visited;
    std::stack<const SVFInstruction *>callstack;
    ICFGTraversal *gt = new ICFGTraversal(pag);
    for (const CallICFGNode *src : gt->identifySources())
    {
        for (const CallICFGNode *snk : gt->identifySinks())
        {
            gt->DFS(visited, path, callstack, src, snk);
        }
    }
    
    std::set<std::string> expected = {"START: 5->6->7->8->11->1->2->3->12->15->END", "START: 5->6->7->8->9->1->2->3->10->13->END"};
    assert(expected == gt->getPaths() && "test2 failed!");
    std::cout << "test2 passed!" << "\n";
    LLVMModuleSet::releaseLLVMModuleSet();
    SVFIR::releaseSVFIR();
    delete gt;
}
void Test()
{
    Test1();
    Test2();
}

int main()
{
    Test();
    return 0;
}
