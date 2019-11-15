#include<iostream>
#include"ArrayQueue.h"

using namespace std;

int main()
{
    ArrayQueue<int> queue = ArrayQueue<int>();
    for (int i = 0; i < 8; i++)
    {
        queue.enqueue(i);
    }
    queue.dequeue();
    queue.enqueue(0);
    queue.print();
}