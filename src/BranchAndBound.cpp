#include <iostream>
#include <vector>
#include <queue>
#include "../inc/BranchAndBound.hh"

// Konstruktor klasy Branch And Bound
BranchAndBound::BranchAndBound(Graph graph)
{
    count = graph.getCount(); // Pobranie ilości wierzchołkow w grafie
    matrix = graph.getMatrix(); // Pobranie macierzy z kosztami krawędzi
    uBound = INF; // Ustawienie ograniczenia gornego na "nieskończoność"
    tempCost = 0;
    outgoingEdges = new int[count]; // Utworzenie tablicy pomocniczej
    visited = new bool[count]; // Utworzenie tablicy zawierającej listę odwiedzonych wierzchołkow
    n0_lb = 0;
    int min = INF;

    // Wypełnienie tablicy pomocniczej wartościami najnizszych wag krawędzi wychodzących z wierzchołkow
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

    // Oznaczenie wszystkich wierzchołkow jako nieodwiedzonych
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
    // Dodanie aktualnego wierzchołka do stosu przechowującego ściezkę tymczasową dla danego etapu algorytmu
    pathHelper.push(node.vertex); 
    visited[node.vertex] = true; // Oznaczenie aktualnego wierzchołka jako odwiedzonego
    Node temp;
    // Utworzenie kolejki priorytetowej zawierającej węzły i ich ograniczenia dolne
    // Najwyzszy priorytet ma wierzchołek o najnizszej wartości ograniczenia dolnego
    std::priority_queue <Node, std::vector<Node>, std::greater<Node>> bounds; 

    // Sprawdza czy dany węzeł był juz odwiedzony
    for (int i = 0; i < count; ++i)
    {
        if (!visited[i]) // Jeśli nie, to obliczane jest jego ograniczenie dolne
        {
            temp.vertex = i; // Ustawienie aktualnego wierzchołka jako tymczasowy
            temp.lBound = lowerBound(node, i); // Obliczanie ograniczenia dolnego danego węzła
            bounds.push(temp); // Dodanie aktualnego węzła wraz z jego ograniczeniem dolnym do kolejki priorytetowej
        }
    }

    // Sprawdzenie czy nie ma więcej wierzchołkow do sprawdzenia
    if (bounds.empty())
    {
        // Sprawdzenie czy gorne ograniczenie jest większe od dolnego ograniczenia danego wierzchołka
        if (lowerBound(node, 0) < uBound)
        {
            uBound = lowerBound(node, 0); // Obliczenie dolnego ograniczenia danego wierzchołka i ustawienie go jako ograniczenie gorne
            pathHelper.copy(&path); // Zapisanie sciezki tymczasowej jako najlepsze znalezione rozwiązanie
        }
    }
    else // Jeśli są wierzchołki do sprawdzenia
    {
        // Powtarzanie algorytmu az nie zostaną sprawdzone wszystkie wierzchołki
        while (!bounds.empty())
        {
            // Ustawienie wierzchołka o najwyzszym priorytecie (najnizszej wartosci ograniczenia dolnego) jako aktualnie sprawdzany
            temp = bounds.top();
            bounds.pop(); // Usuniecie danego wierzchołka ze stosu
            // Jeśli jego ograniczenie dolne jest mniejsze od gornego ograniczenia powtarza algorytm rozpoczynając od danego wierzchołka
            if (temp.lBound < uBound)
                recursion(temp); 
            else
                break;
        }
    }

    // Usunięcie wierzchołka ze stosu
    pathHelper.pop();
    visited[node.vertex] = false;
}

// Metoda rozpoczynająca działane algorytmu
void BranchAndBound::apply()
{
    Node start;
    start.vertex = 0; // Ustwaienie korzenia jako pierwszy wierzchołek
    start.lBound = n0_lb; // Ustawienie ograniczenia dolnego na 0

    recursion(start); // Rozpoczęcie algorytmu w korzeniu grafu
}

// Metoda obliczająca dolne ograniczenie dla danego wierzchołka
int BranchAndBound::lowerBound(Node arg, int next)
{
    int result = arg.lBound; // Przekazanie wartości dolnego ograniczenia poprzednika
    result -= outgoingEdges[arg.vertex]; // Odjęcie wartości najnizszej wagi krawędzi wychodzącej z danego wierzchołka
    result += matrix[arg.vertex][next]; // Dodanie wartości wagi krawędzi przebytej do następnika

    return result;
}

// Metoda wyświetlająca w konsoli wynik działania algorytmu
std::string BranchAndBound::toString()
{
    std::string result = "";
    result = "Droga: " + path.toString() + "0\n"
        + "Koszt: " + std::to_string(uBound);

    return result;
}
