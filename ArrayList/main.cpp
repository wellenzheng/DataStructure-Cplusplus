#include<iostream>
#include"ArrayList.h"

using namespace std;

int main()
{
    ArrayList<int> list = ArrayList<int>();
    list.insert(1);
    list.append(2);
    list.insert(3);
    list.remove();
    list.print();
}