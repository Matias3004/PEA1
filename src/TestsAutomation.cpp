#include <string>
#include "../inc/TestsAutomation.hh"

void TestsAutomation::menuTests()
{
    int instanceSize;
    int algorithm;
    std::cout << "================================TESTY AUTOMATYCZNE================================\n";
    do
    {
        std::cout << "Wybierz algorytm [1 - Brute Force, 2 - Branch & Bound, 3 - Dynamic Programming]: ";
        std::cin >> algorithm;
    } while (algorithm < 1 || algorithm > 3);

    std::cout << "Podaj rozmiar instancji [6 / 8 / 9 / 10 / 12 / 13 / 14]: ";
    std::cin >> instanceSize;

    switch (instanceSize)
    {
    case 6: case 8: case 9: case 10: case 12: case 13: case 14:
    {
        loopTests(instanceSize, algorithm);
        break;
    }
    default:
        std::cout << std::endl << "Podaj 6, 8, 9, 10, 12, 13 albo 14!" << std::endl;
         // menuTests();
        break;
    }
}

void TestsAutomation::loopTests(int instanceSize, int algorithm)
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
            if (algorithm == 1)
                numOfRuns = 50;
            else
                numOfRuns = 100;
            break;
        case 13:
            if (algorithm == 1)
                numOfRuns = 25;
            else
                numOfRuns = 100;
            break;
        case 14:
            if (algorithm == 1)
                numOfRuns = 5;
            else
                numOfRuns = 100;
            break;
        default:
            break;
    }

    switch (algorithm)
    {
        case 1:
        {
            for (int i = 0; i < numOfRuns; i++)
            {
                graph.generateRandomGraph(instanceSize);
                BruteForce bruteForce(graph);

                std::cout << i + 1 << " pomiar Brute Force..." << std::endl;
                testing.startTimer();
                bruteForce.apply();
                testing.stopTimer();

                if (instanceSize <= 10)
                    testing.addBruteForceResults(testing.measuredTimeMicroSec(), i);
                else
                    testing.addBruteForceResults(testing.measuredTimeMilliSec(), i);

            }
            auto filename = "BF-" + std::to_string(instanceSize);
            testing.saveBFResults(filename, instanceSize, numOfRuns);

            break;
        }
        case 2:
        {
            for (int i = 0; i < numOfRuns; i++)
            {
                graph.generateRandomGraph(instanceSize);
                BranchAndBound branchAndBound(graph);

                std::cout << i + 1 << " pomiar Branch and Bound..." << std::endl;
                testing.startTimer();
                branchAndBound.apply();
                testing.stopTimer();

                testing.addBranchAndBoundResults(testing.measuredTimeMicroSec(), i);
            }
            auto filename = "BB-" + std::to_string(instanceSize);
            testing.saveBBResults(filename, numOfRuns);

            break;
        }
        case 3:
        {
            for (int i = 0; i < numOfRuns; i++)
            {
                graph.generateRandomGraph(instanceSize);
                DynamicProgramming dynamicProgramming(graph);

                std::cout << i + 1 << " pomiar Dynamic Programming..." << std::endl;
                testing.startTimer();
                dynamicProgramming.apply();
                testing.stopTimer();

                testing.addDynamicProgrammingResults(testing.measuredTimeMicroSec(), i);
            }
            auto filename = "DP-" + std::to_string(instanceSize);
            testing.saveDPResults(filename, numOfRuns);

            break;
        }
        default:
            break;
    }
    std::cout << "\nTesty zakończone\n" << std::endl;
    getchar();
}