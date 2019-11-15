#ifndef LINKSTACK_H
#define LINKSTACK_H

#include <iostream>
#include "Link.h"

using namespace std;

template <typename E>
class LinkStack
{
private:
    Link<E> *top;
    int size;
    /* data */
public:
    LinkStack()
    {
        top = new Link<E>();
        size = 0;
    }
    ~LinkStack() { clear(); }
    void clear();
    void push(const E &e);
    E pop();
    E topVaule();
    int length();
    bool isEmpty();
    void print();
};

template <typename E>
void LinkStack<E>::clear()
{
    while (top != nullptr)
    {
        Link<E> *temp = top;
        top = top->next;
        delete temp;
    }
    size = 0;
}

template <typename E>
void LinkStack<E>::push(const E &e)
{
    top = new Link<E>(e, top); //top永远位于栈顶
    size++;
}

template <typename E>
E LinkStack<E>::pop()
{
    E e;
    if (size != 0)
    {
        e = top->element;
        Link<E> *temp = top;
        top = top->next;
        delete temp;
        size--;
    }
    return e;
}

template <typename E>
E LinkStack<E>::topVaule()
{
    E e;
    if (size != 0)
    {
        return top->element;
    }
    return e;
}

template <typename E>
int LinkStack<E>::length()
{
    return size;
}

template <typename E>
bool LinkStack<E>::isEmpty()
{
    return size == 0;
}

template <typename E>
void LinkStack<E>::print()
{
    Link<E> *temp = top;
    while (temp->next != nullptr)
    {
        cout << temp->element << " ";
        temp = temp->next;
    }
}

#endif