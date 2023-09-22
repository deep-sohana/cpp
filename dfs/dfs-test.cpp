
#include "dfs.h"
#include <assert.h>

void Test1()
{
  /*


      1
     /  \ 
    2   3
     \ / 
      4
      |
      5

*/
  // init nodes
    Node *node1 = new Node(1);
    Node *node2 = new Node(2);
    Node *node3 = new Node(3);
    Node *node4 = new Node(4);
    Node *node5 = new Node(5);

    // init edges
    Edge *edge1 = new Edge(node1, node2);
    Edge *edge2 = new Edge(node1, node3);
    node1->addOutEdge(edge1);
    node1->addOutEdge(edge2);
    Edge *edge3 = new Edge(node2, node4);
    Edge *edge4 = new Edge(node3, node4);
    node2->addOutEdge(edge3);
    node3->addOutEdge(edge4);
    Edge *edge5 = new Edge(node4, node5);
    node4->addOutEdge(edge5);

    // init Graph
    Graph *g = new Graph();
    g->addNode(node1);
    g->addNode(node2);
    g->addNode(node3);
    g->addNode(node4);
    g->addNode(node5);
    // test
    std::set<std::string> expected_answer{"START: 1->2->4->5->END", "START: 1->3->4->5->END"};
    std::set<const Node *> visited;
    std::vector<const Node *> path;
    GraphTraversal *dfs = new GraphTraversal();
    dfs->DFS(visited, path, node1, node5);
    assert(dfs->getPaths() == expected_answer && "Test case 1 failed!");
    std::cout << "Test case 1 passed!\n";
}

void Test2()
{
  /*

        10
      /  \ 
      20   30
      \ / 
        40
        |
        50

  */
  // init nodes
  Node *node10 = new Node(10);
  Node *node20 = new Node(20);
  Node *node30 = new Node(30);
  Node *node40 = new Node(40);
  Node *node50 = new Node(50);

  // init edges
  Edge *edge10 = new Edge(node10, node20);
  Edge *edge20 = new Edge(node10, node30);
  node10->addOutEdge(edge10);
  node10->addOutEdge(edge20);
  Edge *edge30 = new Edge(node20, node40);
  Edge *edge40 = new Edge(node30, node40);
  node20->addOutEdge(edge30);
  node30->addOutEdge(edge40);
  Edge *edge50 = new Edge(node40, node50);
  node40->addOutEdge(edge50);

  // init Graph
  Graph *g2 = new Graph();
  g2->addNode(node10);
  g2->addNode(node20);
  g2->addNode(node30);
  g2->addNode(node40);
  g2->addNode(node50);
  // test
  std::set<std::string> expected_answer2{"START: 10->20->40->50->END", "START: 10->30->40->50->END"};
  std::set<const Node *> visited2;
  std::vector<const Node *> path2;
  GraphTraversal *dfs2 = new GraphTraversal();
  dfs2->DFS(visited2, path2, node10, node50);
  assert(dfs2->getPaths() == expected_answer2 && "Test case 2 failed!");
  std::cout << "Test case 2 passed!\n";
}

void Test3()
{
  /*

        10
        |
        30
        |
        40
        |
        50

  */
  // init nodes
  Node *node10 = new Node(10);
  Node *node30 = new Node(30);
  Node *node40 = new Node(40);
  Node *node50 = new Node(50);

  // init edges
  Edge *edge10 = new Edge(node10, node30);
  node10->addOutEdge(edge10);
  Edge *edge40 = new Edge(node30, node40);
  node30->addOutEdge(edge40);
  Edge *edge50 = new Edge(node40, node50);
  node40->addOutEdge(edge50);

  // init Graph
  Graph *g3 = new Graph();
  g3->addNode(node10);
  g3->addNode(node30);
  g3->addNode(node40);
  g3->addNode(node50);
  // test
  std::set<std::string> expected_answer3{"START: 10->30->40->50->END"};
  std::set<const Node *> visited3;
  std::vector<const Node *> path3;
  GraphTraversal *dfs3 = new GraphTraversal();
  dfs3->DFS(visited3, path3, node10, node50);
  assert(dfs3->getPaths() == expected_answer3 && "Test case 3 failed!");
  std::cout << "Test case 3 passed!\n";
}


void Test4()
{
  /*

        10
        |
        20
        |
        30
        |
        40
        |
        50

  */
  // init nodes
  Node *node10 = new Node(10);
  Node *node20 = new Node(20);
  Node *node30 = new Node(30);
  Node *node40 = new Node(40);
  Node *node50 = new Node(50);

  // init edges
  Edge *edge10 = new Edge(node10, node20);
  node10->addOutEdge(edge10);
  Edge *edge20 = new Edge(node20, node30);
  node20->addOutEdge(edge20);
  Edge *edge40 = new Edge(node30, node40);
  node30->addOutEdge(edge40);
  Edge *edge50 = new Edge(node40, node50);
  node40->addOutEdge(edge50);

  // init Graph
  Graph *g4 = new Graph();
  g4->addNode(node10);
  g4->addNode(node30);
  g4->addNode(node40);
  g4->addNode(node50);
  // test
  std::set<std::string> expected_answer4{"START: 10->20->30->40->50->END"};
  std::set<const Node *> visited4;
  std::vector<const Node *> path4;
  GraphTraversal *dfs4 = new GraphTraversal();
  dfs4->DFS(visited4, path4, node10, node50);
  assert(dfs4->getPaths() == expected_answer4 && "Test case 4 failed!");
  std::cout << "Test case 4 passed!\n";
}

void Test5(){
   /*

        10
        |
  */
  // init nodes
  Node *node10 = new Node(10); 

  Graph *g5 = new Graph();
  g5->addNode(node10);
  //test
  std::set<std::string> expected_answer5{"START: 10->END"};
  std::set<const Node *> visited5;
  std::vector<const Node *> path5;
  GraphTraversal *dfs5 = new GraphTraversal();
  dfs5->DFS(visited5, path5, node10, node10);
  assert(dfs5->getPaths() == expected_answer5 && "Test case 5 failed!");
  std::cout << "Test case 5 passed!\n\n\n";
}


/// Entry of the program
int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    return 0;
}