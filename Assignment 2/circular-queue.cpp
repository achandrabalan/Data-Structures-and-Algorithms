#include "circular-queue.h"
#include "iostream"

const CircularQueue::QueueItem CircularQueue::EMPTY_QUEUE = 9999;
using namespace std;

CircularQueue::CircularQueue() {
//head_ : index of the first element in circ queue
head_ = 0;
//tail_ : index of the element after the last item in circ queue
tail_ = 0;
//capacity_ : max # items in circ queue
capacity_ = 16;
//size_ : current # of items in circ queue
size_ = 0;

//items_ : array of queue items
items_ = new QueueItem [capacity_];

}

CircularQueue::CircularQueue(unsigned int capacity) {
head_ = 0;
tail_ = 0;

capacity_ = capacity;
size_ = 0;

items_ = new QueueItem[capacity];
}

CircularQueue::~CircularQueue() {
    delete [] items_;
}

bool CircularQueue::empty() const {
// Returns true if the queue is empty and false otherwise.
    if (size_ == 0){
        return true;
    }

    else{
        return false;
    }
}

bool CircularQueue::full() const {
// Returns true if the queue is full and false otherwise.
    if (size_ == capacity_){
        return true;
    }

    else{
        return false;
    }
}

int CircularQueue::size() const {
// Returns the number of items in the queue.
    return size_;
}

bool CircularQueue::enqueue(QueueItem value) {
// MUTATORS
    // Takes as an argument a QueueItem value. If the queue is not at capacity,
    // it inserts the value at the rear of the queue after the last item, and
    // returns true. If the insertion fails due to lack of space, it
    // returns false.

    //check if Queue is full
    if(size_ == capacity_){
        return false; //lack of space
    }
    else{
        items_[tail_] = value;


        //special case, if tail is last element, loop around
        tail_++;
        if (tail_ == capacity_) {
            tail_ = 0;
        }
        size_++;
        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue() {
//check if there is anything to dequeue
    if(size_ == 0){
        return EMPTY_QUEUE;
    }
    else{ // dequeue from head_

        //QueueItem defines kind of data : access via "CircularQueue::QueueItem"
        CircularQueue::QueueItem temp = items_[head_];
        head_++;
        if (head_ == capacity_){
            head_ = 0;
        }

        size_--;
        return temp;

    }
}

CircularQueue::QueueItem CircularQueue::peek() const {
    if (size_ == 0){
        return EMPTY_QUEUE;
    }

    else{
        return items_[head_]; //first item
    }
}

void CircularQueue::print() const {
    for (int i = 0; i < size_; i++){
        cout << items_[i] << ", " ;

    }
    cout << endl;
    return;
}

