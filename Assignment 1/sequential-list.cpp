#include <iostream>
#include "sequential-list.h"
using namespace std;
SequentialList::SequentialList(unsigned int cap)
{
    //create vars capacity, size, data
    capacity_ = cap;
    size_ = 0;
    data_ = new DataType[capacity_];
}

//destructor
SequentialList::~SequentialList()
{
    //delete data (pointer)
    //set pointer to null
    delete data_;
    data_ = nullptr;
}

unsigned int SequentialList::size() const
{
    //return list size
    return size_;
}

unsigned int SequentialList::capacity() const
{
    // return capacity
    return capacity_;
}

bool SequentialList::empty() const
{
    //check if it is empty
    // if empty = true
    // if not-empty = false
    if (size_ == 0){
        return true;
    }

    else {
        return false;
    }

}

bool SequentialList::full() const
{
    //list is full when all available spaces are taken up
    // when size = capacity
    // if full = true
    // if not-full = false
    if (size_ == capacity_){
        return true;
    }

    else {
        return false;
    }

}

// Searches for the given value, and returns the index of this value if found.
// Returns the size of the list otherwise
SequentialList::DataType SequentialList::select(unsigned int index) const
{
    //if index is greater than size return data(size -1) *return last element
    //invalid inputs: index > size & index is negative
    if (index >= size_ - 1 || index < 0){
        return data_[size_ - 1];
    }

    else {
        return data_[index];
    }
}

// Searches for the given value, and returns the index of this value if found.
// Returns the size of the list otherwise
unsigned int SequentialList::search(DataType val) const
{
    //for loop (unsigned int i is 0, must be less than capacity, increment)
    //if data_[i] = val
   // return i

   for (int i = 0; i < size_; i++) {
       if (data_[i] == val) {
           return i;
       }
   }

           return size_;


   }


//Prints all elements in the list to the standard output.
void SequentialList::print() const
{
    //print every single value of the list
    // for unsigned int i =0, less than size(), increment
    //cout << data_[i] << endl;

    for (unsigned int i=0; i < size_; i++ ){
        std::cout << data_[i] << std::endl;
    }
}

// Inserts a value at the beginning of the list.
bool SequentialList::insert(DataType val, unsigned int index)
{
    //Inserts a value into the list at a given index.
    //if full()(
    //cout <<'full list' << endl;
    //if index bigger than size
    //return false
    //if index bigger than capacity()
    //return false

    if (index > size_ || index > capacity_ || index < 0 || full()) {
        return false;
    }

    else {

        for (unsigned int i = size_; i > index; i-- ){
            data_[i] = data_[i - 1];
            }

        data_[index] = val;
        size_++;
        return true;
        }

    }


bool SequentialList::insert_front(DataType val)
{
    //Inserts a value at the front of the list.
    return insert(val, 0);
}

bool SequentialList::insert_back(DataType val)
{
    //Inserts a value at the end of the list.
    return insert(val, size_);
}

// Deletes a value from the list at the given index.
bool SequentialList::remove(unsigned int index)
{
    if (index >= size_ || size_ == 0 || index < 0){
        return false;
    }

    else {
        for (unsigned int i = index; i < size_ - 1; i++) {
            data_[i] = data_[i+1];
        }

    size_--;
    return true;
    }
}
// Deletes a value from the beginning of the list.
bool SequentialList::remove_front()
{
    return remove(0);
}

// Deletes a value from the end of the list.
bool SequentialList::remove_back()
{
    return remove(size_-1);
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    // some invalid inserts and deletes
    //check for validity
    if ((size_ == 0 && index != 0) || index > size_){
        return false;
    }
    data_[index] = val;
    return true;
}

