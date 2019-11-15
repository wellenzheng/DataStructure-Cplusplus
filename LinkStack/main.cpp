#include"Link.h"
#include"LinkStack.h"

int main()
{
    LinkStack<int>* stack = new LinkStack<int>();
    stack->push(1);
    stack->push(2);
    stack->pop();
    stack->pop();
    stack->print();
    cout<<stack->length();
}