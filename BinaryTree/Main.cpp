#include <iostream>
#include <sstream>
#include <string>
#include "DBentry.h"
#include "TreeDB.h"
#include "TreeNode.h"
using namespace std;

int main() {

    string line;
    string command;
    TreeDB tree;

    cout << "> ";
    getline(cin, line);

    while (!cin.eof()) {

        string name, status;
        unsigned int IP;
        bool activeStatus;

        stringstream lineStream(line);
        lineStream >> command;

        if (command == "insert") {
            //Setting data members
            lineStream >> name >> IP >> status;
            activeStatus = status == "active" ? true : false;

            //Entry to be inserted
            DBentry* inserted = new DBentry(name, IP, activeStatus);

            if (!tree.insert(inserted)) { //Insert function
                cout << "Error: entry already exists" << endl;
                delete inserted; //Free the memory
            } else
                cout << "Success" << endl;

        } else if (command == "find") {

            lineStream >> name;
            if (!tree.find(name)) //Find function 
                cout << "Error: entry does not exist" << endl;
            else
                cout << *tree.find(name); //Overloaded print for DBentry

        } else if (command == "remove") {

            lineStream >> name;
            if (tree.remove(name)) //Remove function
                cout << "Success" << endl;
            else
                cout << "Error: entry does not exist" << endl;

        }
        else if (command == "printall")
            cout << tree; //Overloaded print for TreeDB


        else if (command == "printprobes") {
            lineStream >> name;

            if (!tree.find(name)) //Find sets he probe count
                cout << "Error: entry does not exist" << endl;
            else
                tree.printProbes(); //printProbes function

        } else if (command == "removeall") {
            tree.clear(); //Clear deletes whole tree
            cout << "Success" << endl;
        } else if (command == "countactive")
            tree.countActive(); //Count the active elements

        else if (command == "updatestatus") {
            lineStream >> name >> status;
            activeStatus = status == "active" ? true : false;

            DBentry* temp = tree.find(name); //Find function
            if (!temp)
                cout << "Error: entry does not exist" << endl;
            else {
                temp->setActive(activeStatus);
                cout << "Success" << endl;
            }

        }

        cout << "> ";
        getline(cin, line);
    }

    return 0;
}