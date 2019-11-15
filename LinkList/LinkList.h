#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>
#include "ListNode.h"

using namespace std;

template <typename E>
class LinkList
{
private:
    /* data */
    ListNode<E> *head;
    ListNode<E> *tail;
    ListNode<E> *curr;
    int size;

public:
    LinkList()
    {
        initiate();
    }
    ~LinkList() { clear(); }
    void initiate();
    void clear();
    void insert(const E &e);
    void append(const E &e);
    void remove();
    void pop();
    void moveToStart();
    void moveToEnd();
    void moveToPos(int i);
    void pre();
    void next();
    int currPos();
    int length();
    bool isEmpty();
    E get();
    void print();
};

template <typename E>
void LinkList<E>::initiate()
{
    head = tail = curr = new ListNode<E>();
    size = 0;
}

template <typename E>
void LinkList<E>::clear()
{
    curr = head;
    while (curr != nullptr)
    {
        curr = head;
        head = head->next;
        delete curr;
    }
    initiate();
}

template <typename E>
void LinkList<E>::insert(const E &e)
{
    curr->next = new ListNode<E>(e, curr->next);
    if (curr == tail)
        tail = curr->next;
    size++;
}

template <typename E>
void LinkList<E>::append(const E &e)
{
    tail = tail->next = new ListNode<E>(e, nullptr);
    size++;
}

template <typename E>
void LinkList<E>::remove()
{
    ListNode<E> *temp = curr->next;
    if (curr->next == tail)
        tail = curr;
    curr->next = temp->next;
    delete temp;
    size--;
}

template <typename E>
void LinkList<E>::pop()
{
    ListNode<E> *temp = curr;
    while (temp->next != tail)
    {
        temp = temp->next;
    }
    tail = temp;
    temp = temp->next;
    delete temp;
}

template <typename E>
void LinkList<E>::moveToStart()
{
    curr = head;
}

template <typename E>
void LinkList<E>::moveToEnd()
{
    curr = tail;
}

template <typename E>
void LinkList<E>::moveToPos(int pos)
{
    curr = head;
    for (int i = 0; i < pos; i++)
    {
        curr = curr->next;
    }
}

template <typename E>
int LinkList<E>::currPos()
{
    int pos = 0;
    ListNode<E> *temp = head;
    while (temp != curr)
    {
        temp = temp->next;
        pos++;
    }
    return pos;
}

template <typename E>
int LinkList<E>::length()
{
    return size;
}

template <typename E>
bool LinkList<E>::isEmpty()
{
    return size == 0;
}

template <typename E>
E LinkList<E>::get()
{
    if (curr != nullptr)
        return curr->element;
}

template <typename E>
void LinkList<E>::print()
{
    ListNode<E> *temp = head;
    while (temp != tail)
    {
        temp = temp->next;
        cout << temp->element << " ";
    }
}

#endif