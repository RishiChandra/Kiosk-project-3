#include "binarySearchTree.h"
#include <iostream>

// Simple destructor to delete the root
template <class T>
binarySearchTree<T>::~binarySearchTree()
{
    if (root != nullptr){
        delete root;
    }
}


