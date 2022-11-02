#include <iostream>
#include "../inc/BruteForce.hh"

BruteForce::BruteForce(Graph graph)
{
    count = graph.getCount();
    matrix = graph.getMatrix();
    visited = new bool[count];
    sumOfWeights = INF;
    sumOfWeightsHelper = 0;

    for (int i = 0; i < count; i++)
        visited[i] = false;
}

BruteForce::~BruteForce() {}

bool BruteForce::recursion(int node)
{
    pathHelper.push(node);

    if (pathHelper.getSize() != count)
    {
        visited[node] = true;

        for (int i = 0; i < count; i++)
        {
            if (visited[i])
                continue;

            sumOfWeightsHelper += matrix[node][i];
            recursion(i);
            sumOfWeightsHelper -= matrix[node][i];
        }

        visited[node] = false;
        pathHelper.pop();
    }
    else if (matrix[node][0] <= 0)
        pathHelper.pop();
    else
    {
        sumOfWeightsHelper += matrix[node][0];

        if (sumOfWeightsHelper >= sumOfWeights)
            sumOfWeightsHelper -= matrix[node][0];
        else
        {
            sumOfWeights = sumOfWeightsHelper;
            pathHelper.copy(&path);
            sumOfWeightsHelper -= matrix[node][0];
        }

        pathHelper.pop();
    }

    if (path.getSize())
        return true;
    else
        return false;
}

void BruteForce::apply()
{
    recursion(0);
}

std::string BruteForce::toString()
{
    std::string result = "";
    result = "Trasa: " + path.toString() + "0\n"
        + "Koszt: " + std::to_string(sumOfWeights);

    return result;
}
