#include "../inc/DynamicProgramming.hh"

DynamicProgramming::DynamicProgramming(Graph graph)
{
    matrix = graph.getMatrix();
    count = graph.getCount();
    memory = new int*[1 << count];
    getMemory = new int*[1 << count];
    temp = 0;
    result = 0;
    lastVertex = 0;

    for (int i = 0; i < (1 << count); i++)
    {
        memory[i] = new int[count];
        getMemory[i] = new int[count];
    }

    for (int i = 0; i < (1 << count); i++)
    {
        for (int j = 0; j < count; j++)
        {
            memory[i][j] = INF;
            getMemory[i][j] = INF;
        }
    }
}

DynamicProgramming::~DynamicProgramming()
{
    for (int i = 0; i < (1 << count); i++)
    {
        delete[] memory[i];
        delete[] getMemory[i];
    }

    delete[] memory;
    delete[] getMemory;
}

void DynamicProgramming::apply()
{
    for (int i = 0; i <count; i++)
    {
        memory[(1 << i) | 1][i] = matrix[0][i];
        getMemory[(1 << i) | 1][i] =0;
    }

    for (int bitMask = 0; bitMask < 1 << count; bitMask++)
    {
        for (int v = 0; v < count; v++)
        {
            if (!(bitMask & (1 << v)))
                continue;

            for (int i = 0; i < count; i++)
            {
                if (!(bitMask & (1 << i)))
                {
                    if (memory[bitMask][v] + matrix[v][i]
                        < memory[bitMask | (1 << i)][i])
                    {
                        getMemory[bitMask | (1 << i)][i] = v;
                        memory[bitMask | (1 << i)][i] =
                            memory[bitMask][v] + matrix[v][i];
                    }
                }
            }
        }
    }

    result = INF;
    temp = 0;

    for (int i = 0; i < count; i++)
    {
        temp = memory[(1 << count) - 1][i] + matrix[i][0];
        if (temp < result)
        {
            result = temp;
            lastVertex = i;
        }
    }
}

int DynamicProgramming::getResult()
{
    return result;
}

std::string DynamicProgramming::toString()
{
    std::string msg = "";
    int bitMask = (1 << count) - 1;
    int prev;
    StackImpl path;
    path.push(lastVertex);

    for (int i = count - 2; i > 0; i--)
    {
        prev = getMemory[bitMask][lastVertex];
        path.push(prev);
        bitMask = bitMask ^ (1 << lastVertex);
        lastVertex = prev;
    }

    msg = "Droga: 0 " + path.toString() + "0\n"
        + "Koszt: " + std::to_string(result);

    return msg;
}