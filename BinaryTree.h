//
//  BinaryTree.h
//  group ibrahim part
//
//  Created by ibrahim ibrahim on 6/9/15.
//  Copyright (c) 2015 ibrahim ibrahim. All rights reserved.
//

#include "BinaryNode.h"
#include "queue.h"
#include <iostream>
#include <iomanip>
using namespace std;

template<class ItemType>
class BinaryTree
{
protected:
    //******************// //******************// //******************// //******************//
    bool compareUniqueKey = true; //if true: we know we're comparing by the skyscraper's name
                                //if false: we compare by the height
     //******************// //******************// //******************//
    
    BinaryNode<ItemType>* rootPtr;		// ptr to root node
    int count;							// number of nodes in tree
    
public:
    // "admin" functions
    BinaryTree() {rootPtr = 0; count = 0;}
    BinaryTree(const BinaryTree<ItemType> & tree){ }
    virtual ~BinaryTree() { destroyTree(rootPtr); }
    BinaryTree & operator = (const BinaryTree & sourceTree);
    
    // common functions for all binary trees
    bool isEmpty() const	{return count == 0;}
    int size() const	    {return count;}
    void clear()			{destroyTree(rootPtr); rootPtr = 0; count = 0;}
    void preOrder(void visit(ItemType &)) const {_preorder(visit, rootPtr);}
    void inOrder(void visit(ItemType &)) const  {_inorder(visit, rootPtr);}
    void postOrder(void visit(ItemType &)) const{_postorder(visit, rootPtr);}
    int getHeight() const{return getHeightHelper(rootPtr);}
    
    // add function for the binaray tree.
    // print_ indented. prints the tree horizontally
    // range. prints given range in the tree
    // tree_breath prints level by level, from the tree
    void print_indented(void visit(ItemType &, int&)) const {_print_indented(visit, rootPtr,0);}
    void range(void visit(ItemType &), const ItemType one, const ItemType two) const  {_range(visit, rootPtr, one, two);}
    void tree_breadth(void visit(ItemType &)) const { _TreeBreadth(visit,rootPtr); };
    
      //******************// //******************// //******************// //******************//
    
    //function to compare skyscrapers
    int compareSkyscrapers(const Scrapper & s1,const Scrapper & s2)const;
    //specific function to compare skyscrapers by UNIQUE KEY
    int compareByUniqueKey(const Scrapper & s1, const Scrapper & s2)const ;
    //specific function to compare skyscrapers by SECONDARY KEY
    int compareBySecondaryKey(const Scrapper & s1, const Scrapper & s2)const ;
    
    
    void setCompareByUniqueKey(bool compareUnique) {
        compareUniqueKey = compareUnique;
    }
    
      //******************// //******************// //******************// //******************//
    // abstract functions to be implemented by derived class
    virtual bool insert(const ItemType & newData) = 0;
    virtual bool remove(const ItemType & data) = 0;
    virtual bool getEntry(const ItemType & anEntry, ItemType & returnedItem) const = 0;
    
    
private:
    // delete all nodes from the tree
    void destroyTree(BinaryNode<ItemType>* nodePtr);
    
    // copy from the tree rooted at nodePtr and returns a pointer to the copy
    BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);
    
    // internal traverse
    void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
    int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
    
    // internal function to help complete job.
    void _print_indented(void visit(ItemType &,int&), BinaryNode<ItemType>* nodePtr,int num) const;
    void _range(void visit(ItemType &), BinaryNode<ItemType>* nodePtr, const ItemType one, const ItemType two) const;
    void _TreeBreadth(void visit(ItemType &),BinaryNode<ItemType>* nodePtr)const;
    
    
};

//////////////////////////////////////////////////////////////////////////

  //******************// //******************// //******************// //******************//
template<class ItemType>
int BinaryTree<ItemType>::compareSkyscrapers(const Scrapper & s1,const  Scrapper & s2)const  {
    //takes two skyscraper objects, returns 1 if first parameter's data comparison greater than second parameter
    // returns 0 if both skyscrapers' data equal to each other
    //returns -1 if second parameter's compared data greater than first parameter's compared data
    if (compareUniqueKey) {
        return compareByUniqueKey(s1, s2);
    }
    else {
        return compareBySecondaryKey(s1, s2);
    }
}

