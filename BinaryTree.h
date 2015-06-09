// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by:

#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
	BinaryTree() { rootPtr = 0; count = 0; }
	BinaryTree(const BinaryTree<ItemType> & tree){ }
	virtual ~BinaryTree() { }
	BinaryTree & operator = (const BinaryTree & sourceTree);

	// common functions for all binary trees
	//bool isEmpty() const	{ return count == 0; }
	int size() const	    { return count; }
	//void clear()			{ destroyTree(rootPtr); rootPtr = 0; count = 0; }
	void preOrder(void visit(ItemType &)) const { _preorder(visit, rootPtr); }
	void inOrder(void visit(ItemType &)) const  { _inorder(visit, rootPtr); }
	void postOrder(void visit(ItemType &)) const{ _postorder(visit, rootPtr); }


	// abstract functions to be implemented by derived class
	virtual bool insert(const ItemType & newData) = 0;
	virtual bool remove(const ItemType & data) = 0;
	virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
	void displayInorderIndented() const
	{
		displayInorderIndented(rootPtr);
	}

private:
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void displayInorderIndented(BinaryNode<ItemType> *) const;
	int getLevelUtil(BinaryNode<ItemType> *nodePtr, ItemType item, int level) const;

};

//////////////////////////////////////////////////////////////////////////



template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
	BinaryNode<ItemType>* newNodePtr = 0;
	if (nodePtr != nullptr)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem(), nullptr, nullptr);
			newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}

	return newNodePtr;
}

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != nullptr)
	{
		if (nodePtr->getLeftPtr())
			destroyTree(nodePtr->getLeftPtr());
		if (nodePtr->getRightLPtr())
			destroyTree(nodePtr->getRightLPtr());
		delete nodePtr;
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != nullptr)
	{
		ItemType item = nodePtr->getItem();
		_inorder(visit, nodePtr->getLeftPtr());
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != nullptr)
	{
		ItemType item = nodePtr->getItem();
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		visit(item);
	}
}
template <class ItemType>
void BinaryTree<ItemType>::displayInorderIndented(BinaryNode<ItemType> *nodePtr) const
{
	if (nodePtr != nullptr)
	{
		int level = getLevelUtil(rootPtr, nodePtr->getItem(), 1);
		displayInorderIndented(nodePtr->getLeftPtr());
		for (int i = 1; i < level; ++i)
		{
			cout << "\t";
		}
		cout << level << ". " << nodePtr->getItem() << endl;
		displayInorderIndented(nodePtr->getRightPtr());
	}
}
template <class ItemType>
int BinaryTree<ItemType>::getLevelUtil(BinaryNode<ItemType> *nodePtr, ItemType item, int level) const
{
	if (nodePtr == nullptr)
		return 0;

	if (nodePtr->getItem() == item)
		return level;

	int downlevel = getLevelUtil(nodePtr->getLeftPtr(), item, level + 1);
	if (downlevel != 0)
		return downlevel;

	downlevel = getLevelUtil(nodePtr->getRightPtr(), item, level + 1);
	return downlevel;
}

template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{

}


#endif
