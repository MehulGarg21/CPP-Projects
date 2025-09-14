//
//  Rectangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Rectangle_h
#define Rectangle_h

#include <iostream>
#include <string>
using namespace std;
#include "Shape.h"


// This class implements the rectangle Shape objects.
// ECE244 Student: Write the definition of the class here.
class Rectangle : public Shape {
private:
    float width,height;                

public:
    // Constructor
    Rectangle (string n, float xcen, float ycen,float w,float h);
    
    // Destructor
    virtual ~Rectangle();
    
    // Accessor
    float getWidth() const;   
    float getHeight() const; 
    
    // Mutator
    void setHeight(float x1);     
    void setWidth(float x2); 

    // Utility methods
    virtual void draw() const;     // Draws the triangle; for the assignment it
                                   // prints the information of the Rectangle
    
    virtual float computeArea() const;   // Computes the area of the Rectangle
    
    virtual Shape* clone() const;  // Clones the object
};


#endif /* Rectangle_h */


