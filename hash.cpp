// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    node* created = new node{restaurantName, PriorityQ(50), next};
    return created;
}

HashTable::HashTable(int bsize)
{
    table = new node*[bsize];
    tableSize = bsize;
    numCollision = 0;
}

HashTable::~HashTable()
{
    for(int i = 0;i < tableSize;i++)
    {
        node*  iterator = table[i];
        while(iterator != nullptr)
        {
            node* temp = iterator->next;
            delete iterator;
            iterator = temp;
        }
    }
    delete[] table;
    tableSize = 0;
    numCollision = 0;
}

void HashTable::displayTable()
{
    //iterate over the table 
    for(int i = 0;i < tableSize;i++)
    {
        //take head of the table index
        node* curr = table[i];
        cout << i << "|";
        while(curr != nullptr)
        {
            cout << curr->restaurantName << "-->";
            curr = curr->next;
        }
        cout << "NULL" << endl;
    } 
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    //initialize the sum of the ascii values
    int sum = 0;
    for(int i = 0;i < restaurantName.length();i++)
    {
        //for each character in the restaurant name, add the ascii value
        sum += restaurantName[i];
    }
    //return the sum mod the table size
    return(sum%tableSize);
}

node* HashTable::searchItem(string restaurantName)
{
    //Get the index and chain head of the given restaurant name
    int index = hashFunction(restaurantName);
    node* iterator = table[index];

    //iterate throught the linked list while the node's restaurant name is NOT equal
    while(iterator != nullptr && iterator->restaurantName != restaurantName)
    {
        iterator = iterator->next;
    }
    
    //return the value after traversal
    return iterator;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    //Search for the given restaurant
    node* search = searchItem(restaurant.restaurantName);
    if(search != nullptr)
    {
        //if search returns a value that isn't null, insert the restaurant into the priority queue
        search->pq.insertElement(restaurant);
        return;
    }

    //if the code reaches here, the value it finds is null, so update the hash table accordingly
    //get the index that the restaurant should be added into
    int index = hashFunction(restaurant.restaurantName);
    node* created = createNode(restaurant.restaurantName, table[index]);
    created->pq.insertElement(restaurant);

    if(table[index] != nullptr)
    {
        //if the table's head pointer is not null, there is a collision
        numCollision++;
        table[index] = created;
        return;
    }
    //if the table's head pointer is null, there is no collision
    table[index] = created;
}


void HashTable::setup(string fname)
{
    //variable initialization
    ifstream input;
    input.open(fname);
    
    string line = "";
    string restoName = "";
    string review = "";
    string name = "";
    string stime = "";
    ReviewInfo restaurant;

    if(!input.is_open())
    {
        cout << "File not found!" << endl;
        return;
    }
    //while there are lines to take an input of the file
    while(getline(input, line))
    {
        stringstream ss(line);
        getline(ss, restoName,';');
        getline(ss, review, ';');
        getline(ss,name,';');
        getline(ss,stime);

        //creating the restaurant object
        restaurant.restaurantName = restoName;
        restaurant.review = review;
        restaurant.customer = name;
        restaurant.time = stoi(stime);

        //after creation, insert the item into the hashtable
        insertItem(restaurant);
    }

    return; 
}