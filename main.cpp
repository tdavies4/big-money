//
//  main.cpp
//  group ibrahim part
//
//  Created by ibrahim ibrahim on 6/9/15.
//  Copyright (c) 2015 ibrahim ibrahim. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>
#include<fstream>
#include <stdlib.h>
#include <cmath>
#include "scrapper.h"
#include "hash.h"
#include "BinarySearchTree.h"
#include "linkedlist.h"
using namespace std;



// parse data then create objects,
void readinfile(HASH*, BinarySearchTree<Scrapper> *tree1Ptr,BinarySearchTree<Scrapper> *tree2Ptr);

// used to parse the data, readinfile helper
void seperatedata(string&, string&, int&, int&, int&, int&, string&, string&, double&, double&);

void printSkyscrapers();

// display function to pass to BST traverse functions
void display(Scrapper & anItem)
{
    cout  << anItem << endl;
    cout << endl;
}

// display2 print indented list
void display2(Scrapper & anItem, int&  num)
{
    for (int x=0; x<num+2; x++)
    {
        cout<<'\t';
    }
    
    cout << num << ":" << anItem << endl;
    cout <<endl;
    
}

// check is used to check if value is found in tree
void check(bool success)
{
    if (success)
        cout << "found." << endl;
    else
        cout << " Entry not in tree." << endl;
}

// hash table menu
void menu(HASH*);

// tree menu
void menu_tree(BinarySearchTree<Scrapper> *tree1Ptr,BinarySearchTree<Scrapper> *tree2Ptr);

// Haversine helper
double Radians(double value);

// finds distance between two coordinates
double Haversine( double dlatitude1, double dlongitude1, double dlatitude2, double dlongitude2, double radius );


int main()
{
   
    BinarySearchTree<Scrapper>* tree1Ptr= new BinarySearchTree<Scrapper>;
    tree1Ptr->setCompareByUniqueKey(true);
    
    BinarySearchTree<Scrapper>* tree2Ptr= new BinarySearchTree<Scrapper>;
    tree2Ptr->setCompareByUniqueKey(false);
    
    HASH* hash = new HASH(20);
    
    readinfile(hash,tree1Ptr,tree2Ptr);
    
    printSkyscrapers();
    
    
    char choice;
 
    cout << "LADIES AND GENTLEMEN WELCOME TO THE MAIN EVENT LETS GET READY TO make hashtables and bst's" << endl;
    cout << endl;
    cout << "pick and choose your weapon, (hashtable or bst)" << endl;
    do
    {
     
        cout << endl;
        cout << "enter H for hashtable or B for bst; (or Q to exit): ";
        cin>>choice;
        
        if(toupper(choice)=='H')
            menu(hash);
        
        if (toupper(choice)=='B')
            menu_tree(tree1Ptr,tree2Ptr);
        
    }while(toupper(choice)!='Q');
   
    
    
 
    
    delete tree1Ptr;
    delete tree2Ptr;
    delete hash;
    
    cout<<endl;
    cout<<endl;
    cout<<endl;
    cout << "WE DID THIS SO WE WON'T GET FINED " << endl;
    
    
   
    return 0;
}


void readinfile(HASH* hash,BinarySearchTree<Scrapper> *tree1Ptr,BinarySearchTree<Scrapper> *tree2Ptr)
{
    ifstream infile;
    infile.open("tower.txt");
    if(!infile)
    {
        cout << "No such file exists." << endl;
		return;
    }
    
    string temp;
    string na;
    int flo = 0;
    int yea = 0;
    int ft = 0;
    int m = 0;
    string cit;
    string coun;
    double longt;
	double lat;
    
    while(getline(infile, temp))
    {
        //cout << temp << endl;
        seperatedata(temp, na, flo, yea, ft, m, cit, coun, longt, lat);
        Scrapper data(na, ft, m, coun, flo, cit, yea, longt, lat);
        hash->add(data);
        tree1Ptr->insert(data);
        tree2Ptr->insert(data);
    }
    infile.close();    
}


