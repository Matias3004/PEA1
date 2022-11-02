#include <iostream>
#include "../inc/MainMenu.hh"
#include "../inc/Graph.hh"
#include "../inc/StackImpl.hh"
#include "../inc/TestsAutomation.hh"

MainMenu::MainMenu()
{
    preview = "";
}

MainMenu::~MainMenu() {}

void MainMenu::loadGraph()
{
    std::string filename = "";
    bool check = false;
    do
    {
        std::cout << "Podaj nazwę pliku: ";
        std::cin >> filename;
        check = graph.readGraph(filename);
        
        if (!check)
            std::cout << "Blad odczytu\n";

    } while (!check);

    preview = "Plik <" + filename + ">\n\n";
    preview.append(graph.toString());
    graph.infDiagram();
}

void MainMenu::testBruteForce()
{
    if (!graph.getCount())
    {
        std::cout << "Brak danych\n";
        std::cin.ignore();
        std::cin.get();
    }
    else
    {
        BruteForce bruteForce(graph);
        bruteForce.apply();
        std::cout << "===================BRUTE FORCE===================\n"
            + bruteForce.toString();				
    }
}

void MainMenu::testBranchAndBound()
{
    if (!graph.getCount())
    {
        std::cout << "Brak danych\n";
        std::cin.ignore();
        std::cin.get();
    }
    else
    {
        BranchAndBound branchAndBound(graph);
        branchAndBound.apply();
        std::cout << "=================BRANCH AND BOUND=================\n"
            + branchAndBound.toString();
    }
}

void MainMenu::testDynamicProgramming()
{
    if (!graph.getCount())
    {
        std::cout << "Brak danych\n";
        std::cin.ignore();
        std::cin.get();
    }
    else
    {
        DynamicProgramming dynamicProgramming(graph);
        dynamicProgramming.apply();
        std::cout << "=============PROGRAMOWANIE DYNAMICZNE=============\n"
            + dynamicProgramming.toString();
    }
}

void MainMenu::autoTest()
{
    TestsAutomation testsAutomation;
    testsAutomation.menuTests();
}

void MainMenu::showMenu()
{
    Tests testing;
    while (true)
    {
        std::cout << "===================================================" << std::endl;
        std::cout << "===================PEA PROJEKT 1===================" << std::endl;
        std::cout << "===================================================";
        std::cout << menu;
        char input;
        int instanceSize = 0;
        std::cout << "Twoj wybor: ";
        std::cin >> input;
    
        switch(input)
        {
            case '1':
            {
                loadGraph();
                break;
            }

            case '2':
            {
                std::cout << "Podaj rozmiar instancji [6 / 8 / 9 / 10 / 12 / 13 / 14]: ";
                std::cin >> instanceSize;

                switch (instanceSize)
                {
                case 6: case 8: case 9: case 10: case 12: case 13: case 14:
                {
                    graph.generateRandomGraph(instanceSize);
                    break;
                }
                default:
                    std::cout << std::endl << "Podaj 6, 8, 9, 10, 12, 13 albo 14!" << std::endl;
                    break;
                }
                preview.append(graph.toString());
                graph.infDiagram();
                break;
            }

            case '3':
            {
                testing.startTimer();
                testBruteForce();
                testing.stopTimer();

                if (instanceSize <= 10)
                    std::cout << "\nCzas wykonania algorytmu: " << testing.measuredTimeMicroSec() << "µs\n";
                else
                    std::cout << "\nCzas wykonania algorytmu: " << testing.measuredTimeSeconds() << "s\n";

                break;
            }

            case '4':
            {
                testing.startTimer();
                testBranchAndBound();
                testing.stopTimer();

                std::cout << "\nCzas wykonania algorytmu: " << testing.measuredTimeMicroSec() << "µs\n";

                break;
            }

            case '5':
            {
                testing.startTimer();
                testDynamicProgramming();
                testing.stopTimer();

                std::cout << "\nCzas wykonania algorytmu: " << testing.measuredTimeMicroSec() << "µs\n";

                break;
            }

            case '6':
            {
                autoTest();
                break;
            }

            case '0':
            {
                return;
            }
        }
    }
}