template<class ItemType>
int BinaryTree<ItemType>::compareByUniqueKey(const Scrapper & s1,const  Scrapper & s2)const  {
    //since I'm comparing by unique key, I know I'm comparing by NAME
    //return 1 if s1's name greater than s2, 0 if both equal, -1 if s2's name greater than s1
    if (s1.getname() > s2.getname()) {
        return 1;
    }
    else if (s1.getname() == s2.getname()) {
        return 0;
    }
    else return -1;
}


template<class ItemType>
int BinaryTree<ItemType>:: compareBySecondaryKey(const Scrapper & s1,const  Scrapper & s2)const  {
    //since I'm comparing by secondary key, I know I'm comparing by HEIGHT
    //return 1 if s1's height greater than s2, 0 if both equal, -1 if s2's height greater than s1
    if (s1.getheightft() > s2.getheightft()) {
        return 1;
    }
    else if (s1.getheightft() == s2.getheightft()) {
        return 0;
    }
    else return -1;
}
  //******************// //******************// //******************// //******************//

template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr)
{
    BinaryNode<ItemType>* newNodePtr = 0;
    
    if(nodePtr != 0)
    {
        
        newNodePtr = new BinaryNode<ItemType> (nodePtr->getItem());
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
        destroyTree(nodePtr->getLeftPtr());
        destroyTree(nodePtr->getRightPtr());
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
    if (nodePtr != 0)
    {
        
        _inorder(visit, nodePtr->getLeftPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
        _inorder(visit, nodePtr->getRightPtr());
        
    }
    
    
    
}

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
    if (nodePtr != 0)
    {
        
        _postorder(visit, nodePtr->getLeftPtr());
        _postorder(visit, nodePtr->getRightPtr());
        ItemType item = nodePtr->getItem();
        visit(item);
    }
    
}



template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
    
    rootPtr = copyTree(sourceTree.rootPtr);
    
    return rootPtr;
}



template<class ItemType>
void  BinaryTree<ItemType>:: _print_indented(void visit(ItemType &, int&), BinaryNode<ItemType>* nodePtr, int num) const
{
    if (nodePtr !=0)
    {
        
        num++;
        _print_indented(visit, nodePtr->getRightPtr(),num);
        
        
        ItemType item = nodePtr->getItem();
        visit(item,num);
        
        _print_indented(visit, nodePtr->getLeftPtr(),num);
        
        
        
    }
}


template<class ItemType>
void BinaryTree<ItemType>::_range(void visit(ItemType &), BinaryNode<ItemType>* nodePtr,const ItemType one, const ItemType two) const
{
    
    if (nodePtr != 0)
    {
        
        _range(visit, nodePtr->getLeftPtr(), one, two);
        if(nodePtr->getItem() >= one && nodePtr->getItem() <= two)
        {
            ItemType item = nodePtr->getItem();
            visit(item);
        }
        _range(visit, nodePtr->getRightPtr(), one, two);
    }
    
}

template<class ItemType>
void BinaryTree<ItemType>::_TreeBreadth(void visit(ItemType &),BinaryNode<ItemType>* nodePtr)const
{
    
    if (nodePtr == 0)
    {
        return;
    }
    BinaryNode<ItemType>* rover = nodePtr;
    
    Queue<BinaryNode<ItemType>* > q;
    
    q.enqueue(rover);
    
    while(!q.isEmpty())
    {
        q.queueFront(rover);
        
        ItemType item = rover->getItem();
        visit(item);
        
        
        if ( rover->getLeftPtr() != NULL )
            q.enqueue(rover->getLeftPtr());
        
        
        if ( rover->getRightPtr() != NULL )
            q.enqueue(rover->getRightPtr());
        
        
        
        q.dequeue(rover);
    }
}


template<class ItemType>
int BinaryTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
    if (subTreePtr == nullptr) return 0;
    else
        return 1 + max(getHeightHelper(subTreePtr->getLeftPtr()),
                       getHeightHelper(subTreePtr->getRightPtr()));
} 