void seperatedata(string& temp, string& na, int& flo, int& yea, int& ft,
                  int& m, string& cit, string& coun, double& longt, double& lat)
{
    int i = 0;
    string floor;
    
    na = temp.substr(0, temp.find(';'));
    i = i + na.length() + 1;
    cit = temp.substr(i, temp.find(';', i) - i);
    i = i + cit.length() + 1;
    coun = temp.substr(i, temp.find(';', i) - i);
    i = i + coun.length() + 1;
    m = atoi(temp.substr(i, temp.find(';', i) - i).c_str());
    i = i + temp.substr(i, temp.find(';', i) - i).length() + 1;
    ft = atoi(temp.substr(i, temp.find(';', i) - i).c_str());
    i = i + temp.substr(i, temp.find(';', i) - i).length() + 1;
    flo = atoi(temp.substr(i, temp.find(';', i) - i).c_str());
    i = i + temp.substr(i, temp.find(';', i) - i).length() + 1;
    yea = atoi(temp.substr(i, temp.find(';', i) - i).c_str());
    i = i + temp.substr(i, temp.find(';', i) - i).length() + 1; 
    longt = atof(temp.substr(i, temp.find(';', i) - i).c_str());
	i = i + temp.substr(i, temp.find(';', i) - i).length() + 1;
	lat = atof(temp.substr(i, temp.length() - i).c_str());
	

}




/*******
 menu display the menu.
 let the user select from the menu.
 *******/
