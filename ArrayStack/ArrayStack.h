#ifndef ARRAYSTACK_H
#define ARRAYSTACK_H

#define DEAULTSIZE 1024

#include <iostream>

using namespace std;

template <typename E>
class ArrayStack
{
private:
    /* data */
    int maxSize;
    int top;
    E *stack;

public:
    ArrayStack(int size = DEAULTSIZE)
    {
        maxSize = size;
        top = 0;
        stack = new E[maxSize];
    }
    ~ArrayStack()
    {
        maxSize = 0;
        top = 0;
        delete[] stack;
    }
    void clear();
    void push(const E &e);
    E pop();
    E topVaule();
    int length();
    bool isEmpty();
    void print();
};

template <typename E>
void ArrayStack<E>::clear()
{
    top = 0;
    delete[] stack;
    stack = new E[maxSize];
}

template <typename E>
void ArrayStack<E>::push(const E &e)
{
    if (top < maxSize)
        stack[top++] = e;
}

template <typename E>
E ArrayStack<E>::pop()
{
    if (top != 0)
        return stack[--top];
    return stack[0];
}

template <typename E>
E ArrayStack<E>::topVaule()
{
    return stack[top];
}

template <typename E>
int ArrayStack<E>::length()
{
    return top;
}

template <typename E>
bool ArrayStack<E>::isEmpty()
{
    return top == 0;
}

template<typename E>
void ArrayStack<E>::print()
{
    for (int i = 0; i < top; i++)
    {
        cout<<stack[i]<<" ";
    }
}

#endif