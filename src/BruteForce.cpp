#include <iostream>
#include "../inc/BruteForce.hh"

// Konstruktor klasy Brute Force
BruteForce::BruteForce(Graph graph)
{
    count = graph.getCount(); // Pobranie wielkości grafu
    matrix = graph.getMatrix(); // Pobranie reprezntacji macierzowej grafu
    visited = new bool[count]; // Utworzenie tablicy na odwiedzone wierzchołki
    sumOfWeights = INF; // Ustawienie wartości rozwiązania na "nieskończoność"
    sumOfWeightsHelper = 0; // Inicjalizacja zmiennej pomocniczej zawierającej obecną wartość rozwiązania 

    // Oznaczenie wszystkie wierzchołków jako nieodwiedzonych
    for (int i = 0; i < count; i++)
        visited[i] = false;
}

// Destuktor klasy Brute Force
BruteForce::~BruteForce() {}

// Metoda odpowiedzialna za przegląd kolejnych przypadków
bool BruteForce::recursion(int node)
{
    pathHelper.push(node); // Dodanie aktualnego węzła do tymczasowej ścieżki

    // Sprawdza czy są jeszcze węzły do sprawdzenia
    if (pathHelper.getSize() != count)
    {
        visited[node] = true; // Oznacza wierzchołek jako odwiedzony

        for (int i = 0; i < count; i++)
        {
            if (visited[i]) // Jeśli wierzchołek był już odwiedzony kontynuuje dalej
                continue;

            sumOfWeightsHelper += matrix[node][i]; // Dodaje koszt krawędzi do tymczasowej zmiennej zawierającej sumę kosztów
            recursion(i); // Powtarza wykonanie od aktualnego wierzchołka
            sumOfWeightsHelper -= matrix[node][i];
        }

        visited[node] = false;
        pathHelper.pop();
    }
    else if (matrix[node][0] <= 0) // Sprawdza czy aktualnie rozpatrywany przypadek nie jest ścieżką z jednego do tego samego miasta
        pathHelper.pop();
    else
    {
        sumOfWeightsHelper += matrix[node][0];

        if (sumOfWeightsHelper >= sumOfWeights)
            sumOfWeightsHelper -= matrix[node][0];
        else
        {
            sumOfWeights = sumOfWeightsHelper; // Zapisanie tymczasowego kosztu jako ostateczny
            pathHelper.copy(&path); // Zapisanie utworzonej ścieżki jako najlepsze znalezione rozwiązanie
            sumOfWeightsHelper -= matrix[node][0];
        }

        pathHelper.pop();
    }

    if (path.getSize())
        return true;
    else
        return false;
}

// Rozpoczyna algorytm przeglądu zupełnego
void BruteForce::apply()
{
    recursion(0);
}

// Wyświetla wynik działania algorytmu
std::string BruteForce::toString()
{
    std::string result = "";
    result = "Trasa: " + path.toString() + "0\n"
        + "Koszt: " + std::to_string(sumOfWeights);

    return result;
}
