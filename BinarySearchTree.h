//
//  BinarySearchTree.h
//  group ibrahim part
//
//  Created by ibrahim ibrahim on 6/9/15.
//  Copyright (c) 2015 ibrahim ibrahim. All rights reserved.
//

#include "BinaryTree.h"
#include "queue.h"
#include "scrapper.h"
#include "linkedlist.h"

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
    // using BinaryTree<ItemType>::rootPtr;
    
    // internal insert node: insert newNode in nodePtr subtree
    BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    
    // internal remove node: locate and delete target node under nodePtr subtree
    BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    
    // delete target node from tree, called by internal remove node
    BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
    // remove the leftmost node in the left subtree of nodePtr
    BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
    // search for target node
    BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* nodePtr, const ItemType & target) const;
    
    //when searching by secondary key we need to gather ALL the duplicate buildings with the same key
    void findNodes(BinaryNode<ItemType>* nodePtr, const ItemType & target, linklist* nodes);
    

    
    
public:
    // insert a node at the correct location
    bool insert(const ItemType & newEntry);
    // remove a node if found
    bool remove(const ItemType & anEntry);
    // find a target node
    bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    //find all the target nodes that match the secondary key
    bool getEntries(const ItemType & target, linklist* itemsFound);
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(const ItemType & newEntry)
{
    BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newEntry);
    this->rootPtr = _insert(this->rootPtr, newNodePtr);
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & target)
{
    
    bool isSuccessful = false;
    this->rootPtr = _remove(this->rootPtr, target, isSuccessful);
    return isSuccessful;
    
    return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry, ItemType & returnedItem) const
{
    
    BinaryNode<ItemType>* nodePtr = findNode(this->rootPtr, anEntry);
    if(nodePtr)
    {
        returnedItem=nodePtr->getItem();
        return true;
    }
    else
    {
        return false;
    }
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntries(const ItemType & target, linklist* itemsFound) {
    
    findNodes(this->rootPtr, target, itemsFound);
    
    return !itemsFound->isEmpty(); //return whether there is something in the list
}

//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
    if (nodePtr==nullptr)
    {
        
        return newNodePtr;
    }
    else if (this->compareSkyscrapers(newNodePtr->getItem(), nodePtr->getItem() )== -1)
    {
        nodePtr->setLeftPtr( _insert(nodePtr->getLeftPtr(),newNodePtr));
    }
    else
    {
        nodePtr->setRightPtr( _insert(nodePtr->getRightPtr(),newNodePtr));
    }
    return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target,
                                                          bool & success)
{
    
    if (nodePtr == 0)
    {
        success = false;
        return 0;
    }
    if (this-> compareSkyscrapers(nodePtr->getItem(), target ) == 1)
        nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
    
    else if (this->compareSkyscrapers(nodePtr->getItem(), target) == -1)
        nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
    else
    {
        nodePtr = deleteNode(nodePtr);
        success = true;
    }
    return nodePtr;
    
    //return NULL;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
    if (nodePtr->isLeaf())
    {
        delete nodePtr;
        nodePtr = 0;
        return nodePtr;
    }
    else if (nodePtr->getLeftPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else if (nodePtr->getRightPtr() == 0)
    {
        BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
        delete nodePtr;
        nodePtr = 0;
        return nodeToConnectPtr;
    }
    else
    {
        ItemType newNodeValue;
        nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
        nodePtr->setItem(newNodeValue);
        return nodePtr;
    }
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
    if (nodePtr->getLeftPtr() == 0)
    {
        successor = nodePtr->getItem();
        return deleteNode(nodePtr);
    }
    else
    {
        nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
        return nodePtr;
    }
}


template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{
    
    if (nodePtr==nullptr)
    {
        return nullptr;
    }
    else
    {
        
        if (this->compareSkyscrapers(nodePtr->getItem(),target) == 0) // if they are the same return node ptr
        {
            return nodePtr;
        }
        else if (this->compareSkyscrapers(nodePtr->getItem(),target)== 1) // if left > right
        {
            return( findNode(nodePtr->getLeftPtr(),target));              // go left
        }
        else
        {
            return ( findNode(nodePtr->getRightPtr(),target));
        }
    }
}

template<class ItemType>
void BinarySearchTree<ItemType>::findNodes(BinaryNode<ItemType>* nodePtr, const ItemType & target, linklist* nodes) {
    //takes in an empty linklist of nodes
    if (nodePtr == nullptr) {
        return;
    }
    else {
        if (this->compareSkyscrapers(nodePtr->getItem(), target) == 0)
        { // if they are the same add node ptr to list of ptrs
            Scrapper item= nodePtr->getItem();
            nodes->insert(item); //I insert the skyscraper in list if it matches target skyscraper
            findNodes(nodePtr->getRightPtr(), target, nodes); //I still need to search for duplicates to its right
        }
        else if (this->compareSkyscrapers(nodePtr->getItem(), target) == 1) // if left > right
        {
            findNodes(nodePtr->getLeftPtr(), target, nodes);              // go left
        }
        else
        {
            findNodes(nodePtr->getRightPtr(), target, nodes); //otherwise go right
        }
    }
}

