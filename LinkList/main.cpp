#include<iostream>
#include"LinkList.h"
#include"ListNode.h"

using namespace std;

int main()
{
    LinkList<int>* list = new LinkList<int>();
    list->insert(1);
    list->insert(2);
    list->remove();
    list->append(4);
    list->append(6);
    list->moveToPos(1);
    list->remove();
    list->print();
}