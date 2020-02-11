//
//  shape.cpp skeleton
//  lab3
//
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018 Tarek Abdelrahman. All rights reserved.
//

#include <iostream>
#include <string>
using namespace std;

#include "shape.h"

// ECE244 Student: 
// Write the implementation (and only the implementation) of the shape
// class below

//Accessors
//Returns the type of shape
string shape::getType(){
    return type;
}
//Returns the nsmr of shape
string shape::getName(){
    return name;
}
//Returns the X location of shape
int shape::getXlocation(){
    return x_location;
}
//Returns the Y location of shape
int shape::getYlocation(){
    return y_location;
}
//Returns the X size of shape
int shape::getXsize(){
    return x_size;
}
//Returns the Y size of shape
int shape::getYsize(){
    return y_size;
}

//Mutators
//Set the type of shape
void shape::setType(string t){
    type = t;
}
//Set the name of shape
void shape::setName(string n){
    name = n;
}
//Set the X location of shape
void shape::setXlocation(int x_loc){
    x_location = x_loc;
}
//Set the Y location of shape
void shape::setYlocation(int y_loc){
    y_location = y_loc;
}
//Set the X size of shape
void shape::setXsize(int x_sz){
    x_size = x_sz;
}
//Set the Y size of shape
void shape::setYsize(int y_sz){
    y_size = y_sz;
}
//Set the rotation of shape
void shape::setRotate(int angle){
    rotation = angle;
}

//Utility 
//"Draw" the shape
void shape::draw(){
    cout << name << ": " << type << " " << x_location
         << y_location << x_size << y_size;
}
//Constructor
//Initializes an object
shape::shape(string n, string t, int x_loc, int y_loc, int x_sz, int y_sz) {
	name = n;
	type = t;
	x_location = x_loc;
	y_location = y_loc;
	x_size = x_sz;
	y_size = y_sz;
}