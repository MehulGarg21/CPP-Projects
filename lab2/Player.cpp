//
//  Player.cpp
//  Lab 2 Pong Game
//
//  Created by Mehul Garg, Date

#include <iostream>
#include "Player.h" 
#include "Globals.h"
#include "Screen.h"
#include "io.h"
using namespace std ;

Player::Player(){
x=0;
y=0;
height=0;
width=1;

}
//Seeked help from PrivatePiazza post to form constructors with same func prototype and variables to find out
Player::Player(double x_coordinate, double y_coordinate, int height_coordinate){
 x=x_coordinate;
 y=y_coordinate;
 height= height_coordinate;
 width=1;

}

double Player::getX (){    
    return x;
}
double Player::getY (){    
    return y;
}
int Player::getHeight (){    
    return height ;
}
int Player::getWidth (){    
    return width ;
}
void Player:: decreaseHeight (int delta_to_decrease_by){   
 height = height - delta_to_decrease_by;
 if(height<=3){
    height=3;
 }
  
 }
 void Player::update (char c){
     
     if( c == 'A'){
        if(y+2<= HEIGHT-1-height){
            y=y+2;
        }
        else{
            y=HEIGHT-1-height;
        }
     }

     if (c== 'B')
     {
       if(y-2 >= 0){
        y=y-2;
       }
       else{
        y=0;
       }
     }
 }
void Player::draw (Screen& screen_to_draw_to){
   

    for(int i=int(y); i< y+height && i<=HEIGHT-1; i++){
    screen_to_draw_to.addPixel(x,i,'#');

    }

}


 





