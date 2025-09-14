//
//  Ball.cpp
//  Lab 2 Pong Game
//
//  Created by Author Name, Date
#include<iostream>
#include"Ball.h"
#include "Screen.h"

#include "Globals.h"

using namespace std;

Ball::Ball(){
    x=30.0;
    y=30.0; 
    velocity_x=1.7;
    velocity_y=0; 
    id=0; 
    height=1;
    width=1;    
}
//Seeked help from PrivatePiazza post to form constructors with same func prototype and variables to find out
Ball::Ball(double x_coordinate, double y_coordinate, double velocity_xcoordi, double velocity_ycoordi, int id_coordinate){

    x= x_coordinate;
    y=y_coordinate;
   velocity_x=velocity_xcoordi;
   velocity_y=velocity_ycoordi;
   id=id_coordinate;
   width=1;
   height=1;

}

double Ball::getX(){
    return x;
}
int Ball::getID(){
    return id;
}
void Ball::update(){
    velocity_y=velocity_y - 0.02*timeStep;
    y=y+velocity_y*timeStep;
    x=x +velocity_x*timeStep;
    
    
}
 int Ball::overlap(Ball& b){
      
    double x2= (b.getX());
    double y2= (b.y);
    //case 1
    if(x<x2 && x2<x+width && y<y2 && y2<y+height){

        

        if((y+height-y2)>(x+width-x2)){

            return VERTICAL_OVERLAP;

              
        }
        return HORIZONTAL_OVERLAP;

    }
    //case2
      if(x>x2 && x<x2+b.width && y<y2 && y2<y+height){



        if((y+height-y2)>(x2+b.width-x)){

            return VERTICAL_OVERLAP;
       

        }
        return HORIZONTAL_OVERLAP;


        

    }
    //case 3
      if(x<x2 && x2<x+width && y>y2 && y<y2+b.height){
 
         if((y2+b.height-y)>(x+width-x2)){

            return VERTICAL_OVERLAP;

        }
        return HORIZONTAL_OVERLAP;

    }
    //case 4
    
      if(x>x2 && x<x2+b.width && y>y2 && y<y2+b.height){



         if((y2+b.height-y)>(x2+ b.width-x2)){

            return VERTICAL_OVERLAP;

        }
        return HORIZONTAL_OVERLAP;


    }

    return NO_OVERLAP;

    

 }

 int Ball::overlap(Player& p){
// 
    //case 1
    if(x<(p.getX()+p.getWidth()) && p.getX()<x && y<(p.getY()+p.getHeight()) && p.getY()<y){    
//Debuggging to see why collisions arent working with the paddle--->error fixed paddle width not incluided
 
      return HORIZONTAL_OVERLAP;
    } 
   
    else if(x<(p.getX()+p.getWidth()) && p.getX()<x && y+height>p.getY() && p.getY()>y){

        return HORIZONTAL_OVERLAP;
    }
    else

    return NO_OVERLAP;


 }

 void Ball::bounce (Ball arr[], int ballCount, Player player){
    //make sure the ball doesnt bounce with itself

    for(int i=0;i<ballCount;i++){
        if(i!=id){

                if(overlap(arr[i])== HORIZONTAL_OVERLAP){
                    
                    velocity_x=-velocity_x;
                }
                if(overlap(arr[i])== VERTICAL_OVERLAP){
                    velocity_y=-velocity_y;
                    
                }


            }


         if(overlap(player)== HORIZONTAL_OVERLAP){
                    velocity_x=-velocity_x;
                }
                if(overlap(player)== VERTICAL_OVERLAP){
                    velocity_y=-velocity_y;
                }

        if(arr[i].x>=WIDTH-1){ //arr[i].x<0.0 ||
           velocity_x=-velocity_x;
        }
        if(arr[i].y<=0.0 || arr[i].y>=HEIGHT-1){
            velocity_y=-velocity_y;
        }
              
        

    }

 }

 void Ball::draw(Screen& screen_to_draw_to){

    screen_to_draw_to.addPixel(x,y,'o');
 }






