#ifndef LISTNODE_H
#define LISTNODE_H

template <typename E>
class ListNode
{
private:
    /* data */

public:
    E element;
    ListNode *next;

    ListNode(const E &e)
    {
        element = e;
        next = nullptr;
    }
    ListNode(ListNode<E> *n = nullptr)
    {
        next = n;
    }
    ListNode(const E &e, ListNode<E> *n = nullptr)
    {
        element = e;
        next = n;
    }
};

#endif