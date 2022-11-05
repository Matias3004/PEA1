#pragma once
#include "Graph.hh"
#include "StackImpl.hh"

#define INF 9999

class DynamicProgramming
{
    private:
        int **matrix;
        int count;
        int result;
        int temp;
        int **memory;
        int **getMemory;
        int lastVertex;

    public:
        DynamicProgramming(Graph);
        ~DynamicProgramming();
        void apply();
        int getResult();
        std::string toString();
};