//
//  main.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "shape.h"

// This is the shape array, to be dynamically allocated
shape** shapesArray;

// The number of shapes in the database, to be incremented 
// everytime a shape is successfully created
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
bool checkCreate(string s, string &rName, string &rType, int &rX, int &rY, int &rxSz, int &rySz);
bool checkMove(string s, string &rName, int &rX, int &rY, int &rIndex);
bool checkRotate(string s, string &rName, int &rAngle, int &rIndex);
bool checkD(string s, int &rIndex);
void draw(int index, bool drawAll);
void deleteS(int index, bool deleteAll);
int countArgs(string inputLine);
int findName(string name);

int main() {

    string line;
    string command;

    cout << "> "; // Prompt for input
    getline(cin, line); // Get a line from standard input

    while (!cin.eof()) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so the flags are cleared
        stringstream lineStream(line);

        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here

        if (command == keyWordsList[1]) {

            //Assuming maxShape command is valid, no error checking here
            lineStream >> max_shapes;
            shapesArray = new shape* [max_shapes]; //Dynamically allocating memory
            cout << "New database: max shapes is " << max_shapes << endl;

        } else if (command == keyWordsList[2]) {

            bool checkC;
            string nameCreated, typeCreated;
            int xLoc, yLoc, xSz, ySz;

            //Here, all the values are passed by reference so that if
            //checkCreate returns valid, the program is able to call
            //the constructor to create a new object, this is a recurring
            //style that is used for all commands.

            //line.erase is used here to remove the command from the argument
            //being passed, as the command portion has already been error checked
            checkC = checkCreate(line.erase(0, 6), nameCreated, typeCreated, xLoc, yLoc, xSz, ySz);

            if (checkC) {
                //Calling constructor once the command is valid
                shapesArray[shapeCount] = new shape(nameCreated, typeCreated, xLoc, yLoc, xSz, ySz);
                shapeCount++;
                cout << "Created " << nameCreated << ": " << typeCreated << " " << xLoc << " "
                        << yLoc << " " << xSz << " " << ySz << endl;
            }

        } else if (command == keyWordsList[3]) {

            bool checkM;
            string nameMoved;
            int xLoc = 0, yLoc = 0, index = 0;

            //Similar to error checking from create command
            //Move has 4 characters, erasing 4
            checkM = checkMove(line.erase(0, 4), nameMoved, xLoc, yLoc, index);

            if (checkM) {
                //Calling mutators once command is valid
                shapesArray[index]->setXlocation(xLoc);
                shapesArray[index]->setYlocation(yLoc);
                cout << "Moved " << nameMoved << " to " << xLoc << " " << yLoc << endl;
            }

        } else if (command == keyWordsList[4]) {

            bool checkR;
            string nameRotated;
            int angleRotated = 0, index = 0;

            //Similar to error checking from create command
            checkR = checkRotate(line.erase(0, 6), nameRotated, angleRotated, index);

            if (checkR) {
                //Calling mutators once command is valid
                shapesArray[index]->setRotate(angleRotated);
                cout << "Rotated " << nameRotated << " by " << angleRotated << " degrees" << endl;
            }

        } else if (command == keyWordsList[5]) {

            bool checkDraw;
            int index = 0;

            //Similar to error checking from create command
            //Draw has 4 characters, erasing 4
            checkDraw = checkD(line.erase(0, 4), index);


            if (checkDraw) {

                //index being -1 meaning all keyword was used, refer to function
                //checkDraw for more details

                //Calling utility function once the command is valid
                if (index == -1)
                    draw(-1, true);
                else
                    draw(index, false);
            }

        } else if (command == keyWordsList[6]) {

            bool checkDelete;
            int index = 0;

            //Similar to error checking from create command
            checkDelete = checkD(line.erase(0, 6), index);

            if (checkDelete) {
                if (index == -1)
                    deleteS(-1, true);
                else
                    deleteS(index, false);
            }
        } else
            //invalid command check
            cout << "Error: invalid command" << endl;



        // Once the command has been processed, prompt for the
        // next command
        cout << "> "; // Prompt for input
        getline(cin, line); // Get the command line

    } // End input loop until EOF.

    return 0;
}

