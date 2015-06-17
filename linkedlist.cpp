//
//  linkedlist.cpp
//  pre-final
//
//  Created by ibrahim ibrahim on 6/12/15.
//  Copyright (c) 2015 ibrahim ibrahim. All rights reserved.
//

#include "linkedlist.h"
#include "scrapper.h"
#include <iostream>
#include <cstdlib>

using namespace std;



/***************
 Constructor
 **************/

linklist::linklist()
{
    
    ListNode* sental = new ListNode;
    head=sental;
    head->next=head;
    head->prev=head;
    empty = true; //when it's first created, it's automatically empty

    
}



/*************************
 The insert function inserts a node with
 integer copied to its country member.
 *********************************/
void linklist::insert( Scrapper& spot)
{
	
    empty = false; //the moment you insert a skyscraper, linklist isn't empty
    
    ListNode* object = new ListNode;
    object->toy_object=spot;
    
    
    if (head->next==head)
    {
        head->prev=object;
        object->next=head;
        head->next=object;
        object->prev=head;
        
    }
    else
    {
        head->prev->next=object;
        object->prev=head->prev;
        
        object->next=head;
        head->prev=object;
        
        
    }
    
    
}



/***************
 print, prints each number stored in each node
 which is pointed by the head
 print forwards
 **************/
void linklist::print()
{
    
    ListNode* ptr = head;
    ptr=ptr->next;
    
    while (ptr!=head)
    {
        
        
        cout << ptr->toy_object << endl;
        ptr=ptr->next;
        cout << endl;
    }
    cout << endl;
    
}





/*******************
 deleta is basically a deconstructor.
 ******************/
void linklist::deleta()
{
    
    ListNode *ptr = head;
    ptr=ptr->next;
    
    
    while (ptr!=head)
    {
        ListNode *temp;
        
        temp = ptr;
        ptr = ptr->next;
        delete temp;
    }
    
    head->next=head;
    head->prev=head;
    
    
}
