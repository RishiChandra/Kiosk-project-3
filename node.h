#ifndef NODE_H
#define NODE_H
#include <string>

class node
{
    public:
        // Constructor and destructor prototypes
        node(){};
        node(std::string t, int a, int r){title = t; avail = a; rent = r;} // Overloaded constructor
        ~node();

        // Simple accessor methods
        std::string getTitle() {return title;}
        int getAvail() {return avail;}
        int getRent() {return rent;}
        node*& getParent() {return parent;}
        node*& getLeft() {return left;}
        node*& getRight() {return right;}

        // Simple mutator methods
        void setTitle(std::string t) {title = t;}
        void setAvail(int a) {avail = a;}
        void setRent(int r) {rent = r;}
        void setParent(node* p) {parent = p;}
        void setLeft(node* l) {left = l;}
        void setRight(node* r) {right = r;}

    protected:

    private:
        std::string title;
        int avail = 0;
        int rent = 0;
        node* parent = nullptr;
        node* left = nullptr;
        node* right = nullptr;
};

#endif // NODE_H
