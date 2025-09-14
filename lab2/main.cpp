//
//  main.cpp
//  Lab 2 Pong Game
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-11
//  Copyright © 2024 Nathan Hung. No rights reserved.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <string>
#include "Ball.h"
#include "Globals.h"
#include "Player.h"
//#include "Screen.cpp"
//#include "io.cpp"
#include "Screen.h"
#include "io.h"
////#include "Ball.cpp"
//#include "Player.cpp"

int main() {
  int score = 0;
  bool gameEnded = false;
  std::string messageToPutOnScreen;

  std::chrono::steady_clock::time_point begin_time =
      std::chrono::steady_clock::now();
  std::chrono::steady_clock::time_point now_time;
  Screen screen = Screen();

  int ballCount = 0;
  const int max_ballCount = 5;

  Ball balls_array[max_ballCount];

  balls_array[0] = Ball(30.0, 30.0, 1.7, 0, ballCount);
  ballCount++;

  Player player = Player(0, 5, 10);
  int hit=0; 
  int mockhit=0;
  int ballscore=0;
  // asked ai why my score was increasing in the multiples of 6000 so it suggested creating a boolean to track collisions every frame
  bool collision=false;
  
  

 
  while (!gameEnded) {
    // TODO: ECE 244 Student: Complete the game loop here only!
    // ECE 244 Student: DO NOT edit any other segments of this file!

    //TA assistance for creating the for loop with fps

      
           
     
        for (int i=0; i<=simulation_fps;i++){
          char c= get_input();
        

          if (get_input()=='q'){
                gameEnded=1;   
                break;  
                }

               
               player.update(c);              
      
               

           
            for(int j=0; j< ballCount;j++){

              if(balls_array[j].getX()<=0){
              gameEnded=1;
              break;
             } 
              balls_array[j].update();

              
              balls_array[j].bounce(balls_array, ballCount, player);
              

             
              
          
               if(balls_array[j].overlap(player)==-1 && !collision){

                hit=hit+1;
                score=hit;
                collision=true;
               
               }   
              

               }  

                   

            }
            //SIM FPS ENDS 
            player.draw(screen);
            //player.update(c); 
            for(int j=0; j< ballCount;j++){

              (balls_array[j]).draw(screen);
            }

            //Used help from CHATGPT to set up decreasing height of player function
            if (hit>0 && hit==mockhit+2 )
            {              
              player.decreaseHeight(1);
              mockhit=hit;
            }
             if(score>=5&& score==ballscore+5 && ballCount<max_ballCount){
              
              balls_array[ballCount]=Ball(30.0, 30.0, 0.9, 0, ballCount);
              ballscore=score;
              ballCount++;
             }
             //resetting it for the next set of frames
             collision=false;
             
             

            //if (c=='q'){
              //  gameEnded=1;   
                //break;  
                //}        
          
                messageToPutOnScreen = "Your score is: " + std::to_string(score);
    screen.update(messageToPutOnScreen);

    // wait until 1/fps seconds
    while (std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now() - begin_time)
               .count() < (long int)milliseconds_per_frame) {
    }

    begin_time = std::chrono::steady_clock::now();
  }
  messageToPutOnScreen = "Game over. Your score is: " + std::to_string(score);
  screen.update(messageToPutOnScreen);

  return 0;
}