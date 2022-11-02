#include <string>
#include "../inc/TestsAutomation.hh"

void TestsAutomation::menuTests()
{
    int instanceSize;
    std::cout << "=======================TESTY AUTOMATYCZNE=======================\n";
    std::cout << "Podaj rozmiar instancji [6 / 8 / 9 / 10 / 12 / 13 / 14]: ";
    std::cin >> instanceSize;

    switch (instanceSize)
    {
    case 6: case 8: case 9: case 10: case 12: case 13: case 14:
    {
        loopTests(instanceSize);
        break;
    }
    default:
        std::cout << std::endl << "Podaj 6, 8, 9, 10, 12, 13 albo 14!" << std::endl;
         // menuTests();
        break;
    }
}

void TestsAutomation::loopTests(int instanceSize)
{
    Tests testing;
    Graph graph;
    int numOfRuns = 100;

    switch (instanceSize)
    {
        case 6: case 8: case 9: case 10:
            numOfRuns = 100;
            break;
        case 12:
            numOfRuns = 50;
            break;
        case 13:
            numOfRuns = 25;
            break;
        case 14:
            numOfRuns = 5;
            break;
        default:
            break;
    }

    for (int i = 0; i < numOfRuns; i++)
    {
        graph.generateRandomGraph(instanceSize);
        if (!graph.getCount())
        {
            std::cout << "Brak danych\n";
            std::cin.ignore();
            std::cin.get();
        }
        else
        {
            BruteForce bruteForce(graph);
            BranchAndBound branchAndBound(graph);

            std::cout << i + 1 << " pomiar Brute Force..." << std::endl;
            testing.startTimer();
            bruteForce.apply();
            testing.stopTimer();

            if (instanceSize <= 10)
                testing.addBruteForceResults(testing.measuredTimeMicroSec(), i);
            else
                testing.addBruteForceResults(testing.measuredTimeSeconds(), i);

            std::cout << i + 1 << " pomiar Branch and Bound..." << std::endl;
            testing.startTimer();
            branchAndBound.apply();
            testing.stopTimer();

            testing.addBranchAndBoundResults(testing.measuredTimeMicroSec(), i);
        }
    }
    std::cout << "\nTesty zakończone\n" << std::endl;
    getchar();
    
    auto filename = std::to_string(instanceSize);
    testing.saveResults(filename, instanceSize, numOfRuns);
}