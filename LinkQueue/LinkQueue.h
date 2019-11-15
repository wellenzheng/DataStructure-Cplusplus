#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include <iostream>
#include "Link.h"

using namespace std;

template <typename E>
class LinkQueue
{
private:
    int size;
    Link<E> *front;
    Link<E> *rear;

public:
    LinkQueue()
    {
        front = rear = new Link<E>();
    }
    ~LinkQueue() { clear(); }
    void clear();
    void enqueue(const E &e);
    void dequeue();
    E getFront();
    int length();
    bool isEmpty();
    void print();
};

template <typename E>
void LinkQueue<E>::clear()
{
    while (front->next != nullptr)
    {
        Link<E> *temp = front;
        front = front->next;
        delete temp;
    }
}

template <typename E>
void LinkQueue<E>::enqueue(const E &e)
{
    rear = rear->next = new Link<E>(e);
    size++;
}

template <typename E>
void LinkQueue<E>::dequeue()
{
    if (front->next != nullptr)
    {
        Link<E> *temp = front;
        front = front->next;
        delete temp;
    }
}

template <typename E>
E LinkQueue<E>::getFront()
{
    return front->next->element;
}

template <typename E>
int LinkQueue<E>::length()
{
    return size;
}

template <typename E>
bool LinkQueue<E>::isEmpty()
{
    return size == 0;
}

template <typename E>
void LinkQueue<E>::print()
{
    Link<E> *temp = front->next;
    while (temp != nullptr)
    {
        cout << temp->element << " ";
        temp = temp->next;
    }
}

#endif