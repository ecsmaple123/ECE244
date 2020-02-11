#include "TreeDB.h"
#include "DBentry.h"
#include "TreeNode.h"
#include <iostream>

TreeDB::TreeDB() {
    root = nullptr;
    probesCount = 0;
}

// the destructor, deletes all the entries in the database.

TreeDB::~TreeDB() {
    clear();
}

// inserts the entry pointed to by newEntry into the database. 
// If an entry with the same key as newEntry's exists 
// in the database, it returns false. Otherwise, it returns true.

bool TreeDB::insert(DBentry* newEntry) {

    //Check if entry exists
    if (find(newEntry->getName()))
        return false;

    //Call helper function to insert
    root = insertion(root, newEntry); //Should always be true here
    return true;
}

// searches the database for an entry with a key equal to name.
// If the entry is found, a pointer to it is returned.
// If the entry is not found, the NULL pointer is returned.
// Also sets probesCount

DBentry* TreeDB::find(string name) {
    TreeNode *curNode = root;
    int tempProbe = 1;

    //Loop in tree as long as current node has value
    while (curNode) {
        if (name > curNode->getEntry()->getName()) { //Look in right subtree
            curNode = curNode->getRight();
            tempProbe++; //Increase probe count

        } else if (name < curNode->getEntry()->getName()) {//Look in left subtree
            curNode = curNode->getLeft();
            tempProbe++;

        } else {
            probesCount = tempProbe;
            return curNode->getEntry();
        }
    }
    //Not found
    return nullptr;
}

// deletes the entry with the specified name (key)  from the database.
// If the entry was indeed in the database, it returns true.
// Returns false otherwise.
// See section 6 of the lab handout for the *required* removal method.
// If you do not use that removal method (replace deleted node by
// maximum node in the left subtree when the deleted node has two children)
// you will not match exercise's output.

bool TreeDB::remove(string name) {
    //Nothing to delete
    if(!root)
        return false;
    
    //If root is being deleted, helper function will return 
    //a null pointer, causing this function to return false
    //even though the entry has been deleted successfully
    //Adding a check here specifically for deleting root
    if (root->getEntry()->getName() == name) {
        deleteNode(name, root);
        return true;
    }

    //Call helper for deleting any other node
    if (deleteNode(name, root))
        return true;
    else
        return false; //Return pointer is null
}

// deletes all the entries in the database.

void TreeDB::clear() {
    //Calling helper function
    deleteTree(root);
    root = nullptr;
}

// prints the number of probes stored in probesCount

void TreeDB::printProbes() const {
    cout << probesCount << endl;
}

// computes and prints out the total number of active entries
// in the database (i.e. entries with active==true).

void TreeDB::countActive() const {
    //Calling helper function to count active elements
    cout << activeNumbers(root) << endl;
}

// Prints the entire tree, in ascending order of key/name

ostream& operator<<(ostream& out, const TreeDB& rhs) {
    //Calling helper function to print tree
    rhs.ascendPrintAll(out, rhs.root);
    return out;
}

int TreeDB::activeNumbers(TreeNode* currentNode) const {

    int active = 0;

    //Base case
    if (currentNode == nullptr)
        return 0;

    //Recursively add up counts on left and right subtree
    active += activeNumbers(currentNode->getLeft()) + activeNumbers(currentNode->getRight());

    //Actual counting, execution will get to here at final leaf node, start counting backwards.
    if (currentNode->getEntry()->getActive())
        active++;

    return active;
}

//Recursive helper function for insertion

TreeNode* TreeDB::insertion(TreeNode* currentNode, DBentry* newEntry) {

    //Base case, found location to insert the new node
    if (!currentNode) {
        currentNode = new TreeNode(newEntry);
        return currentNode;
    }

    //Recursive calls
    if (newEntry->getName() < currentNode->getEntry()->getName())
        //Setting the left node incase there is a change caused by insertion
        currentNode->setLeft(insertion(currentNode->getLeft(), newEntry));
    else
        //Similar to previous arguments
        currentNode->setRight(insertion(currentNode->getRight(), newEntry));

    return currentNode;

}
//Recusrsive helper function to print the tree

void TreeDB::ascendPrintAll(ostream& out, TreeNode *currentNode) const {

    //Base case covered when currentNode is of null value
    if (currentNode) {
        //Get to left most value
        ascendPrintAll(out, currentNode->getLeft());
        out << *currentNode->getEntry();

        //Once left most value of current subtree is printed, start printing right values
        ascendPrintAll(out, currentNode->getRight());
        //After current iteration of recursion, go to previous parent of current subtree root and repeat
    }
}

//Recursive helper function to delete an element in the tree

TreeNode* TreeDB::deleteNode(string name, TreeNode *treenode) {
    TreeNode *tmpNode = nullptr;
    if (!treenode) //not found
        return nullptr;
    else if (name < treenode->getEntry()->getName()) //search left branch
        treenode->setLeft(deleteNode(name, treenode->getLeft()));
    else if (name > treenode->getEntry()->getName()) //search right branch
        treenode->setRight(deleteNode(name, treenode->getRight()));

    else { /*found entry*/
        if (treenode->getLeft() && treenode->getRight()) { //entry has two children
            tmpNode = findMax(treenode->getLeft()); //find max node on left branch

            //Copying the value of the left max node into current node
            treenode->getEntry()->setName(tmpNode->getEntry()->getName());
            treenode->getEntry()->setIPaddress(tmpNode->getEntry()->getIPaddress());
            treenode->getEntry()->setActive(tmpNode->getEntry()->getActive());

            //Recursively calling delete to delete left max node as it is replacing original
            //node that was being deleted. Setting the left as it might return a null value if 
            //left max has no children. This case should turn out to be the else case below at some
            //point in execution
            treenode->setLeft(deleteNode(treenode->getEntry()->getName(), treenode->getLeft()));
        } else { //One or less child, base case
            tmpNode = treenode;
            if (!treenode->getLeft())
                treenode = treenode->getRight(); //Setting right child to be current node
            else if (!treenode->getRight())
                treenode = treenode->getLeft(); //Setting left child to be current node

            //These if statements will also cover the case with no children
            //as the first if will set treenode to treenode -> getRight() which is null

            //Special case for root being deleted, updating data member.
            if (tmpNode == root)
                root = treenode;

            delete tmpNode; //Actual deletion

        }
    }
    //Returning the updated root of tree/subtree
    return treenode;
}

//Utility function to find the maximum value of a tree

TreeNode* TreeDB::findMax(TreeNode *curNode) {
    //No more bigger values, base case
    if (!curNode->getRight())
        return curNode;
    //Look in right sub tree
    return findMax(curNode->getRight());
}

//Recursive helper function to delete the entire tree

void TreeDB::deleteTree(TreeNode* currentNode) {

    //Base case, nothing to delete
    if (!currentNode)
        return;
    //Recursively delete left and right subtree
    deleteTree(currentNode->getLeft());
    deleteTree(currentNode->getRight());

    //Deleting, should start with left most then working backwards
    delete currentNode;
}