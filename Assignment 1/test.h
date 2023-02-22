#ifndef A1_TESTS_HPP
#define A1_TESTS_HPP

#include "doubly-linked-list.h"
#include "sequential-list.h"
#include "polynomial.h"

#define ASSERT_TRUE(T) \
    if (!(T))          \
        return false;
#define ASSERT_FALSE(T) \
    if ((T))            \
        return false;

class SequentialListTest
{
public:
    // New empty list is valid
    bool test1()
    {
        unsigned int capacity = 5;
        SequentialList list(capacity);

        ASSERT_TRUE(list.size() == 0)
        ASSERT_TRUE(list.capacity() == capacity)
        ASSERT_TRUE(list.empty() == true)
        ASSERT_TRUE(list.full() == false)
        return true;
    }

    // insert_front() and insert_back() on zero-element list
    bool test2()
    {
        unsigned int capacity = 5;
        SequentialList list1(capacity);
        SequentialList list2(capacity);
        ASSERT_TRUE(list1.insert_front(100))
        ASSERT_TRUE(list2.insert_back(100))

        ASSERT_TRUE(list1.size() == list2.size() && list1.size() == 1)
        ASSERT_TRUE(list1.data_ != NULL)
        ASSERT_TRUE(list2.data_ != NULL)
        ASSERT_TRUE(list1.select(0) == list2.select(0) && list1.select(0) == 100)
        return true;
    }

    // select() and search() work properly
    bool test3()
    {
        unsigned int capacity = 5;
        SequentialList list(capacity);
        for (unsigned int i = 0; i < capacity; i++)
        {
            ASSERT_TRUE(list.insert_back(i * 100))
        }

        unsigned int idx = 3;
        ASSERT_TRUE(list.search(list.select(idx)) == idx)
        ASSERT_TRUE(list.select(capacity + 1) == list.select(capacity))
        ASSERT_TRUE(list.search(1000) == list.size())

        for (unsigned int i = 0; i < capacity; i++)
        {
            ASSERT_TRUE(list.select(i) == i * 100 && list.data_[i] == i * 100)
        }
        return true;
    }

    // remove_front() and remove_back() on one-element list
    bool test4()
    {
        unsigned int capacity = 5;
        SequentialList list1(capacity);
        SequentialList list2(capacity);
        ASSERT_TRUE(list1.insert_front(100))
        ASSERT_TRUE(list2.insert_front(100))
        ASSERT_TRUE(list1.remove_front())
        ASSERT_TRUE(list2.remove_back())

        ASSERT_TRUE(list1.size_ == list2.size_ && list1.size_ == 0)
        ASSERT_TRUE(list1.empty() == true && list2.empty() == true)
        return true;
    }

    // Inserting too many elements should fail
    bool test5()
    {
        unsigned int capacity = 5;
        SequentialList list(capacity);
        // Fill up the list.
        for (unsigned int i = 0; i < capacity; i++)
        {
            ASSERT_TRUE(list.insert_back(i))
        }

        // Try overfilling (they should all return false with no modifications).
        int val_not_inserted = 100;
        ASSERT_FALSE(list.insert_back(val_not_inserted))
        ASSERT_FALSE(list.insert_front(val_not_inserted))
        ASSERT_FALSE(list.insert(val_not_inserted, 3))

        // Check size is correct.
        ASSERT_TRUE(list.full() == true && list.empty() == false)
        ASSERT_TRUE(list.size_ == list.capacity_ && list.capacity_ == capacity)

        return true;
    }
};

#endif
