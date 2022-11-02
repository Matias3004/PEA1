#pragma once

#include <vector>
#include <algorithm>

class BF2
{
    private:
        std::vector<std::vector<int>> cities;
        std::vector<int> shortestPath;
        std::vector<int> pathTemp;
        std::vector<bool> isUsedInPath;

        int vertexCount;
        int minCost = INT_MAX;
        int tempCost = 0;
        int beginPathIndex = 0, previousIndex;

    public:
        BF2();
        ~BF2();
        bool isNotInPath(int);
        void findShortestPath(int, int);
        void bruteForce();
};