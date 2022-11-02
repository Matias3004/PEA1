#include <iostream>
#include <string>
#include "../inc/BF2.hh"

BF2::BF2() {}

BF2::~BF2() {}

bool BF2::isNotInPath(int index)
{
    for (int i = 0; i < pathTemp.size(); i++)
        if (pathTemp[i] == index) return false;

    return true;
}

void BF2::findShortestPath(int startIndex, int startCost)
{
    isUsedInPath[startIndex] = true;
    pathTemp.push_back(startIndex);

    if (pathTemp.size() == vertexCount)
    {
        pathTemp.push_back(beginPathIndex);
        tempCost = startCost + cities[startIndex][beginPathIndex];

        if (startCost + cities[startIndex][beginPathIndex] < minCost)
        {
            minCost = startCost + cities[startIndex][beginPathIndex];
            shortestPath = pathTemp;
        }

        pathTemp.pop_back();
    }
    else
    {
        for (int i = 0; i < vertexCount; i++)
        {
            if (cities[startIndex][i] != -1 && cities[startIndex][i] != 0)
            {
                if ((isUsedInPath[i])
                    || ((startCost + cities[startIndex][i]) > minCost))
                    continue;
                else
                    findShortestPath(i, startCost + cities[startIndex][i]);
            }
        }
    }
    
    pathTemp.pop_back();
    isUsedInPath[startIndex] = false;
}

void BF2::bruteForce()
{
    beginPathIndex = 0;
    while (beginPathIndex < vertexCount)
    {
        previousIndex = beginPathIndex;
        tempCost = 0;
        pathTemp.clear();
        findShortestPath(beginPathIndex, 0);
        beginPathIndex++;
    }
}