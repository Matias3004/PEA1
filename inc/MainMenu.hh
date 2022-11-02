#pragma once
#include "TestsAutomation.hh"
#include "Graph.hh"
#include "StackImpl.hh"
#include "BruteForce.hh"
#include "BranchAndBound.hh"

class MainMenu
{
    private:
        Graph graph;
        std::string preview;
        std::string menu = "\n\t1. Wczytaj graf"
            "\n\t2. Wygeneruj losowy graf"
            "\n\t3. Algorytm przeglądu zupełnego (Brute Force)"
            "\n\t4. Algorytm podziału i ograniczeń (B&B)"
            "\n\t5. Testy automatyczne"
            "\n\t0. Zamknij program\n";

    public:
        MainMenu();
        ~MainMenu();
        void showMenu(); // Głowne menu programu
        void loadGraph(); // Wczytywanie grafu
        void testBruteForce(); // Test algorytmu przeglądu zupełnego
        void testBranchAndBound(); // Test alrgorytmu podziału i ograniczeń
        void autoTest(); // Obsługa testow
};
