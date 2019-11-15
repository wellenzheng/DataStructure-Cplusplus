#ifndef LINK_H
#define LINK_H

template <typename E>
class Link
{
public:
    E element;
    Link *next;

    Link(Link<E> *n = nullptr)
    {
        next = n;
    }
    Link(const E &e, Link<E> *n = nullptr)
    {
        element = e;
        next = n;
    }
};

#endif
