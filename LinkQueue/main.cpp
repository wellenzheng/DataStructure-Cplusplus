#include <iostream>
#include "Link.h"
#include "LinkQueue.h"

using namespace std;

int main()
{
    LinkQueue<int> *queue = new LinkQueue<int>();
    queue->enqueue(1);
    queue->enqueue(2);
    queue->enqueue(3);
    queue->dequeue();
    queue->enqueue(1);
    queue->print();
}