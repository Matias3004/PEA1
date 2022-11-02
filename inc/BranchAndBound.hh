#pragma once
#include "Graph.hh"
#include "StackImpl.hh"

struct Node
{
    int lBound;
    int vertex;
};

class BranchAndBound
{
    private:
        int **matrix;
        int count;
        int uBound;
        int tempCost;
        bool *visited;
        int *outgoingEdges;
        int n0_lb;
        StackImpl path;
        StackImpl pathHelper;

    public:
        BranchAndBound(Graph);
        ~BranchAndBound();
        void recursion(Node);
        void apply();
        int lowerBound(Node, int);
        std::string toString();
};