void menu(HASH*hash)
{
    cout<<endl;
    cout <<  "        Hash-Table made COOL"<< '\n'<<endl;
    
    
    cout<< "    PRINTERS" <<endl;
    cout<< "'D' Display content of the hash table"<<endl;
    cout<< "'O' Print overflow from hash table " << endl;
    cout<< "'P' Print the hash tabel"<<endl;
    cout<< "'M' Show Menu"<<endl;
    cout<< "'T' Show the statistics "<<endl;
    cout<<endl;
    
    cout<< "    SEARCHERS"<<endl;
    cout<< "'S' Search for skyscaper in the hash table"<<endl;
    cout<<endl;
    
    
    cout<< "    OTHERS "<<endl;
    cout<< "'H' Height comparison between you and any skyscrapper " << endl;
    cout<< "'A' Add a skyscraper to the data structure"<<endl;
    cout<< "'R' Remove skyscraper from hash table" << endl;
    cout<<endl;
    
    cout<< "'Q' Quit"<<endl;
    
    
    cout<<endl;
   
    char choice;
    
    do
    {
        
        
        cout << "enter choice: " ;
        cin>>choice;
		cin.ignore(100, '\n');
		cin.clear();
        cout<<endl;
        
        if (toupper(choice)=='A')
        {
            string test, name,city,country;
            int meter,feet,floors;
            double lat,lon;
			int year = 2015;
            
           
            

			cout << "enter the name of the skyscraper: ";
			getline(cin, name);
			cout << endl;
            
			cout << "enter the city in which to build the skyscraper ";
			cin.clear();
			getline(cin, city);
			
			cout << endl;
            
            
            cout<<"enter the country in which to build the skyscraper: ";
			cin.clear();
			getline(cin, country);
			
			cout << endl;
            
          
           
            
            cout<<"enter the height of the building (meters): ";
            cin.clear();
            cin>>meter;
			cout << endl;
            
            
            feet=meter*.3048;
            
            cout<<"how many floors should the building have: ";
            cin.clear();
            cin>>floors;
			cout << endl;
            
            
          
            cout << "enter latitude: ";
            cin.clear();
            cin>>lat;
			cout << endl;
           
            
           cout << "enter longitude: ";
           cin.clear();
           cin>> lon;
		   cout << endl;

		   


			 
			   Scrapper new_tower(name, feet, meter, country, floors, city,year,lon,lat);
			   hash->add(new_tower);
            
            
        }
        
        if (toupper(choice)=='S')
        {
            string name;
            cout << "what's the name of the skyscraper you are looking for: ";
            //cin.ignore();
            getline(cin,name);
            cout<<endl;
            
            Scrapper max=hash->search(name);
            
            if (max.empty())
            {
                cout << "'skyscraper not found in file'"<< '\n'<<endl;
            }
            else
            {
               
                cout << "'found' " <<endl;
                cout << max << '\n' << endl;
            }
        }
        if(toupper(choice)=='H')
        {
            string name;
            cout << "what's the name of the skyscraper you are looking for: ";
           // cin.ignore();
            getline(cin,name);
            cout<<endl;
            
            
            Scrapper max=hash->search(name);
            
            if (max.empty())
            {
                cout << "skyscraper not found in file"<< '\n'<<endl;
                
            }
            else
            {
                
                double height = 0;
                cout << "Enter your height in feet; ex.(5.11) :";
                cin >> height;
                cin.ignore();
                cout<<endl;
               
                cout << "It would take " << max.getheightft() / height << " of you standing on top of eachother to be as tall as this tower!"<< '\n'<<endl;
            }
            
        }
        
        if (toupper(choice)=='R')
        {
            bool succes;
            
            string name;
            cout << "enter name of skyscraper you want to remove: " ;
            //cin.ignore();
            getline(cin,name);
            cout<<endl;
            
            succes = hash->remove(name);
            
            if(succes)
                cout << "'removed'" << '\n'<<endl;
            else
                cout << "skyscraper not found in file"<< '\n'<<endl;
                
            
        }
        
        if(toupper(choice)=='D')
        {
            hash->print();
            
        
        }
        
        if (toupper(choice)=='O')
        {
            cout << "overflow" << '\n'<<endl;
            hash->print_overflow();
        }
        
        
        if(toupper(choice)=='P')
        {
            hash->print_two();
        }
        
        if(toupper(choice) =='T')
        {
            double load = hash->return_load();
            double hashsize = hash->return_hashsize();
            double collision = hash->return_collisions();
            
            
            cout << "total collisions                        :" << hash->return_collisions() <<  '\n'<<endl;
            cout << "load factor %                           :" << 100*(load/hashsize)<< "%"<< '\n'<<endl;
            cout << "amount of full buckets                  :" << hash->return_buc_two() << '\n'<<endl;
            cout << "amount of empty buckets                 :" << hash->empty_buckets()  << '\n' <<endl;
            cout << "average number of nodes per bucket      : " << (collision/load) << '\n'<<endl;
          
           
            
            
        }
        
        if(toupper(choice)=='M')
        {
            cout<<endl;
            cout <<  "        Hash-Table made COOL"<< '\n'<<endl;
            
            
            cout<< "    PRINTERS" <<endl;
            cout<< "'D' Display content of the hash table"<<endl;
            cout<< "'O' Print overflow from hash table " << endl;
            cout<< "'P' Print the hash tabel"<<endl;
            cout<< "'M' Show Menu"<<endl;
            cout<< "'T' Show the statistics "<<endl;
            cout<<endl;
            
            cout<< "    SEARCHERS"<<endl;
            cout<< "'S' Search for skyscaper in the hash table"<<endl;
            cout<<endl;
          
            
            cout<< "    OTHERS "<<endl;
            cout<< "'H' Height comparison between you and any skyscrapper " << endl;
            cout<< "'A' Add a skyscraper to the data structure"<<endl;
            cout<< "'R' Remove skyscraper from hash table" << endl;
            cout<<endl;
            
            
            cout<< "'Q' Quit"<<endl;
            
            
            cout<<endl;
        }
        
       
        
    }while(toupper(choice)!='Q');
    
}


