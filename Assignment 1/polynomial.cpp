#include "polynomial.h"
#include <iostream>
using namespace std;
Polynomial::Polynomial(int A[], int size) {
    size_ = size;
    //A[] double linked list
    //Populate values into linked list (insert_back is cleanest + simplest)
    //Invalid inputs (size > index)
    int i = 0;
    while( i != size){
        coefficients.insert_back(A[i]);
        i++;
    }
}
Polynomial* Polynomial::add(Polynomial* rhs) {
    //longer list has to come first, because you can't iterate over longer polynomial
    //initialize size limits
    int size_Upper;


    // if rhs_ size > size(size of polynomial called, in this instance A)
    // if rhs = lhs (then doesnt matter could be either)
    // then rhs_size will be size_M
    if (rhs->size_ >= size_){
        size_Upper = rhs->size_;
    }
    else {
        size_Upper = size_;
    }

    // create pointer to another list which includes the resultants of sum (allocate maxsize)
    int* resultant_values = new int(size_Upper);

    // if still in bound for iteration, select the coeffs of rhs at index i, otherwise 0
    //then same with left
    //result at index i = resultants = left + right

    for (int i = 0; i < size_Upper; i++){
        int left = (size_ -1  >= i) ? coefficients.select(i) : 0;
        int right = (rhs->size_ -1  >= i) ? rhs->coefficients.select(i) : 0;
        resultant_values[i] = left + right;
        }

    Polynomial* resultants = new Polynomial(resultant_values, size_Upper);
    return resultants;
}
Polynomial* Polynomial::sub(Polynomial* rhs) {
    //longer list has to come first, because you can't iterate over longer polynomial
    //initialize size limits
    int size_Upper, size_Lower;

    // if rhs_ size > size(size of polynomial called, in this instance A)
    // if rhs = lhs (then doesnt matter could be either)
    // then rhs_size will be size_M
    if (rhs->size_ >= size_){
        size_Upper = rhs->size_;
    }
    else {
        size_Upper = size_;
    }


    // create pointer to another list which includes the resultants of sum (allocate maxsize)
    int *resultant_values = new int(size_Upper);

    // if still in bound for iteration, select the coeffs of rhs at index i, otherwise 0
    //then same with left
    //result at index i = resultants = left + right

    for (int i = 0; i < size_Upper; i++){
        int left = (size_ -1  >= i) ? coefficients.select(i) : 0;
        int right = (rhs->size_ -1  >= i) ? rhs->coefficients.select(i) : 0;
        resultant_values[i] = left - right;
    }

    Polynomial* resultants = new Polynomial(resultant_values, size_Upper);
    return resultants;
}
Polynomial* Polynomial::mul(Polynomial* rhs) {
//assume polynomials follow proper format (x^2 + x + c)
// to allocate enough space we know that when ie. 3 term polynomials * 3 term polynomial the result is 5 term polynmomial
// therefore, # of terms A[] + # of terms RHS - 1 = resultant # of terms

    const int allocated_size = size_ + rhs->size_ - 1;
    int resultant_array[allocated_size];

//when multiplying polynomials the resultant multiple  can have multiple terms for each exponent
// set coeffs of each power to 0, then add them to simplify , array[i+j]

    for (int i = 0; i > allocated_size; i++) {
        for (int j = 0; j < rhs->coefficients.size(); j++){
            resultant_array[i+j] += coefficients.select(i) * rhs->coefficients.select(j);
        }
    }

    Polynomial *newPolynomial = new Polynomial (resultant_array, allocated_size);
    return newPolynomial;


}
void Polynomial::print() {
    //check all coefficents,m if positive, no change, if negative add brackets
    //do inital output break after one term
    // for the rest same but dont break add the "+"

    int count = size_ - 1;
    for (int i = count; i >= 0; i--){
        if (coefficients.select(i) >= 0){ //positive
            cout << coefficients.select(i) << "x^" << i;
            count--;
            break;
            }

        else if (coefficients.select(i) < 0){ //positive
            cout << "(" << coefficients.select(i) << ")" << "x^" << i;
            count--;
            break;
        }


    }

    //non first terms
    for (int j = count; j>=0; j--){
        if (coefficients.select(count) > 0){
            cout << " + " << coefficients.select(count) << "x^" << count;
        }

        else if (coefficients.select(count) < 0){
            cout << " + " << "(" << coefficients.select(count) << ")" <<  "x^" << count;
        }
    }
    std::cout << std::endl;
}