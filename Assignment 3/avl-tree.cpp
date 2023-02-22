#include "avl-tree.h"
#include <iostream>
using namespace std;

int AVLTree::getNodeDepth(BinarySearchTree::Node *n) const {
    if (n == 0){
        return -1;
    }
    else {
        return ::max(getNodeDepth(n->left), getNodeDepth(n->right)) + 1;
    }
}

int AVLTree::Weight(BinarySearchTree::Node *node) {

    int right = getNodeDepth(node->right);
    int left = getNodeDepth(node->left);

    return left - right;
}

bool AVLTree::insert(DataType val)
{
    if(BinarySearchTree::insert(val) == 0){
        return false;
    }
    else {
        balance(getRootNode());
        return true;
    }
}

bool AVLTree::remove(DataType val)
{
    if(BinarySearchTree::remove(val) == 0) {
        return false;
    }
    else {
        balance(getRootNode());
        return true;
    }
}

void AVLTree::LHS(Node* node) {

    Node* temp = new Node(node->val);

    //Temp allocation
    temp->left = node->left;
    temp->right = node->right->left;


    //Node allocation
    node->left = temp;
    node->val = node->right->val;
    node->right = node->right->right;

}

void AVLTree::RHS(Node* node) {

    Node* temp = new Node(node->val);

    //Temp allocation
    temp->left = node->left->right;
    temp->right = node->right;

    //Node allocation
    node->right = temp;
    node->val = node->left->val;
    node->left = node->left->left;
}

void AVLTree::balance(BinarySearchTree::Node* node) {
    if(node == 0) {
        return;
    }

    balance(node->left);
    balance(node->right);
    int balance_factor = Weight(node);

    //determine RHS or LHS
    if(balance_factor > 1 && Weight(node->left) < 0){
        LHS(node->left);
        return RHS(node);
    }
    else if (balance_factor > 1){
        return RHS(node);
    }


    else if (balance_factor < -1 && Weight(node->right) > 0){
        RHS(node->right);
        return LHS(node);
    }
    else if(balance_factor < -1){
        return LHS(node);
    }

    else {
        return;
    }
}



