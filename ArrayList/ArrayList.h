#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#define DEAFULTSIZE 1024

#include<iostream>
#include <assert.h>

using namespace std;

template <typename E>
class ArrayList
{
private:
    int maxSize;
    int listSize;
    int curr;
    E *list;

public:
    ArrayList(int size = DEAFULTSIZE)
    {
        maxSize = size;
        listSize = 0;
        curr = 0;
        list = new E[maxSize];
    }
    ~ArrayList() { clear(); }
    void clear();
    void insert(const E &e);
    void append(const E &e);
    void remove();
    void pop();
    E get();
    E at(int i);
    void moveToStart();
    void moveToEnd();
    void moveTo(int i);
    void pre();
    void next();
    int length();
    bool isEmpty();
    void print();
};

template <typename E>
void ArrayList<E>::clear()
{
    listSize = curr = 0;
    delete[] list;
    list = new E[maxSize];
}

template <typename E>
void ArrayList<E>::insert(const E &e)
{
    if (listSize < maxSize)
    {
        for (int i = listSize; i > curr; i--)
        {
            list[i] = list[i - 1];
        }
        list[curr] = e;
        listSize++;
    }
}

template <typename E>
void ArrayList<E>::append(const E &e)
{
    if (listSize < maxSize)
    {
        list[listSize] = e;
        listSize++;
    }
}

template <typename E>
void ArrayList<E>::remove()
{
    if (listSize != 0)
    {
        for (int i = curr; i < listSize - 1; i++)
        {
            list[i] = list[i + 1];
        }
        listSize--;
    }
}

template <typename E>
void ArrayList<E>::pop()
{
    if (listSize != 0)
    {
        listSize--;
        if (curr == listSize - 1)
            curr--;
    }
}

template <typename E>
E ArrayList<E>::get()
{
    return list[curr];
}

template <typename E>
E ArrayList<E>::at(int i)
{
    if (i < listSize && i >= 0)
        return list[i];
}

template <typename E>
void ArrayList<E>::moveToStart()
{
    curr = 0;
}

template <typename E>
void ArrayList<E>::moveToEnd()
{
    curr = listSize - 1;
}

template <typename E>
void ArrayList<E>::moveTo(int i)
{
    if (i < listSize && i >= 0)
    {
        curr = i;
    }
}

template <typename E>
void ArrayList<E>::pre()
{
    if (curr > 0)
        curr--;
}

template <typename E>
void ArrayList<E>::next()
{
    if (curr < listSize - 1)
        curr++;
}

template <typename E>
int ArrayList<E>::length()
{
    return listSize;
}

template <typename E>
bool ArrayList<E>::isEmpty()
{
    return listSize == 0;
}

template <typename E>
void ArrayList<E>::print()
{
    for (int i = 0; i < listSize; i++)
    {
        cout << list[i] << " ";
    }
}

#endif