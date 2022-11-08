#include "../inc/Graph.hh"
#include <fstream>
#include <iostream>
#include <time.h>

Graph::Graph() {}

Graph::~Graph() {}

// Metoda wczytująca graf z podanego pliku *.txt
bool Graph::readGraph(std::string filename)
{
    int **temp;

    std::ifstream file;
    file.open(filename);

    if (file.fail() || file.eof())
        return false;

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; ++i)
            delete[] matrix[i];

        delete[] matrix;
    }

    file >> vertexCount;
    temp = new int*[vertexCount];

    for (int i = 0; i < vertexCount; ++i)
        temp[i] = new int[vertexCount];

    for (int i = 0; i < vertexCount; ++i)
    {
        for (int j = 0; j < vertexCount; ++j)
            file >> temp[i][j];
    }

    file.close();

    matrix = temp;

    return true;
}

// Metoda ustawiająca wartości na przekątnej grafu na -1
bool Graph::infDiagram()
{
    if (!vertexCount)
        return false;
    else
    {
        for (int i = 0; i < vertexCount; ++i)
            matrix[i][i] = -1;

        return true;
    }
}

int Graph::getCount()
{
    return vertexCount;
}

int** Graph::getMatrix()
{
    return matrix;
}

// Metoda generująca losowy graf o podanej wielkości
void Graph::generateRandomGraph(int size)
{
    vertexCount = size;
    int **buff = nullptr;
    buff = new int*[vertexCount];

    srand(time(nullptr));

    for (int i = 0; i < vertexCount; ++i)
    {
        buff[i] = new int[vertexCount];
        for (int j = 0; j < vertexCount; ++j)
            buff[i][j] = rand() % 100 + 1;
    }

    matrix = buff;
    infDiagram();
}

// Metoda wyświetlająca graf
std::string Graph::toString()
{
    std::string graph = "";

    if (vertexCount)
    {
        for (int i = 0; i < vertexCount; ++i)
        {
            for (int j = 0; j < vertexCount; ++j)
            {
                if ((matrix[i][j] < 10) && (matrix[i][j] >= 0))
                    graph += std::to_string(matrix[i][j]) + "   ";
                else if (((matrix[i][j] < 100) && (matrix[i][j] > 9)) ||
                    (matrix[i][j] < 0))
                    graph += std::to_string(matrix[i][j]) + "   ";
                else
                    graph += std::to_string(matrix[i][j]) + "   ";
            }

            graph += "\n";
        }
    }
    else
        graph = "Graf jest pusty\n";

    return graph;
}
