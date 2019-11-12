#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
#include <string>
#include "node.h"
// Templated binary search tree
template <class T>
class binarySearchTree
{
    public:
        // Constructors and destructors
        binarySearchTree(){};
        binarySearchTree(T* r) {root = r;} // Overloaded constructor
        ~binarySearchTree();

        // Mutators and Accessors
        void insertNode(T*,T*&,T*);
        T*& getNode(T*&, T*);
        T* getRoot() {return root;}
        void deleteNode(T*);

    protected:

    private:
        T* root = nullptr; // Root of binary tree
};

// Method to delete a node
template <class T>
void binarySearchTree<T>::deleteNode(T* n){
    // If the node has no children
    if (n->getRight() == nullptr && n->getLeft() == nullptr){
        // If the node is not the root
        if (n->getParent() != nullptr){
            // If the node is on the left
            if (n->getTitle() < n->getParent()->getTitle()){
                n->getParent()->setLeft(nullptr); // Tell the parent its left child is deleted
            }
            else{
                n->getParent()->setRight(nullptr); // Tell the parent its right child is deleted
            }
        }
        else {
            root = nullptr; // Delete the root
        }
        delete n; // Delete the node
    }

    // If the node only has one child
    else if ((n->getRight() != nullptr) ^ (n->getLeft() != nullptr)){
        // If the node is not BATMAN (has parents and not the root)
        if (n->getParent() != nullptr){
            // If the node is on the left of the parent
            if (n->getTitle() < n->getParent()->getTitle()){
                // If the node has the child on the left
                if (n->getLeft() != nullptr){
                    n->getParent()->setLeft(n->getLeft()); // Update the parent
                }
                // If the node has the child on the right
                else{
                    n->getParent()->setLeft(n->getRight()); // Update the parent
                }
            }
            // If the node is on the left of the parent
            else{
                // If the node has the child on the left
                if (n->getLeft() != nullptr){
                    n->getParent()->setRight(n->getLeft()); // Update the parent
                }
                // If the node has the child on the right
                else{
                    n->getParent()->setRight(n->getRight()); // Update the parent
                }
            }
        }
        // If the node is the root
        else {
            // If the child is on the left
           if (n->getLeft() != nullptr){
                root = n->getLeft(); // Make the child the root
            }
            // If the child is on the right
            else{
                root = n->getRight(); // Make the child the root
            }
        }

        n->setRight(nullptr);
        n->setLeft(nullptr);
        delete n;
    }
    // The node has two children
    else{
        // Create helper nodes
        node* leftmost = n->getRight()->getLeft();
        node* parent = n->getRight();
        // Find the left most node on the right subtree
        while (leftmost != nullptr){
            parent = leftmost;
            leftmost = leftmost->getLeft();
        }
        // Store the data from the left most
        std::string title = parent->getTitle();
        int rent = parent->getRent();
        int avail = parent->getAvail();
        // Delete the leftmost node
        deleteNode(parent);
        // Set the data of the leftmost node to the node
        n->setTitle(title);
        n->setRent(rent);
        n->setAvail(avail);
    }
}

// Recursive method to search for a node
template <class T>
T*& binarySearchTree<T>::getNode(T*& curr, T* n){
    // Base case if node is never found
    if(curr == nullptr){
        return curr;
    }
    else{
        // If the node is found
        if (curr->getTitle() == n->getTitle()){
            return curr;
        }
        // If the node is less than the current node search the left node
        else if (curr->getTitle() > n->getTitle()){
            return getNode(curr->getLeft(), n);
        }
        // If the node is greater than the current node search the right node
        else {
            return getNode(curr->getRight(), n);
        }
    }
}

// Recursive method to insert a node
template <class T>
void binarySearchTree<T>::insertNode(T* add,T*& curr, T* prev){
    // Base Case if at the end of the tree
    if (curr == nullptr){
        // Add the node
        curr = add;
        curr->setParent(prev);
    }
    else{
        // If the node is less than the current node then go down that tree
        // Otherwise go down the right tree
        if (add->getTitle() < curr->getTitle()){
            insertNode(add, curr->getLeft(), curr);
        }
        else {
            insertNode(add, curr->getRight(), curr);
        }
    }
}


#endif // BINARYSEARCHTREE_H
