#pragma once
#include "Graph.hh"
#include "StackImpl.hh"

class BruteForce
{
    private:
        int **matrix;
        int count;
        int sumOfWeights;
        int sumOfWeightsHelper;
        StackImpl path;
        StackImpl pathHelper;
        bool *visited;

    public:
        BruteForce(Graph);
        ~BruteForce();
        bool recursion(int);
        void apply();
        std::string toString();
};
