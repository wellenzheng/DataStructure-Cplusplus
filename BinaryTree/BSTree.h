#pragma once

#ifndef BSTREE_H
#define BSTREE_H

#include<cstdio>
#include "BSTNode.h"

using namespace std;

template <typename Key, typename E>
class BSTree
{

private:
	BSTNode<Key, E> *root;
	int count;

	void clearHelp(BSTNode<Key, E> *root);
	BSTNode<Key, E> *insertHelp(BSTNode<Key, E> *root, const Key &k, const E &e);
	E findHelp(BSTNode<Key, E> *root, const Key &k);
	BSTNode<Key, E> *removeHelp(BSTNode<Key, E> *root, const Key &k);
	void preorderHelp(BSTNode<Key, E> *root);

public:
	BSTree() { root = nullptr; }
	~BSTree() {}
	void clear();
	void insert(const Key &k, const E &e);
	E find(const Key &k);
	E remove(const Key &k);
	BSTNode<Key, E> *deleteMin(BSTNode<Key, E> *root);
	int size();
	int height();
	BSTNode<Key, E> *getMin(BSTNode<Key, E> *root);
	void preorder() { preorderHelp(root); }
};

template <typename Key, typename E>
void BSTree<Key, E>::clearHelp(BSTNode<Key, E> *root)
{
	if (root->isLeaf())
		delete root;
	clearHelp(root->left());
	clearHelp(root->right());
}

template <typename Key, typename E>
void BSTree<Key, E>::clear()
{
	clearHelp(root);
}

template <typename Key, typename E>
BSTNode<Key, E> *BSTree<Key, E>::insertHelp(BSTNode<Key, E> *root, const Key &k, const E &e)
{
	if (root == nullptr)
		return new BSTNode<Key, E>(k, e);
	if (k < root->getKey())
		root->setLeft(insertHelp(root->left(), k, e));
	else
		root->setRight(insertHelp(root->right(), k, e));
	return root;
}

template <typename Key, typename E>
void BSTree<Key, E>::insert(const Key &k, const E &e)
{
	root = insertHelp(root, k, e);
	count++;
}

template <typename Key, typename E>
E BSTree<Key, E>::findHelp(BSTNode<Key, E> *root, const Key &k)
{
	if (root == nullptr)
		return 0;
	if (k < root->getKey())
		return findHelp(root->left(), k);
	else if (k > root->getKey())
		return findHelp(root->right(), k);
	else
		return root->getElement();
}

template <typename Key, typename E>
E BSTree<Key, E>::find(const Key &k)
{
	return findHelp(root, k);
}

template <typename Key, typename E>
BSTNode<Key, E> *BSTree<Key, E>::removeHelp(BSTNode<Key, E> *root, const Key &k)
{
	if (root == nullptr)
		return nullptr;
	else if (k < root->getKey())
		root->setLeft(removeHelp(root->left(), k));
	else if (k > root->getKey())
		root->setRight(removeHelp(root->right(), k));
	else
	{
		if (root->left() == nullptr)
		{
			BSTNode<Key, E> *temp = root;
			root = root->right();
			delete temp;
		}
		else if (root->right() == nullptr)
		{
			BSTNode<Key, E> *temp = root;
			root = root->left();
			delete temp;
		}
		else
		{
			BSTNode<Key, E> *temp = getMin(root->right());
			root->setElement(temp->getElement());
			root->setKey(temp->getKey());
			root->setRight(deleteMin(root->right()));
			delete temp;
		}
	}
	return root;
}

template <typename Key, typename E>
E BSTree<Key, E>::remove(const Key &k)
{
	E e = findHelp(root, k);
	if (e != 0)
	{
		root = removeHelp(root, k);
		count--;
	}
	return e;
}

template <typename Key, typename E>
BSTNode<Key, E> *BSTree<Key, E>::deleteMin(BSTNode<Key, E> *root)
{
	if (root->left() == nullptr)
		return root->right();
	else
		root->setLeft(deleteMin(root->right()));
	return root;
}

template <typename Key, typename E>
int BSTree<Key, E>::height()
{
	if (root == nullptr)
		return 0;
	return 1 + max(height(root->left()), height(root->right()));
}

template <typename Key, typename E>
int BSTree<Key, E>::size()
{
	return count;
}

template <typename Key, typename E>
BSTNode<Key, E> *BSTree<Key, E>::getMin(BSTNode<Key, E> *root)
{
	if (root->left() == nullptr)
		return root;
	return getMin(root->left());
}

template <typename Key, typename E>
void BSTree<Key, E>::preorderHelp(BSTNode<Key, E> *root)
{
	if (root == nullptr)
	{
		cout << "/ ";
		return;
	}
	cout << root->getElement() << " ";
	preorderHelp(root->left());
	preorderHelp(root->right());
}

#endif // !BSTREE_H
