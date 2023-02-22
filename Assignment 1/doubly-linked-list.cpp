#include <iostream>
#include "doubly-linked-list.h"
using namespace std;

//seg faults check for leaks
DoublyLinkedList::Node::Node(DataType data)
{
    //declare vars, value, next prev
    value = data;
    next = nullptr; //essentially Node* next since constructor - Pointer to next node in DLL
    prev = nullptr; // Pointer to previous node in DLL

}

DoublyLinkedList::DoublyLinkedList()
{
    //Create new empty double linked list -> constructor
    //declare vars head, tail and initialize size
    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0; //must increment after addition / subtraction

}

DoublyLinkedList::~DoublyLinkedList()
{
    //Delete new empty double linked list -> destructor
Node *current = head_;
Node*temp;
while (current!=nullptr) {
    temp = current->next;
    delete current;
    current = temp;
}
}

unsigned int DoublyLinkedList::size() const
{
    //return size val
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    //return capacity
    //static const unsigned int CAPACITY = 65536;
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    // Returns true if the list is empty, false otherwise.
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

bool DoublyLinkedList::full() const
{
    // Returns true if the list is at capacity, false otherwise.
    //list is full when all available spaces are taken up
    // when size = capacity
    // if full = true
    // if not-full = false
    if (size_ == CAPACITY){
        return true;
    }

    else {
        return false;
    }
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    // Returns the value at the given index in the list. If index is invalid,
    // return the value of the last element.
    //if index is greater than size return data(size -1) *return last element
    //invalid inputs: index > size & index is negative
    if (index > size_  || index < 0 || size_ == 0 || (empty() && index != 0)){
        return tail_ -> value;
    }
        Node* N_val = getNode(index);
        return N_val -> value;


}

unsigned int DoublyLinkedList::search(DataType value) const
{
    // Searches for the given value, and returns the index of this value if found.
    // returns the size of the list otherwise.

    Node* N_current = head_;

    for (int i = 0; i < size_; i++){
        if (N_current -> value == value) {
            return i;
        }
            N_current = N_current -> next;

    }

    return size_; //fail case
}

void DoublyLinkedList::print() const
{
    //invalids
    if (empty()){
        std::cout << "not valid" << std::endl;
    }

    else {
        // Prints all elements in the list to the standard output.
        Node* N_current = head_->next;
        for (int i = 0; i < size_; i++) {
            std::cout << N_current -> value << std::endl; //output
            N_current = N_current -> next; //increment
        }
    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    //optional
    Node *current = head_;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    //invalids
    //size != 0 when index > 0
    if ((empty() && index != 0) || index > size_){
        return false;
    }


    // Inserts a value into the list at a given index.
    Node* N_current = head_;
    Node *newNode = new Node(value);

    for (int i=0; i<size_; i++ ){
        if (i == index) {
            Node* previous = N_current->prev;
            N_current->prev = newNode;
            previous->next = newNode;

            newNode->next = N_current;
            newNode->prev = previous;
            size_++;
            return true;
        }
        N_current = N_current -> next;
    }

//    Node* newNode = new Node(value);
//    newNode -> prev = N_current;
//    newNode -> next = N_current;
//    N_current -> prev = newNode;
//    size_++;
//    return true;

}

bool DoublyLinkedList::insert_front(DataType value)
{
    //invalid input check
    if (full()){
        return false;
    }

    //insert val at front
    //in DLL inserting at front means new node becomes head_
  Node* newNode = new Node(value); //create node
  //if nothing in DLL then just insert

  if (size_ == 0){
      head_ = newNode;
      tail_ = newNode;
  }

  else {
      //start at head and go opposite
      head_ -> prev = newNode;
      newNode -> next = head_;
      head_ = newNode;
  }

  size_++;
  return true;

}

bool DoublyLinkedList::insert_back(DataType value)
{
    if (full()){
        return false;
    }
    //invalid input check

    //insert val at back
    //in DLL inserting at back means new node becomes tail_
    Node* newNode = new Node(value); //create node
    //if nothing in DLL then just insert

    if (size_ == 0){
        head_ = newNode;
        tail_ = newNode;
    }

    else {
        //start at head and go opposite
        tail_ -> next = newNode;
        newNode -> prev = tail_;
        tail_ = newNode;
    }

    size_++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    // Deletes a value from the list at the given index.
    // invalid input check
    //invalid when index = size or index is not positive
    if (index<0 || index> size_){
        return false;
    }

    //if index = 0, equivalent to inserting first/any
    //if index = size -1 than equivalent to inserting last
    if (index == 0) {
        return remove_front();
    }

    if (index == size_ - 1){
        return remove_back();
    }

    Node* N_current = head_;

    for (unsigned int i=0; i<=index; i++ ){
        if ( i == index){
            return N_current;
        }

        N_current = N_current -> next;
    }

    N_current -> next -> prev = N_current -> prev;
    N_current -> prev -> next = N_current -> next;

    size_--; //decrement size
    return true;
}

bool DoublyLinkedList::remove_front()
{
    //invalid values
    if (empty()){
        return false;
    }
    //cannot delete from empty list
    if (size_ == 0){
        return false;
    }

    head_ = head_ -> next;
    if (head_){
        head_ -> prev = NULL;
    }

    else{
        tail_ = NULL;
    }

    size_--; //decrement size
    return true;
}

bool DoublyLinkedList::remove_back()
{

    //deletes last val
    //invalid values
    //cannot delete from empty list
    if (empty()){
        return false;
    }
    if (size_ == 1) {
        return remove_front();
    }
    else {
        Node* helper = tail_;
        tail_ = tail_ -> prev;
        tail_->next = nullptr;
    }
//    if (tail_){
//        tail_ -> prev = NULL;
//    }


    size_--; //decrement size
    return true;
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{

    //invalid inputs
    //cant have index without size, index cant be greater than size
    if ((empty() && index != 0 )|| index > size_){
        return false;
    }


        Node* N_current = head_;

        for (int i=0; i < index; i++ ){
            if ( i == index){
                N_current->value = value;
                return true;
            }

            N_current = N_current -> next;
        }
        N_current -> value = value;


    return true;
    //size is same
}

