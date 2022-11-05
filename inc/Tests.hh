#pragma once
#include <iostream>
#include <chrono>

class Tests
{
    protected:
        const static int number = 100;
        unsigned long bruteForceResults[number];
        unsigned long branchAndBoundResults[number];
        unsigned long dynamicProgrammingResults[number];

    public:
        std::chrono::high_resolution_clock::time_point startTime;
        std::chrono::high_resolution_clock::time_point endTime;

        void saveBFResults(std::string, int, int);
        void saveBBResults(std::string, int);
        void saveDPResults(std::string, int);
        void startTimer();
        void stopTimer();
        long measuredTimeMicroSec();
        long measuredTimeMilliSec();
        void addBruteForceResults(unsigned long, int);
        void addBranchAndBoundResults(unsigned long, int);
        void addDynamicProgrammingResults(unsigned long, int);
        double calculateAverage(int, unsigned long*);
};
