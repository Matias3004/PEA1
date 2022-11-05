#include "../inc/Tests.hh"
#include <fstream>

void Tests::saveResults(std::string filename, int instanceSize, int runs)
{
    std::ofstream file(filename + ".csv");
    if (file.good() == true)
    {
        if (instanceSize <= 10)
            file << "Brute Force [µs], Branch And Bound [µs]" << std::endl;
        else 
            file << "Brute Force [ms], Branch And Bound [µs]" << std::endl;
        for (int i = 0; i < runs; i++)
        {
            file << bruteForceResults[i] << ","
                << branchAndBoundResults[i] << std::endl;
        }
        file << "AVG [BF], AVG [B&B]" << std::endl;
        file << calculateAverage(instanceSize, bruteForceResults) << ","
            << calculateAverage(instanceSize, branchAndBoundResults) << std::endl;

        file.close();
    }
    else
    {
        std::cout << "Błąd zapisu" << std::endl;
        getchar();
    }
}

void Tests::startTimer()
{
    startTime = std::chrono::high_resolution_clock::now();
}

void Tests::stopTimer()
{
    endTime = std::chrono::high_resolution_clock::now();
}

long Tests::measuredTimeMicroSec()
{
    return std::chrono::duration_cast<std::chrono::microseconds>
        (Tests::endTime - Tests::startTime).count();
}

// long Tests::measuredTimeMilliSec()
// {
//     return std::chrono::duration_cast<std::chrono::milliseconds>
//         (Tests::endTime - Tests::startTime).count();
// }

long Tests::measuredTimeMilliSec()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
        (Tests::endTime - Tests::startTime).count();
}

void Tests::addBruteForceResults(unsigned long duration, int index)
{
    bruteForceResults[index] = duration;
    index++;
}

void Tests::addBranchAndBoundResults(unsigned long duration, int index)
{
    branchAndBoundResults[index] = duration;
    index++;
}

double Tests::calculateAverage(int runs, unsigned long *results)
{
    unsigned long sum = 0;
    for (int i = 0; i < runs; ++i)
        sum += results[i];

    double avg = (sum / runs);

    return avg;
}