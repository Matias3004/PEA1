#include "../inc/StackImpl.hh"

StackImpl::StackImpl() {}

StackImpl::~StackImpl()
{
    if (base != nullptr)
        delete[] base;

}

void StackImpl::push(int value)
{
    if (!size)
    {
        size++;
        base = new int[1];
        *base = value;
    }
    else
    {
        size++;
        int *temp = new int[size];
        int *base_buffer = base;
        int *temp_buffer = temp;

        for (int i = 0; i < size - 1; i++)
        {
            *temp_buffer = *base_buffer;
            temp_buffer++;
            base_buffer++;
        }

        *temp_buffer = value;

        delete[] base;

        base = temp;
    }
}

int StackImpl::pop()
{
    int peak;

    if (size > 1)
    {
        size--;
        peak = *(base + size);

        int *temp = new int[size];
        int *base_buffer = base;
        int *temp_buffer = temp;

        for (int i = 0; i < size; i++)
        {
            *temp_buffer = *base_buffer;
            base_buffer++;
            temp_buffer++;
        }

        delete[] base;
        base = temp;

        return peak;
    }
    else if (size == 1)
    {
        peak = *base;
        size = 0;

        delete[] base;
        base = nullptr;

        return peak;
    }
    else
        return -1;

}

int StackImpl::getSize()
{
    return size;
}

void StackImpl::copy(StackImpl *destination)
{
    int *base_buffer = base;

    destination->clear();

    if (size)
    {
        for (int i = 0; i < size; i++)
        {
            destination->push(*base_buffer);
            base_buffer++;
        }
    }
}

void StackImpl::clear()
{
    delete[] base;
    base = nullptr;
    size = 0;
}

std::string StackImpl::toString()
{
    std::string message = "";
    int *base_buffer = base;

    if (!size)
        message = "Stos jest pusty";
    else
    {
        for (int i = 0; i < size; ++i)
        {
            message = message + std::to_string(*base_buffer) + " ";
            base_buffer++;
        }
    }

    return message;
}
