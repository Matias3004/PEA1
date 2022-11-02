#include <iostream>
#include <vector>
#include <queue>
#include "../inc/BranchAndBound.hh"

BranchAndBound::BranchAndBound(Graph graph)
{
    count = graph.getCount();
    matrix = graph.getMatrix();
    uBound = INF;
    tempCost = 0;
    outgoingEdges = new int[count];
    visited = new bool[count];
    n0_lb = 0;
    int min = INF;

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (matrix[i][j] < min)
                min = matrix[i][j];
        }
        outgoingEdges[i] = min;
        n0_lb += min;
        min = INF;
    }

    for (int i = 0; i < count; i++)
        visited[i] = false;
}

BranchAndBound::~BranchAndBound() {}

bool operator>(const Node &arg1, const Node &arg2)
{
    if (arg1.lBound > arg2.lBound)
        return true;
    else
        return false;
}

bool operator<(const Node &arg1, const Node &arg2)
{
    if (arg1.lBound < arg2.lBound)
        return true;
    else
        return false;
}

bool operator==(const Node &arg1, const Node &arg2)
{
    if (arg1.lBound == arg2.lBound)
        return true;
    else
        return false;
}

void BranchAndBound::recursion(Node node)
{
    pathHelper.push(node.vertex);
    visited[node.vertex] = true;
    Node temp;
    std::priority_queue <Node, std::vector<Node>, std::greater<Node>> bounds;

    for (int i = 0; i < count; ++i)
    {
        if (!visited[i])
        {
            temp.vertex = i;
            temp.lBound = lowerBound(node, i);
            bounds.push(temp);
        }
    }

    if (bounds.empty())
    {
        if (lowerBound(node, 0) < uBound)
        {
            uBound = lowerBound(node, 0);
            pathHelper.copy(&path);
        }
    }
    else
    {
        while (!bounds.empty())
        {
            temp = bounds.top();
            bounds.pop();
            if (temp.lBound < uBound)
                recursion(temp);
            else
                break;
        }
    }

    pathHelper.pop();
    visited[node.vertex] = false;
}

void BranchAndBound::apply()
{
    Node start;
    start.vertex = 0;
    start.lBound = n0_lb;

    recursion(start);
}

int BranchAndBound::lowerBound(Node arg, int next)
{
    int result = arg.lBound;
    result -= outgoingEdges[arg.vertex];
    result += matrix[arg.vertex][next];

    return result;
}

std::string BranchAndBound::toString()
{
    std::string result = "";
    result = "Droga: " + path.toString() + "0\n"
        + "Koszt: " + std::to_string(uBound);

    return result;
}
