#include "dynamic-stack.h"
#include <iostream>
const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -9999;
using namespace std;
DynamicStack::DynamicStack() {
    // *note -- DynamicStack uses 16 as the initial capacity

    // capacity_ -- Maximum number of elements allowed in the current stack
    capacity_ = 16;

    // size_     -- Current number of elements in the stack
    size_ = 0;

    // init_capacity -- Initial capacity of the array <- used by pop()
    init_capacity_ = 100;


    //StackItem
    items_ = new StackItem[init_capacity_]; //dynamically allocate w/ new operator
                                            //item created with determined item type ("StackItem") @ index capacity
}

DynamicStack::DynamicStack(unsigned int capacity){
//parametric constructor: allocates memory for given capacity
    capacity_ = capacity;
    size_ = 0;
    init_capacity_ = capacity;
    items_ = new StackItem[init_capacity_];

}

DynamicStack::~DynamicStack() {
    delete [] items_;
}

bool DynamicStack::empty() const {
    //Returns true if stack is empty, false otherwise
    if (size_ == 0){
        return true;
    }

    return false;
}

int DynamicStack::size() const {
    //Returns number of items in the stack
    //size();
    return size_;
};

void DynamicStack::push(StackItem value) {

    //Stack is full, capacity is doubled then pushed onto stack
    if (size_ == capacity_) {
        capacity_ = capacity_ * 2;

        StackItem *temp = new StackItem[capacity_];

        //resize
        for (int i = 0; i < size_; i++) {
            temp[i] = items_[i];
        }
        items_ = temp;
    }

    // Stack is not full, the value is pushed onto the stack.
    items_[size_] = value;
    size_++;

}

DynamicStack::StackItem DynamicStack::pop() {
    // Removes and returns the top item from the stack as long as the stack is
    // not empty.

    // If the number of items remaining in the stack after popping
    // is less than or equal to one quarter of the capacity of the array, then
    // the array is halved.

    // However, if the new halved capacity is less than
    // the initial capacity, then no resizing takes place.

    // Finally, If the stack
    // is empty before the pop, the EMPTY STACK constant is returned.

    if (size_ == 0) {
        return EMPTY_STACK;
    }

    size_--;

    if (size_ <= capacity_/4){
        if ( init_capacity_ <= capacity_/2) {

            capacity_ = capacity_/2;
            StackItem* temp = new StackItem[capacity_];

            for (int i = 0; i < size_; i++) {
            temp[i] = items_[i];
            }

            items_ = temp;

}

    }



    return items_[size_];

}

DynamicStack::StackItem DynamicStack::peek() const {
    if (size_ == 0){
        return EMPTY_STACK;
    }

    //return top value without removal
    return items_[size_ - 1];
}

void DynamicStack::print() const {

    // return empty stack constant
    if (size_ == 0){
        cout << EMPTY_STACK << endl;
        return;
    }

    int i = 0;
    while ( i <= size_){
        cout << items_[i]  << endl;
    }

    return;
}
//end