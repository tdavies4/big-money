//
//  linkedlist.h
//  pre-final
//
//  Created by ibrahim ibrahim on 6/12/15.
//  Copyright (c) 2015 ibrahim ibrahim. All rights reserved.
//

#ifndef __pre_final__linkedlist__
#define __pre_final__linkedlist__

#include <stdio.h>
#include "scrapper.h"
#include <string>
#include <iostream>
using namespace std;

class linklist
{
private:
    // Declare a structure for the list
    struct ListNode
    {
        Scrapper toy_object; // The object in this node
        ListNode* next;      // To point to the next node
        ListNode* prev;      // To point to the prev node
        
    };
    
    ListNode* head;
	
    bool empty;
    
public:
    // Constructor
    linklist();
    
    // Linked list operations
    void insert(Scrapper& spot);
    void print();
    void deleta();
   
    bool isEmpty()
    {
        return empty;
    }
};




#endif /* defined(__pre_final__linkedlist__) */
