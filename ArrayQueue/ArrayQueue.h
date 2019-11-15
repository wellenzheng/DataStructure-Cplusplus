#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H

#include<iostream>

#define DEAFULTSIZE 8

using namespace std;

template <typename E>
class ArrayQueue
{
private:
    int maxSize;
    int front;
    int rear;
    E *queue;

public:
    ArrayQueue(int size = DEAFULTSIZE)
    {
        maxSize = size + 1; //max size equals to n+1, but only store n elements
        front = 1;
        rear = 0;
        queue = new E[maxSize];
    }
    void clear();
    void enqueue(const E &e);
    void dequeue();
    E getFront();
    int length();
    bool isEmpty();
    void print();
};

template <typename E>
void ArrayQueue<E>::clear()
{
    front = 1;
    rear = 0;
    delete[] queue;
    queue = new E[maxSize];
}

template <typename E>
void ArrayQueue<E>::enqueue(const E &e)
{
    if (front != (rear + 2) % maxSize) //otherwise, the queue is full
    {
        rear = (rear + 1) % maxSize;
        queue[rear] = e;
    }
}

template <typename E>
void ArrayQueue<E>::dequeue()
{
    if (!isEmpty())
    {
        front = (front + 1) % maxSize;
    }
}

template <typename E>
E ArrayQueue<E>::getFront()
{
    return queue[front];
}

template <typename E>
int ArrayQueue<E>::length()
{
    return (rear + maxSize - front + 1) % maxSize;
}

template <typename E>
bool ArrayQueue<E>::isEmpty()
{
    return front == (rear + 1) % maxSize;
}

template <typename E>
void ArrayQueue<E>::print()
{
    if (rear < front - 1)
    {
        for (int i = front; i < maxSize; i++)
        {
            cout << queue[i] << " ";
        }
        for (int i = 0; i <= rear; i++)
        {
            cout << queue[i] << " ";
        }
    }
    else
    {
        for (int i = front; i <= rear; i++)
        {
            cout << queue[i] << " ";
        }
    }
}

#endif