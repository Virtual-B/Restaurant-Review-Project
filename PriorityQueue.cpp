#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    //Storing value of a into a temp variable
    ReviewInfo temp = *a;
    //swapping pointer values
    *a = *b;
    //setting ptr b to temp variable value
    *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    //set heapArr to reviews
    heapArr = new ReviewInfo[cap];
    //capacity set to cap
    capacity = cap;
    //no elements stored in q yet, so size of 0
    currentSize = 0;
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete[] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
    return((index-1)/2);
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return((2 * index)+1);
}

/*
Returns the right child of a node.
*/
int PriorityQ::rightChild(int index)
{
    return((2 * index)+2);
}

void PriorityQ::peek()
{
    //checking amount of elements
    if(currentSize == 0)
    {
        cout << "no record found" << endl;
        return;
    }

    //printing top element out
    ReviewInfo rw = heapArr[0];
    cout << "Restaurant: " << rw.restaurantName << endl;
    cout << "Customer: " << rw.customer << endl;
    cout << "Review: " << rw.review << endl;
    cout << "Time: " << rw.time << endl;
}

void PriorityQ::heapify(int i)
{
    //rearrange the heap (maintain by priority) (maxheap)
    //check size first
    if(currentSize <= 1)
    {
        return;
    }

    //get left and right children of index
    int left = leftChild(i);
    int right = rightChild(i);

    //set the largest in the heap to the index, then verify if it is the largest
    int largest  = i;

    //check left is in bounds and bigger
    if(left < currentSize && heapArr[left].time > heapArr[i].time)
    {
        largest = left;
    }
    else if(right < currentSize && heapArr[right].time > heapArr[i].time)
    {
        largest = right;
    }

    //if largest is no longer the index, swap and heapify
    if(largest != i)
    {
        swap(heapArr[largest], heapArr[i]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    //check if we can add one
    if(currentSize == capacity)
    {
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
        return;
    }

    //if it reaches here, element can be added to the queue
    heapArr[currentSize] = restaurant;
    int current = currentSize;
    currentSize++;

    //swap nodes from the current
    while(current > 0 && heapArr[parent(current)].time < heapArr[current].time)
    {
        //swap as long as while condition runs
        swap(heapArr[parent(current)],heapArr[current]);
        current = parent(current);
    }
}

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    //Go through the heap array and print elements in order of the queue. (If elements to be printed)
    if(currentSize == 0)
    {
        cout << "Queue is empty! No elements to print." << endl;
        return;
    }

    //if it gets here, queue is not empty
    for(int i = 0;i < currentSize;i++)
    {
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    //check size to see if there are elements that can be deleted
    if(currentSize == 0)
    {
        cout << "Queue is empty! No elements to delete." << endl;
        return;
    }

    //Get the last element and swap wth the root
    swap(heapArr[0],heapArr[currentSize]);
    //turn last elemet into a blank
    ReviewInfo blank;
    heapArr[currentSize] = blank;
    //decrement size
    currentSize--;

    //heapify from the root to maintain property
    heapify(0);
}
