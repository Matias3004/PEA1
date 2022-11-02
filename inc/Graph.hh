#pragma once
#include <string>
#define INF 9999

class Graph
{
    private:
        int **matrix = nullptr;
        int vertexCount = 0;

    public:
        Graph();
        ~Graph();
        bool readGraph(std::string);
        bool infDiagram();
        int getCount();
        int **getMatrix();
        void generateRandomGraph(int);
        std::string toString();
};
