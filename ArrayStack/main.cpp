#include<iostream>
#include"ArrayStack.h"


using namespace std;

int main()
{
    ArrayStack<int> stack = ArrayStack<int>();
    stack.push(1);
    stack.push(2);
    stack.print();
    cout<<stack.length()<<endl;
    cout<<stack.pop();
    // stack.pop();
    // stack.pop();
    // stack.print();
}