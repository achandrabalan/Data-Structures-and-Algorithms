/****************************************************
You can use this file to test if your code is working
properly by designing your own test case and test code.
****************************************************/

#include <iostream>
#include <string>
#include "test.h"

using namespace std;

string get_status_str(bool status)
{
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main()
{
    int grade = 0;
    SequentialListTest seq_test;
    // DoublyLinkedListTest linked_test;
    // PolynomialTest poly_test;

    string seq_test_descriptions[10] = {
            "Test1: New empty list is valid",
            "Test2: insert_front() and insert_back() on zero-element list",
            "Test3: select() and search() work properly",
            "Test4: remove_front() and remove_back() on one-element list",
            "Test5: Inserting too many elements should fail"};

    bool seq_test_results[10];
    seq_test_results[0] = seq_test.test1();
    seq_test_results[1] = seq_test.test2();
    seq_test_results[2] = seq_test.test3();
    seq_test_results[3] = seq_test.test4();
    seq_test_results[4] = seq_test.test5();

    cout << "SEQUENTIAL LIST TESTING RESULTS \n";
    cout << "******************************* \n";
    for (int i = 0; i < 5; ++i)
    {
        cout << seq_test_descriptions[i] << endl
             << get_status_str(seq_test_results[i]) << endl;
    }
}

