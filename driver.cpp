#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1];
    int tableSize = stoi(argv[2]);
    int ch = 0;
    string chs;
    HashTable ht(5);
	bool built = false;

    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
				//
                if(built)
                {
                   cout <<  "The data structure has already been built." << endl;
                   break;
                }
                ht.setup(fname);
                built = true;
				break;
            }
            case 2:
			{
                //
                //creating an instance by adding
                ReviewInfo adding;
                string input = "";
                cout << "Restaurant Name: "; 
                getline(cin, input);
                adding.restaurantName = input;
                cout << "Customer: ";
                getline(cin, input);
                adding.customer = input;
                cout << "Review: ";
                getline(cin, input);
                adding.review = input;
                cout << "Time: ";
                getline(cin, input);
                adding.time = stoi(input);

                //add to the queue
                ht.insertItem(adding);
				break;
            }
            case 3:
			{
                //
                node *search;
                string input = "";
                cout << "Restaurant Name: ";
                getline(cin, input);
                //search using input
                search = ht.searchItem(input);
                if(search != nullptr)
                {
                    cout << "Retrieved result" << endl;
                    search->pq.peek();
                    break;
                }
                cout << "Result not found." << endl;
				break;
            }
            case 4:
			{
                //
                node *search;
                string input = "";
                cout << "Restaurant Name: ";
                getline(cin, input);

                //search using input
                search = ht.searchItem(input);
                if(search != nullptr)
                {
                    search->pq.pop();
                    break;
                }
                cout << "Result not found." << endl;
				break;
            }
            case 5:
			{
				//
                node *search;
                string input = "";
                cout << "Restaurant Name: ";
                getline(cin, input);

                //search using input
                search = ht.searchItem(input);
                if(search != nullptr)
                {
                    search->pq.print();
                    break;
                }
                cout  << "no record found." << endl;
				break;
			}
            case 6:
            {
                //
                //call getnumcollisions
                int collision = ht.getNumCollision();
                cout << "Number of collisions: " << collision << endl;
                break;
            }
            case 7:
            {
                //call display table
                ht.displayTable();
                break;
            }
            case 8:
            {
				break;
            }
            default:
            {
                cout << "Enter a valid option." << endl;
                break;
            }
        }
    }
}