//This function checks the create command, it is of recurring theme for every
//command

bool checkCreate(string s, string &rName, string &rType, int &rX, int &rY, int &rxSz, int &rySz) {

    stringstream createStream(s);
    string name, type;
    int x = 0, y = 0, xSz = 0, ySz = 0, args = 0, nameFound = 0;
    bool validT = false;

    //Calling the countArgs function to count the amount of argument the string has
    args = countArgs(s);

    createStream >> name;
    createStream >> type;

    //If there are more than 2 arguments, first one being name, second one being 
    //type, as the command is removed, then check if the integer values are valid
    //First one being X location

    //At any point that there is an error, as the error checking is done in order
    //the function exists and prints the appropriate error message
    if (args > 2) {
        createStream >> x;
        if (createStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    //Similar to x
    if (args > 3) {
        createStream >> y;
        if (createStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    //Similar to x
    if (args > 4) {
        createStream >> xSz;
        if (createStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    //Similar to x
    if (args > 5) {
        createStream >> ySz;
        if (createStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    //Checking for valid name, next error on priority list,
    //Argument has to be greater than 0 for there to exist a name
    if (args > 0) {
        for (int i = 0; i < NUM_KEYWORDS; i++) {
            if (name == keyWordsList[i]) {
                cout << "Error : invalid shape name" << endl;
                return false;
            }
        }

        for (int i = 0; i < NUM_TYPES; i++) {
            if (name == shapeTypesList[i]) {
                cout << "Error : invalid shape name" << endl;
                return false;
            }
        }

        //check for duplicate
        nameFound = findName(name);
        if (nameFound >= 0) {
            cout << "Error : shape " << name << " exists" << endl;
            return false;
        }
    }

    //Checking for type, similar to previous error checking methods
    //Argument has to greater than 1
    if (args > 1) {
        for (int i = 0; i < NUM_TYPES; i++) {
            if (type == shapeTypesList[i]) {
                validT = true;
                break;
            }
        }
        if (!validT) {
            cout << "Error : invalid shape type" << endl;
            return false;
        }
    }

    //Invalid value check
    if (x < 0 || y < 0 || xSz < 0 || ySz < 0) {
        cout << "Error : invalid value" << endl;
        return false;
    }

    //Too many argument check
    if (args > 6) {
        cout << "Error : too many arguments" << endl;
        return false;
    }
    //Too few arguments check
    if (args < 6) {
        cout << "Error : too few arguments" << endl;
        return false;
    }
    //array is full check
    if (shapeCount == max_shapes) {
        cout << "Error : shape array is full" << endl;
        return false;
    }

    //setting return values as they are passed by reference 
    rName = name;
    rType = type;
    rX = x;
    rY = y;
    rxSz = xSz;
    rySz = ySz;

    return true;


}

//Very similar to checkCreate

bool checkMove(string s, string &rName, int &rX, int &rY, int &rIndex) {

    stringstream moveStream(s);
    string name;
    int args, x = 0, y = 0, nameFound = 0;

    args = countArgs(s);
    moveStream >> name;


    if (args > 1) {
        moveStream >> x;
        if (moveStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    if (args > 2) {
        moveStream >> y;
        if (moveStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    if (args > 0) {
        nameFound = findName(name);
        if (nameFound < 0) {
            cout << "Error: shape " << name << " not found" << endl;
            return false;
        } else
            rIndex = nameFound;
    }

    if (x < 0 || y < 0) {
        cout << "Error : invalid value" << endl;
        return false;
    }

    if (args > 3) {
        cout << "Error : too many arguments" << endl;
        return false;
    }

    if (args < 3) {
        cout << "Error : too few arguments" << endl;
        return false;
    }

    rX = x;
    rY = y;
    rName = name;
    return true;

}

//Very similar to checkCreate

bool checkRotate(string s, string &rName, int &rAngle, int &rIndex) {

    stringstream rotateStream(s);
    string name;
    int args, angle = 0, nameFound = 0;

    args = countArgs(s);
    rotateStream >> name;

    if (args > 1) {
        rotateStream >> angle;
        if (rotateStream.fail()) {
            cout << "Error : invalid argument" << endl;
            return false;
        }
    }

    if (args > 0) {

        //calling the findName function to look for the shape 
        nameFound = findName(name);
        if (nameFound < 0) {
            cout << "Error: shape " << name << " not found" << endl;
            return false;
        } else
            rIndex = nameFound;
    }

    if (angle < 0 || angle > 360) {
        cout << "Error : invalid value" << endl;
        return false;
    }

    if (args > 2) {
        cout << "Error : too many arguments" << endl;
        return false;
    }

    if (args < 2) {
        cout << "Error : too few arguments" << endl;
        return false;
    }

    rName = name;
    rAngle = angle;
    return true;

}

//Checks for both draw and delete, similar to checkCreate

bool checkD(string s, int &rIndex) {

    stringstream dStream(s);
    string name;
    int args = 0, nameFound = 0;

    args = countArgs(s);
    dStream >> name;

    if (args > 0) {

        //if "all" is part of the command, return -1 so that when calling the draw
        //or delete functions, all of the shapes will be accessed
        if (name == keyWordsList[0])
            rIndex = -1;
        else {
            nameFound = findName(name); //calling findName 
            if (nameFound < 0 && name != keyWordsList[0]) {
                cout << "Error: shape " << name << " not found" << endl;
                return false;
            } else if (name != keyWordsList[0])
                rIndex = nameFound;
        }
    }


    if (args > 1) {
        cout << "Error : too many arguments" << endl;
        return false;
    }

    if (args < 1) {
        cout << "Error : too few arguments" << endl;
        return false;
    }

    return true;
}

//Function to print the information of shapes 

void draw(int index, bool drawAll) {


    if (drawAll) {
        //If "all" is passed, iterate through the entire array
        cout << "Drew all shapes" << endl;
        for (int i = 0; i < shapeCount; i++) {
            //using accessors
            cout << shapesArray[i]->getName() << ": " << shapesArray[i]->getType()
                    << " " << shapesArray[i]->getXlocation() << " "
                    << shapesArray[i]->getYlocation() << " " << shapesArray[i]->getXsize()
                    << " " << shapesArray[i]->getYsize() << endl;
        }
    } else {
        //using accessors
        cout << "Drew " << shapesArray[index]->getName() << endl << shapesArray[index]->getName()
                << ": " << shapesArray[index]->getType() << " " << shapesArray[index]->getXlocation()
                << " " << shapesArray[index]->getYlocation() << " " << shapesArray[index]->getXsize()
                << " " << shapesArray[index]->getYsize() << endl;

    }

}

//Function to delete shapes
void deleteS(int index, bool deleteAll) {

    //If "all" is passed, iterate through the array
    if (deleteAll) {
        
        cout << "Deleted: all shapes" << endl;
        for (int i = 0; i < shapeCount; i++) {
            delete shapesArray[i];
            shapesArray[i] = NULL; //Setting pointer to NULL
        }

        shapeCount = 0; //Resetting shape count
    } else {

        cout << "Deleted shape " << shapesArray[index]->getName() << endl;

        delete shapesArray[index];
        shapesArray[index] = NULL; //Setting pointer to NULL

        for (int i = index; i < shapeCount; i++) {
            shapesArray[i] = shapesArray[i + 1];
        }

        shapeCount--; //Reducing shape count


    }
}

//Utility function to count the arguments
int countArgs(string inputLine) {
    int count = 0;

    if (inputLine.length() == 0)
        return count;

    stringstream iss(inputLine);
    do {
        string subs;
        iss >> subs;
        count++;
    } while (iss); //stringstream will return false if there is no more arguments

    return count - 1;
}

//Function to find the specific shape, returns -1 if not found
int findName(string name) {
    for (int i = 0; i < shapeCount; i++) {
        if (name == shapesArray[i]->getName()) {
            return i;
        }
    }
    return -1;
}