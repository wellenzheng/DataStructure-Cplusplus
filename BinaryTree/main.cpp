#include <iostream>
#include "BSTree.h"

using namespace std;

int main()
{
	BSTree<int, int> *tree = new BSTree<int, int>();
	tree->insert(1, 1);
	tree->insert(2, 4);
	tree->insert(4, 5);
	tree->remove(2);
	tree->preorder();
}