#include "node.h"

// Simple destructor that deletes children if they exist
node::~node()
{
    if (left != nullptr){
        delete left;
    }
    if (right != nullptr){
        delete right;
    }
}
