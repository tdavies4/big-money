//
//  hash.cpp
//  group ibrahim part
//
//  Created by ibrahim ibrahim on 6/9/15.
//  Copyright (c) 2015 ibrahim ibrahim. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "hash.h"
#include "linkedlist.h"
#include "scrapper.h"
using namespace std;

/*****
 constructor
 
 *****/
HASH::HASH( int x)
{
    rejected = new linklist;
    
    hashtablesize=x;
    load=0;
    collisions=0;
    fullbucket=0;
    
    
    item bucket;
    bucket.count=0;
    
    Scrapper choice("empty",0,0,"empty",0,"empty",0,0,0);
    bucket.my_array[0]=choice;
    bucket.my_array[1]=choice;
    bucket.my_array[2]=choice;
    
    ptr = new item[hashtablesize];
    for (int i = 0; i < hashtablesize; i++)
    {
        ptr[i] = bucket;
        
    }
    
}



/*****
 gethashed  compute the index for the hashtable
 return a unique(int index) using the string key
 ******/
int HASH::gethashed(string key)
{
    if(key.length()>6)
        key.erase(6);
    
    int size=0;
    int index;
    int y=0;
    for (int x=0; x<key.length(); x++)
    {
        size=size + (int)key[x];
        y++;
    }
    index=size%hashtablesize;
    return index;
}



/******
 add @ single_item
 create a unique key using the data in single_item
 check if the unique key address is available. if so insert single_item into the bucket
 if not display it to hash_output.txt
 ******/
bool HASH::add(Scrapper& single_item)
{
    
    
    int index;
    index=gethashed(single_item.getname());
    
    
   
    
    for(int x=0 ; x<3 ; x++ )
    {
        
        
        
        if(ptr[index].my_array[x].empty() )
        {
            if (ptr[index].my_array[0].empty())
                load++;
            
            // collisoons
            if(x==1||x==2)
                collisions++;
            if(x==2)
                fullbucket++;
            
            
            ptr[index].my_array[x]=single_item;
            ptr[index].count++;
            
            return true;
        }
        // if bucket is full print to txt file
        if( x==2)
        {
            
         rejected->insert(single_item);
            
            return false;
        }
        
        
    }
    
    return false;
    
}

/******
 print
 check if the address is not empty, if not the print the
 content of the address
 *****/
void HASH::print()
{
    for (int x=0; x<hashtablesize; x++)
    {
        for (int y=0; y<3; y++)
        {
            if (!ptr[x].my_array[y].empty())
            {
                cout << ptr[x].my_array[y] << endl;
                cout << endl;
            }
        }
    }
    
    
    
}

/******
 print_two
 print the hashtalbe.
 *****/
void HASH::print_two()
{
    for (int x=0; x<hashtablesize; x++)
    {
        cout << endl;
        if(!ptr[x].my_array[0].empty())
            cout << "Index:" << x << " ";
        
        for (int y=0; y<3; y++)
        {
            if (!ptr[x].my_array[y].empty())
            {
                if (y==1||y==2)
                {
                    cout <<"                            ";
                }
                cout<<ptr[x].my_array[y]<<endl;;
            }
        }
    }
}


/******
 search
 search uses sting (name) to find the item.
 get the index from the name
 there can be multiple items with the same index, so look for the
 object that has the same characteristics
 if found return the object, if not return a empty object
 ******/
Scrapper HASH::search(string name)
{
    
    int index = gethashed(name);
    
    Scrapper ibrahim;
    
    for (int y =0; y<3; y++)
    {
        
        if (ptr[index].my_array[y].getname() == name)
            return ptr[index].my_array[y];
    }
    return ibrahim;
}


bool HASH::remove(string name)
{
    
    int index = gethashed(name);
    
    Scrapper ibrahim;
    
    for (int y =0; y<3; y++)
    {
        
        if (ptr[index].my_array[y].getname() == name)
        {
            
            ptr[index].my_array[y]= ibrahim;
            return true;
        }
    }
    return false;
}


/********
 empty_buckets
 counts the empty_bucket in the hashtable
 ********/
int HASH::empty_buckets()
{
    int count=0;
    
    for (int x=0; x<hashtablesize; x++)
    {
        if (ptr[x].my_array[0].empty())
            count++;
    }
    return count;
}


/******
 destructor
 ******/
HASH::~HASH()
{
    
    delete [] ptr;
}



