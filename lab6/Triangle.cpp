//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Triangle.h"

Triangle::Triangle(string n, float x1_, float y1_,
 float x2_, float y2_, float x3_, float y3_):Shape(n,(x1_+x2_+x3_)/3,(y1_+y2_+y3_)/3){
x1=x1_;
x2=x2_;
x3=x3_;
y1=y1_;
y2=y2_;
y3=y3_;
 }

Triangle::~Triangle(){
    //Nothing
} 

//Getters
float Triangle::getX1() const{
    return x1;
}
float Triangle::getX2() const{
    return x2;
}
float Triangle::getX3() const{
    return x3;
}
float Triangle::getY1() const{
    return y1;
}
float Triangle::getY2() const{
    return y2;
}
float Triangle::getY3() const{
    return y3;
}

//Getters
void Triangle::setX1(float x1_){
x1=x1_;
}
void Triangle::setX2(float x2_){
x2=x2_;
}
void Triangle::setX3(float x3_){
x3=x3_;
}

void Triangle::setY1(float y1_){
y1=y1_;
}

void Triangle::setY2(float y2_){
y2=y2_;
}

void Triangle::setY3(float y3_){
y3=y3_;
}
//Virtual Functions

void Triangle::draw() const {
    // Set floating point printing to fixed point with 2 decimals
    cout << std::fixed;
    cout << std::setprecision(2);
    
    // Print the information
    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " <<x1<< " " << y1<< " " << x2<< " " <<y2
         << " " << x3<< " " << y3 << " "<< computeArea()
         << endl;
}

float Triangle::computeArea() const {
    
    float area= x1*(y2-y3) + x2*(y3-y1) +x3*(y1-y2);
    area=area/2;
    if(area<0){
        return (area*-1);
    }
    return area;    
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}


