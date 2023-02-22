#include "binary-search-tree.h"
#include "iostream"
using namespace std;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;

    //avlBalance can be updated w/ implementation of updateNodeBalance
    avlBalance = 0;
}

void BinarySearchTree::updateNodeBalance(Node *n) {
    //implementation
    n->avlBalance = getNodeDepth(n);
}


int BinarySearchTree::getNodeDepth(Node* n) const
{
    // Optional function that recursively gets the maximum depth for a given node.


    // If tree is empty then return -1
    if (n == nullptr) {
        return -1;
    }
    // Else

    else {
        // Get the max depth of left subtree recursively; call maxDepth( tree->left-subtree)
        int maxDepthLeft = getNodeDepth(n->left);

        // Get the max depth of right subtree recursively; call maxDepth( tree->right-subtree)
        int maxDepthRight = getNodeDepth(n->right);

        // Get the max of max depths of left and right subtrees and add 1 to it for the current node.
        //max_depth = max(max dept of left subtree,max depth of right subtree)
        //+ 1
        // (d) Return max_depth

        if (maxDepthLeft > maxDepthRight) {
            maxDepthLeft = maxDepthLeft + 1;
            return maxDepthLeft;
        }

        else {
            maxDepthRight = maxDepthRight + 1;
            return maxDepthRight;
        }
    }



}

BinarySearchTree::BinarySearchTree()
{
// Default constructor to initialize the root.
    root_ = nullptr;
    size_ =  0;
}

void FreeSpace(BinarySearchTree:: Node* root){
    if(root != nullptr){
        FreeSpace(root->left);
        FreeSpace(root->right);

        delete root;
    }
}

//// split **************************************************************************************

BinarySearchTree::~BinarySearchTree()
{
// Destructor of the class BinarySearchTree. It deallocates the memory space allocated for the binary search tree.
//  Needs function to destroy objects (recursive) //FreeSpace
    //delete root_;
    //root_ = nullptr;

    FreeSpace(root_);
}

//// split **************************************************************************************

unsigned int BinarySearchTree::size() const
{
    return size_;
}

//// split **************************************************************************************

BinarySearchTree::DataType BinarySearchTree::max() const
{
// Returns the maximum value of a node in the tree. You can assume that
// this function will never be called on an empty tree.
    //Larger values will always be put in the right child node

    Node *temp = root_; //pointer to root

    while (temp) {
        if(temp->right == nullptr){ //if the next node is empty
            return temp->val; //then, this is the last child so return
        }

        temp = temp->right; //if not last node, continue traversing
    }
}

//// split **************************************************************************************

BinarySearchTree::DataType BinarySearchTree::min() const
{
// Returns the minimum value of a node in the tree. You can assume that
// this function will never be called on an empty tree.
    //Smaller values will always be put in the left child node

    Node *temp = root_; //pointer to root

    while (temp) {
        if(temp->left == nullptr){ //if the next node is empty
            return temp->val; //then, this is the last child so return
        }

        temp = temp->left; //if not last node, continue traversing
    }
}

//// split **************************************************************************************

unsigned int BinarySearchTree::depth() const
{
    return getNodeDepth(root_);
}

//// split **************************************************************************************

void BinarySearchTree::print() const
{
    //Not used for grading purposes
}

//// split **************************************************************************************

bool BinarySearchTree::exists(DataType val) const
{
// Returns true if a node with the value val exists in the tree; otherwise,
// it returns false.

//Must look through entire tree to find value: val

Node *temp = root_;

while (temp){
    if (temp->val == val){
        return true;
    }
    else if (temp-> val > val) {
        temp = temp-> left;
    }

    else {
        temp = temp->right;
    }

}

    return false;
}


BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    // Returns a pointer to the root node
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    // Returns the root node pointer address
    return &root_;

}

//// split **************************************************************************************

bool BinarySearchTree::insert(DataType val)
{
    // Inserts the value val into the tree. Returns false if val already exists in
    // the tree, and true otherwise.
    Node * insert = new Node(val); //create node w/ designated val

    // empty tree check
    if (root_ == nullptr) {
        root_ = insert;
        size_++;
        return true;
    }

    Node *temp = root_;    // create pointer to root node
    Node *parentNode = temp;   // Create a pointer to parent node
    while (temp) {
        if (temp->val == val) {
            return false; //already exists return false
        }


        else if (val < temp->val) {
            parentNode = temp;
            temp = temp->left; //val smaller, so move toward smaller #s (left side)
        }

        else {
            parentNode = temp;
            temp = temp->right; //val larger, so move toward larger #s (right side)
        }
    }

    if (val < parentNode->val){
        parentNode->left = insert;
    }
    else{
        parentNode->right = insert;
    }
    size_++;
    return true;
}

//// split **************************************************************************************

bool BinarySearchTree::remove(DataType val)
{
    // Removes the node with the value val from the tree. Returns true if successful,
    // and false otherwise.

    if (!root_) {
        return false;

    } else if (!exists(val)) {
        return false;

    } else {
        Node *temp = root_;
        Node *parentNode = root_;
        bool end = false;
        bool is_left = false;

        while (temp) {
            if (temp->val == val) {
                end = true;
                break;

            }

            else if (val < temp->val){
                //val is smaller than current val, move left to find match
                parentNode = temp;
                temp = temp->left; //move left
                is_left = true; //direction activated
            }

            else {
                parentNode = temp;
                temp = temp->right; //val is larger than current val, move right to find match
                is_left = false; //deactivated
            }
        }


//// Split *************************************************************************************************************************************


        if(temp->left && temp->right){
            Node * prev = temp->left; //Traverse

            while(prev->right != nullptr){ //base case
                prev = prev->right;
            }

            int previous = prev->val;
            remove(previous); // recursive call
            temp->val = previous;
            return true;

        }

        if(temp->right && !temp->left){
            if (temp == root_){
                root_ = temp->right;

            } if(is_left){
                parentNode->left = temp->right;
            }

            else {
                parentNode->left = temp->right;
            }

            size_--;
            delete temp;
            return true;

        }

        else if(temp->left && !temp->right){

            if(is_left) {
                parentNode->left = temp->left;
            }
            else {
                parentNode->right = temp->left;
            }
            delete temp;
            return true;
    }

        else{
            if(temp == root_) {
                delete root_;
                root_ = nullptr;
                size_ = size_ - 1;
                return true;
            }
            if(is_left){
                parentNode->left = nullptr;
            }

            else {
                parentNode->right = nullptr;
            }

            size_--;
            delete temp;
            return true;
        }

    }
}