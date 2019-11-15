#pragma once

#ifndef BSTNODE_H
#define BSTNODE_H
#include <iostream>
using namespace std;

template <typename Key, typename E>
class BSTNode
{
private:
	Key key;
	E element;
	BSTNode *lc;
	BSTNode *rc;

public:
	BSTNode()
	{
		lc = nullptr;
		rc = nullptr;
	}
	BSTNode(const Key &k, const E &e)
	{
		key = k;
		element = e;
		lc = nullptr;
		rc = nullptr;
	}
	~BSTNode() {}

	E getElement() { return element; }
	void setElement(const E &e) { element = e; }
	Key getKey() { return key; }
	void setKey(const Key &k) { key = k; }
	BSTNode<Key, E> *left() { return lc; }
	void setLeft(BSTNode<Key, E> *l) { lc = l; }
	BSTNode<Key, E> *right() { return rc; }
	void setRight(BSTNode<Key, E> *r) { rc = r; }
	bool isLeaf() { return lc == nullptr && rc == nullptr; }
};

#endif // !BSTNODE_H
