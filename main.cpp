// Name: Rishi Chandra
// NetID: rxc170008
// List of libraries and classes to include
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "node.h"
#include "binarySearchTree.h"
#include <iomanip>
using namespace std;
void getReport(node*, ofstream&); // Method header to display report

int main()
{
    ifstream input("inventory.dat"); // Var to read in input files
    ofstream error("error.log");
    ofstream output("redbox_kiosk.txt");
    binarySearchTree<node>* tree;
    node* root;
    string line; // Var to read input line by line
    int counter = 0; // Counter var to store length of file
    // Validate that file exists
    if (input.good()){
        // Loop through the end of the file
        while(!input.eof()){
            getline(input, line); // Read the next line of the file
            counter++; // Count the number of lines
        }
        // If the last line is just a newline or empty decrease the count of how many lines are in the file
        if (line.length() == 0){
            counter--;
        }
        // Reset the reading of the file
        input.clear();
        input.seekg(0);
        // Loop through the lines of the file
        for (int i = 0; i < counter ; i++){
            // Initialize vars to store the file data
            int parse = 0; // Var to count which term of the line we are at
            string word; // Var to store the terms of the line
            // Vars to store the node data
            string title;
            int avail = 0;
            int rent = 0;
            // Read the next line of the file
            getline(input, line);
            // Initialize var to help parse the line
            stringstream stream(line);
            // Loop through the terms of the line using a comma as a delimiter
            while( getline(stream, word, ',')){
                // Store the data in the appropriate var depending on which term we are at
                if(parse == 0){
                    title = word.substr(1,word.length()-2);
                }
                else if (parse == 1){
                    avail = stoi(word);
                }
                else if (parse == 2){
                    rent = stoi(word);
                }
                parse++;
            }
            // Create the temporary pointer to the node and fill it with the file data
            node* temp = new node(title,avail,rent);
            if (i == 0){
                tree = new binarySearchTree<node>(temp);
                root = temp;
            }
            else {
                tree->insertNode(temp, root, root);
            }
        }

        // Reset the var that reads in the file so it can read in the next input file
        input.clear();
        input.seekg(0);
        input.close();
    }
    // If the inventory file is missing or mis named terminate the program
    else{
        cout << "The inventory file is missing..." << endl;
        return 0;
    }
    counter = 0;
    input.open("transaction.log");
    if (input.good()){
        // Loop through the end of the file
        while(!input.eof()){
            getline(input, line); // Read the next line of the file
            counter++; // Count the number of lines
        }
        // If the last line is just a newline or empty decrease the count of how many lines are in the file
        if (line.length() == 0){
            counter--;
        }
        // Reset the reading of the file
        input.clear();
        input.seekg(0);
        // Loop through all the lines of the file
        for (int i = 0; i < counter; i++){
            // Initialize the many vars to help parse the file
            string order = "";
            string title = "";
            unsigned int quant = 0;
            unsigned int index_space = 0;
            unsigned int first_quote = 0;
            unsigned int last_quote = 0;
            bool order_error = false;
            bool title_error = false;
            bool quant_error = false;

            getline(input, line); // Read the next line of the file
            // Go through each char in the line
            for ( unsigned int j = 0; j < line.length(); j++){
                // If its the first space
                if (line.at(j) == ' ' && index_space == 0){
                    // Parse the order
                    order = line.substr(0,j);
                    index_space = j;
                    // Check if the order is a real order
                    if (order != "add" && order != "remove" && order != "rent" && order != "return"){
                        order_error = true;
                    }
                    else {
                        order_error = false;
                    }
                }
                // If the order dosn't exist there is an error
                if (order == ""){
                    order_error = true;
                }

                // Logic to find the first quote
                if (index_space != 0 && line.at(j) == '\"' && j > index_space && first_quote == 0){
                    first_quote = j;
                }
                // Logic to find the second quote
                if (index_space != 0 && line.at(j) == '\"' && j > first_quote && last_quote == 0){
                    last_quote = j;
                    //cout << last_quote << endl;
                }
                // If there are two quotes found
                if (first_quote != 0 && last_quote != 0 && title == ""){
                    // Parse the title
                    title = line.substr(first_quote + 1, last_quote - first_quote - 1);
                    title_error = false;
                    // First check if the tile actually exists
                    node* temp = new node(title, 0, 0);
                    if (tree->getNode(root, temp) == nullptr && order != "add"){
                        title_error = true;
                    }
                    delete temp;
                }
                // If there is no title there is an error
                else if (title == ""){
                    title_error = true;
                }

                // Get the quant if there should be one
                if ((order == "add" || order == "remove") && quant == 0 && last_quote != 0 && last_quote + 2 <= line.length()){
                    quant = stoi(line.substr((last_quote + 2)));
                    quant_error = false;
                }
                else if ((order == "add" || order == "remove") && quant == 0){
                    quant_error = true;
                }
            }
            // If there was an error report it
            if (order_error || title_error || quant_error){
                error << line << endl;
            }
            // If the line is valid, execute the orders
            else {
                // Create helper nodes
                node* temp =  new node(title, 0, 0);
                node* searched = tree->getNode(root, temp);
                // If ordered to add
                if (order == "add"){
                    // If the node exists
                    if(searched != nullptr){
                        // Add the value
                        searched->setAvail(searched->getAvail() + quant);
                    }
                    // If the node is not part of the tree
                    else {
                        // Create and add the new node
                        searched = new node(title, quant, 0);
                        tree->insertNode(searched, root, root);
                    }
                }
                // If ordered to remove
                else if (order == "remove"){
                    // Subtract the value
                    searched->setAvail(searched->getAvail() - quant);
                    // If the quantity is 0 and should be deleted
                    if (searched->getAvail() == 0 && searched->getRent() == 0){
                        tree->deleteNode(searched);
                        root = tree->getRoot();
                    }
                }
                // If ordered to rent
                else if (order == "rent"){
                    // Update the values
                    searched->setRent(searched->getRent() + 1);
                    searched->setAvail(searched->getAvail() - 1);
                }
                // If ordered to return
                else if (order == "return"){
                    // Update the values
                    searched->setRent(searched->getRent() - 1);
                    searched->setAvail(searched->getAvail() + 1);
                }
                delete temp;
            }
        }
    }
    // Display the report
    getReport(root, output);
    output.close();
    input.close();
    return 0;
}

// Simple recursive Method to output the report
void getReport(node* root, ofstream& out){
    if (root != nullptr){
        getReport(root->getLeft(), out);
        out << setw(30) << root->getTitle() << "\t" << root->getAvail() << "\t" << root->getRent() << endl;
        getReport(root->getRight(), out);
    }
}
