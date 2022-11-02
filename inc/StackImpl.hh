#pragma once
#include <string>

class StackImpl
{
    private:
        int *base = nullptr;
        int size = 0;

    public:
        StackImpl();
        ~StackImpl();

        void push(int value);
        int pop();
        int getSize();
        void copy(StackImpl *destination);
        void clear();

        std::string toString();
};