void menu_tree(BinarySearchTree<Scrapper> *tree1Ptr,BinarySearchTree<Scrapper> *tree2Ptr)
{
   
    char choice;
    cout<<endl;
    cout << "            BST MENU"<< '\n'<<endl;
    
    cout<< "    PRINTERS" <<endl;
    cout << "B: print tree by Breadth-First Traversal  " << endl;
    cout << "D: print tree by Depth-First Traversal. (all 3 ways) " << endl;
    cout << "I: print indented list " << endl;
    cout << "R: Print specific range in the Tree " << endl;
    cout << "M: print menu " << endl;
    cout<<endl;
    
    cout<< "    SEARCHERS"<<endl;
    cout << "1: search tree by Primary Key (name) " << endl;
    cout << "2: search tree by Secondary Key (height) " << endl;
    cout<<endl;
    
    cout<< "    OTHERS "<<endl;
    cout << "A: add a skyscraper to the data structure" << endl;
    cout << "C: calculate distance to any building (in miles)  " << endl;
    cout << "L: Height comparison between you and any skyscrapper " << endl;
    cout << "N: remove skyscraper from file " << endl;
    cout<<endl;
   
    
    cout << "Q: Quit " << '\n'<<endl;
    
    do
    {
      
        cout<< "enter choice: ";
        cin>>choice;
		cin.ignore(100, '\n');
		cin.clear();
		cout << endl;

            // while loop
        
        if (toupper(choice)=='B' )
        {
            cout << "breadth" << '\n'<<endl;
            tree1Ptr->tree_breadth(display);
        }// end if
        
        else if (toupper(choice)=='D' )
        {
            cout << "Inorder"<< '\n'<<endl;
            tree1Ptr->inOrder(display);
            
            cout << "postOrder" << '\n'<<endl;
            tree1Ptr->postOrder(display);
            
            cout << "preOrder" << '\n'<<endl;
            tree1Ptr->preOrder(display);
        } // end if
        else if (toupper(choice)=='I' )
        {
            cout << "indented" << '\n'<<endl;
            tree1Ptr->print_indented(display2);
        } // end if
        else if (toupper(choice)=='R' )
        {
            int min;
            int max;
            cout << "choose the range to print in terms of height (ft)" << '\n'<<endl;
            
            cout<< "Enter the minimum height: " ;
            cin>>min;
            cin.clear();
            cout<<endl;
            
            Scrapper low;
            low.setheight(min);
            
            cout<< "Enter the maximum height: " ;
            cin>>max;
            cin.clear();
            cout << endl;
            
            Scrapper high;
            high.setheight(max);
            
            tree1Ptr->range(display, low, high);
        } // end if
        else if (toupper(choice)=='A')
        {
			string test, name, city, country;
			int meter, feet, floors;
			double lat, lon;
			int year = 2015;




			cout << "enter the name of the skyscraper: ";
			getline(cin, name);
			cout << endl;

			cout << "enter the city in which to build the skyscraper ";
			cin.clear();
			getline(cin, city);

			cout << endl;


			cout << "enter the country in which to build the skyscraper: ";
			cin.clear();
			getline(cin, country);

			cout << endl;




			cout << "enter the height of the building (meters): ";
			cin.clear();
			cin >> meter;
			cout << endl;


			feet = meter*.3048;

			cout << "how many floors should the building have: ";
			cin.clear();
			cin >> floors;
			cout << endl;



			cout << "enter latitude: ";
			cin.clear();
			cin >> lat;
			cout << endl;


			cout << "enter longitude: ";
			cin.clear();
			cin >> lon;
			cout << endl;




		
			Scrapper add(name, feet, meter, country, floors, city, year, lon, lat);

			tree1Ptr->insert(add);

        } // end if
        else if (toupper(choice)=='1')
        {
            string key;
            cout << "Enter the name of a skyscaper to see if it's in the tree: ";
            //cin.ignore();
            getline(cin,key,'\n');
            cout<<endl;
           
            Scrapper search;
            search.setname(key);
            Scrapper result;
            if(tree1Ptr->getEntry(search, result))
            {
                cout<< key <<" 'found'"<< '\n'<<endl;
              
                cout <<result << '\n' << endl;
            }
            else
            {
                cout << " 'not found' "<< '\n'<<endl;
            }
            
        } // end if
        else if (toupper(choice)=='2')
        {
            int key;
            cout << "Enter the height of a skyscaper to see if it's in the tree: (there may be more than one skyscaper with the same height): ";
            cin>>key;
            cout<<endl;
            
           
            cin.clear();
            Scrapper search;
            search.setheight(key);
            
            linklist* result = new linklist;
			if (tree2Ptr->getEntries(search, result))
			{
				cout << " found." << '\n' << endl;
				result->print();
				delete result;
			}
			else
				cout << " not found." << '\n' << endl;
        }
        else if (toupper(choice)=='L')
        {
            double height;
            string key;
            cout << "Enter the name of a skyscaper to see if it's in the tree: ";
           // cin.ignore();
            getline(cin,key,'\n');
            cout<<endl;
            
           
            Scrapper search;
            search.setname(key);
            Scrapper result;
            if(tree1Ptr->getEntry(search, result))
            {
                cout << key <<" 'found'"<< '\n'<<endl;
                
                cout << "enter your height (ft) : ";
                cin>>height;
                cin.ignore();
                cout<<endl;
                
                  cout << "It would take " << result.getheightft() / height << " of you standing on top of eachother to be as tall as this tower!"<< '\n'<<endl;
                
            }
            else
            {
                cout << " 'not found' "<< '\n'<<endl;
            }

        } // end if
        else if(toupper(choice)=='N')
        {
            bool succes;
            
            
			string name;
            cout << "enter name of skyscraper you want to remove: ";
			//cin.ignore();
			getline(cin, name);
			cout << endl;
			cout << name << " ";
            
            Scrapper remove;
            remove.setname(name);
            
            succes = tree1Ptr->remove(remove);
            if (succes)
                cout << "removed" << '\n'<< endl;
            else
                cout << "not found" << '\n' << endl;
            

            
        }// end if
        else if (toupper(choice)=='C')
        {
            // search for the tower
            double earth_radius=3959;
            
            string key;
            cout << "enter the name of the skyscraper, to find the distance: ";
            //cin.ignore();
            getline(cin,key,'\n');
            cin.clear();
            cout<<endl;
            
            Scrapper search;
            search.setname(key);
            Scrapper result;
            
            tree1Ptr->getEntry(search, result);
            
            if(result.empty())
                cout << "'not found'"<< '\n'<<endl;
            else
                cout << "'found'" << '\n'<<endl;
           
         
            
            // IF the the search was successful
            if(!result.empty())
            {
                double result_lat = result.getlatitude();
                double result_lon = result.getlongitude();
                char answer;
               
                cout<< "Enter X, if you want to enter your coordinates, or enter Z for default coordinates (de anza): ";
                cin >> answer;
                cin.clear();
                cout<<endl;
                
                if (toupper(answer)=='X')
                {
                    double start_lat;
                    cout << "enter latitude: ";
                    cin>>start_lat;
                    cin.clear();
                
                double start_lon;
                cout << "enter longitude: ";
                cin>> start_lon;
                
                cout << "distance from your coordinates to " <<result.getname() << " " << "is ";
                cout << Haversine(result_lat, result_lon, start_lat, start_lon, earth_radius) << " " << " miles" << '\n'<<endl;
                }// end of if(choice=='X')
                
                if (toupper(answer)=='Z')
                {
                    double start_lat=37.3192;
                    double start_lon=122.0453;
                    
                    cout << "distance from de anza to " <<result.getname() << " " << "is ";
                    cout << Haversine(result_lat, result_lon, start_lat, start_lon, earth_radius) << " " << " miles" << '\n'<<endl;
                }
             
            }// end if (!result.empty())
            cin.ignore();
        } // end coordinates
        else if (toupper(choice)=='M')
        {
            cout<<endl;
             cout << "            BST MENU"<< '\n'<<endl;
            
            cout<< "    PRINTERS" <<endl;
            cout << "B: print tree by Breadth-First Traversal  " << endl;
            cout << "D: print tree by Depth-First Traversal. (all 3 ways) " << endl;
            cout << "I: print indented list " << endl;
            cout << "R: Print specific range in the Tree " << endl;
            cout << "M: print menu " << endl;
            cout<<endl;
            
            cout<< "    SEARCHERS"<<endl;
            cout << "1: Search tree by Primary Key (name) " << endl;
            cout << "2: Search tree by Secondary Key (height) " << endl;
            cout<<endl;
            
            cout<< "    OTHERS "<<endl;
            cout << "A; add a skyscraper to the data structure" << endl;
            cout << "C: calculate distance to any building (in miles)  " << endl;
            cout << "L: Height comparison between you and any skyscrapper " << endl;
            cout << "N: remove skyscraper from file " << endl;
            cout<<endl;
           
            
            cout << "Q: Quit " << '\n'<<endl;
            

        } // end if
        
        
        
    
    }while(toupper(choice)!='Q'); // end do while
    

}





