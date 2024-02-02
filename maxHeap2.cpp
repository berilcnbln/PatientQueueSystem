#include "maxHeap2.h"
#include <iostream>
using namespace std;

MaxHeap::MaxHeap(){
    currentSize = 0;
    items = new MaxHeap::patient[MAX_SIZE];
}

MaxHeap::~MaxHeap(){
    if (!isEmpty()) {
        delete [] items;
        currentSize = 0;
    }
}

int MaxHeap::size(){
    return currentSize;
}

bool MaxHeap::isEmpty(){
    return (currentSize == 0);
}

MaxHeap::patient MaxHeap::top(){
    if (!isEmpty())
        return items[0];
}

void MaxHeap::push(MaxHeap::patient value){
    if (currentSize == MaxHeap::MAX_SIZE - 1) {

        MaxHeap::patient itemCopy[currentSize];
        for(int i = 0; i < currentSize; i++)
            itemCopy[i] = items[i];

        delete [] items;

//      enlargening the size.
        MaxHeap::MAX_SIZE = 2 * MaxHeap::MAX_SIZE;

        items = new MaxHeap::patient[MAX_SIZE];

        for(int i = 0; i < currentSize; i++)
            items[i] = itemCopy[i];


//        cout << "Resize in push happened and the new max_size is" << MaxHeap::MAX_SIZE << endl;

    }
    items[currentSize] = value;
    int pos = currentSize;

    int parent = (pos - 1)/2;
    while ( pos > 0 && greater(items[pos], items[parent])) {
        MaxHeap::patient temp = items[parent];
        items[parent] = items[pos];
        items[pos] = temp;

        pos = parent;
        parent = (pos - 1)/2;
    }
    currentSize++;

}

MaxHeap::patient MaxHeap::pop(){
//    if (isEmpty())
//        return -1;

    if(size() < MAX_SIZE / 2){
        MaxHeap::patient itemCopy[currentSize];
        for(int i = 0; i < currentSize; i++)
            itemCopy[i] = items[i];

        delete [] items;

//      shrinking the heap.
        MaxHeap::MAX_SIZE = MaxHeap::MAX_SIZE / 2;

        items = new MaxHeap::patient[MAX_SIZE];

        for(int i = 0; i < currentSize; i++)
            items[i] = itemCopy[i];

//        cout << "Resize in pop happened and the new max_size is" << MaxHeap::MAX_SIZE << endl;
    }

    MaxHeap::patient maxItem = top();
    heapDelete(items[0]);
    return maxItem;
}

void MaxHeap::heapRebuild(int root){
    int child = (root * 2) + 1;

    if ( child < currentSize ) {
        int right = child + 1;
        if ((right < size()) && greater(items[right], items[child]) )
            child = right;
        if ( greater(items[child], items[root]) ) {
            MaxHeap::patient temp = items[root];
            items[root] = items[child];
            items[child] = temp;

            heapRebuild(child);
        }
    }
}


void MaxHeap::heapDelete(MaxHeap::patient &rootItem){
    if (isEmpty())
        return ;

    rootItem = top();
    items[0] = items[--currentSize];
    heapRebuild(0);
}

bool MaxHeap::greater(MaxHeap::patient &a, MaxHeap::patient &b){
    return a.patient_priority > b.patient_priority ||
           (a.patient_priority == b.patient_priority && a.arrival_time < b.arrival_time);
}