double Radians(double value)
{
    double radians = value * 3.41 / 180.0;
    return radians;
}

double Haversine( double dlatitude1, double dlongitude1, double dlatitude2, double dlongitude2, double radius )
{
    double dLatitude = Radians( dlatitude2-dlatitude1 );
    double dLongitude = Radians( dlongitude2-dlongitude1 );
    double nA = pow ( sin( dLatitude/2.0 ), 2.0 ) + cos( Radians(dlatitude1) ) * cos( Radians(dlatitude2) ) * pow ( sin( dLongitude/2.0), 2.0 );
    double nC = 2.0 * atan2( sqrt(nA), sqrt( 1.0 - nA ));
    double distance = radius * nC;
    return distance;
}

void printSkyscrapers()
{
    cout << "     | " << endl;
    cout << "     | " << endl;
    cout << "     | " << endl;
    cout << "     | " << endl;
    cout << "     ^" << endl;
    cout << "    / \\" << endl;
    cout << "   /  \\\\" << endl;
    cout << "   =====" << endl;
    cout << "   | *||" << endl;
    cout << "   | *||" << endl;
    cout << "   | *||" << endl;
    cout << "   | *||" << endl;
    cout << "   | *||\\" << endl;
    cout << "   | *|||" << endl;
    cout << "   | *|||" << endl;
    cout << "   | *|||" << endl;
    cout << "   | *|||" << endl;
    cout << "   | *|||" << endl;
    cout << " //=======                                        |" << endl;
    cout << " | |    *||                                       ^" << endl;
    cout << " | |   *||                                       ---" << endl;
    cout << " | |   *||        '''''''''''''''''             -----"<< endl;
    cout << " | |   *||        |' =========== '|            )     ("<< endl;
    cout << " | |   *||        | '\\        /'  |            ======="<< endl;
    cout << " | |   *||        |   '\\     /'   |           )       ("<< endl;
    cout << " | =======        |     -----     |           =========" << endl;
    cout << " | |   *||\\\\      |      '''      |          )         ("<< endl;
    cout << " | |   *|| |      |       |       |          ==========="<< endl;
    cout << " | |   *|| |      |       |       |          ||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |          ||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |          ||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |    ______||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   |******||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   |------||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| |      |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| |\\     |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| ||     |       |       |   | |_|_|||--     *|"<< endl;
    cout << " | |   *|| ||     |       |       |   | |_|_|||--     *|"<< endl;
    cout << "-------------     |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|" << endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|\\\\"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_|||--     *|\\\\\\"<< endl;
    cout << "|-     *||  ||    |       |       |   | |_|_| ----------\\\\\\\\\\"<< endl;
    cout << "|-     *||  ||    |       |       |   |   ////||||||||||\\\\\\\\\\\\"<< endl;
    cout << "|-     *||  ||    |       |       |   |////|||||||||||||\\\\\\\\\\\\\\" << endl;
    cout << "";
    
    
    cout << endl;
       cout << endl;
       cout << endl;
       cout << endl;
       cout << endl;
}



