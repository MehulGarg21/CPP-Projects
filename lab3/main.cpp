//
//  main.cpp
//  Lab 3 The Resistor Network Program
//
//  Created by Nathan Hung on 2024-09-11.
//  Modified by Salma Emara on 2024-09-30
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.
//
//  ECE244 Student: Complete the skeletal code of the main function in this file

#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "Node.h"
#include "Resistor.h"

using namespace std;

Resistor** resistors =
    nullptr;  // Pointer that should point to an array of Resistor pointers
Node* nodes = nullptr;  // pointer that should hold address to an array of Nodes
int maxNodeNumber = 0;  // maximum number of nodes as set in the command line
int maxResistors = 0;  // maximum number of resistors as set in the command line
int resistorsCount = 0;  // count the number of resistors
bool codeended=false;
bool deleted=false;

string errorArray[10] = {
    "invalid command",      // 0
    "invalid argument",         // 1
    "negative resistance",       // 2
    "node value is out of permitted range",             // 3
    "resistor name cannot be keyword \"all\"",          // 4
    "both terminals of resistor connect to same node",  // 5
    "too few arguments",                                // 6
};

// Function Prototypes
bool getInteger(stringstream& ss, int& x);
bool getString(stringstream& ss, string& s);
bool getDouble(stringstream& ss, double& s);

void handleMaxVal(stringstream& ss);
void handleInsertR(stringstream& ss);
void handleModifyR(stringstream& ss);
void handlePrintR(stringstream& ss);
void handleDeleteR(stringstream& ss);
void handleSetV(stringstream& ss);
void handleSolve();

int main() {
  string line;
  cout << ">>> ";
  cout.flush();

  
  // TODO: Implement the main function here

    // get the number of all the resistors only when maxval is intitated
   while(!codeended){

    //Seeked Help from chatpt to implement ctrd+d command as i was getting very confused on the presence of a second getline which delayed all my expected output by one command

    if (!getline(cin, line)) {
            // If we reach end-of-file (Ctrl+D)
            if (cin.eof()) {
                codeended=true;
                break;  // Exit the loop if EOF is detected
            }
    }    

    //getline (cin,line);
    stringstream ss(line);
    // Trim the white spaces . Citation: Question@569 Public Piazza Post Code Snippet in Comments
   
    line.erase(line.find_last_not_of(" \t\n\r\f\v") + 1); 
          
    string cmd;
    ss>>cmd;

    if(cmd != "maxVal" && cmd !="insertR"&& cmd !="modifyR"&&cmd !="printR"&&cmd !="deleteR"&& cmd !="setV"&&cmd !="solve"){
      
      cout<<"Error :"<<errorArray[0]<<endl;
      
      
      ss.ignore(1000,'\n');
      
    }

    if(cmd=="maxVal"){
      handleMaxVal(ss);
    }

    if(cmd=="insertR"){
      handleInsertR(ss);

    }

    if(cmd=="modifyR"){
      handleModifyR(ss);
    }

  if(cmd=="printR"){
      handlePrintR(ss);
    }

  if(cmd=="deleteR"){
      handleDeleteR(ss);
    }
  
  if(cmd=="setV"){
      handleSetV(ss);
    }

    if(cmd=="solve"){
     handleSolve();
    }

  



      
   cout << ">>> ";
   }
   //While loop ends here

   //Freeing memeory of dynamically allocated arrays
   



   
  if (resistors != nullptr) {
        for (int i = 0; i < maxResistors; i++) {
            if (resistors[i] != nullptr) {
                delete resistors[i];
                resistors[i] = nullptr;
            }
        }
        delete[] resistors;
        resistors = nullptr;
    }

 


   if(nodes!=nullptr){
 delete [] nodes;
}
   return 0;
   
}

// TODO: Implement functions here

void handleMaxVal(stringstream& ss){

 if (resistors != nullptr) {
        for (int i = 0; i < maxResistors; i++) {
            if (resistors[i] != nullptr) {
                delete resistors[i];
                resistors[i] = nullptr;
            }
        }
        delete[] resistors;
        resistors = nullptr;
    }


  if(nodes!=nullptr){
 delete [] nodes;
 nodes=nullptr;
}

  ss>> maxNodeNumber;

      if(ss.fail()){

        
        //if eof is true then few args else invalid arg
        if(ss.eof()){
        cout<<"Error: "<< errorArray[6]<<endl;
        }
        else{
        cout<<"Error: "<< errorArray[1]<<endl;
        }
        ss.clear();
        ss.ignore(1000,'\n');
        return;
        
            

      }
      else if(maxNodeNumber<=0){
        ss.clear();
        ss.ignore(1000,'\n');
        cout<<"Error: "<< errorArray[1]<<endl;
        return;


      }
      else {
      

      ss>> maxResistors;

       if(ss.fail()){       

        if(ss.eof()){
        cout<<"Error: "<< errorArray[6]<<endl;
        }
        else{
        cout<<"Error: "<< errorArray[1]<<endl;
        }

        ss.clear();
        ss.ignore(1000,'\n');
        
      
        return;
               
      }
      else if(maxResistors<=0){
         cout<<"Error: "<< errorArray[1]<<endl;
         return;
      }
      else{   
        nodes=new Node [maxNodeNumber];        
        
        resistors= new Resistor*[maxResistors];    

        for (int i=0;i<maxResistors;i++) {

          resistors[i]=nullptr;
        }  

       cout<<" New network: max node number is " << maxNodeNumber <<"; max resistors is "<<maxResistors <<endl;

        
        return;
        


      }
      } 



}

void handleInsertR(stringstream& ss){

string resistancename;
ss>>resistancename;

if(ss.fail()){

if(ss.eof()){
 cout<<"Error: "<< errorArray[6]<<endl;
 }
 else{
  cout<<"Error: "<< errorArray[1]<<endl;
 } 
 
 ss.clear();
 ss.ignore(1000,'\n');

 return;

 }
 else if(resistancename=="all"){
        ss.clear();
        ss.ignore(1000,'\n');
        cout<<"Error: "<< errorArray[4]<<endl;
        return;


      }
      else{
        for(int i=0;i<maxResistors;i++){
          if (resistors[i] != nullptr && resistancename==resistors[i]->getName())
          {
            cout<<"Error: resistor "<< resistancename <<" already exists"<<endl;
            return;
            
          }
          
        }

        double resvalue;

        ss>>resvalue;

         if(ss.fail()){       

        if(ss.eof()){
        cout<<"Error: "<< errorArray[6]<<endl;
        }
        else{
        cout<<"Error: "<< errorArray[1]<<endl;
        }

        ss.clear();
        ss.ignore(1000,'\n');
        
      
        return;
               
      }
      else if(resvalue<0.0){
         cout<<"Error: "<< errorArray[2]<<endl;
         return;
      }
      else{

        int nodeone;
        ss>>nodeone;

        if(ss.fail()){       

        if(ss.eof()){
        cout<<"Error: "<< errorArray[6]<<endl;
        }
        else{
        cout<<"Error: "<< errorArray[1]<<endl;
        }

        ss.clear();
        ss.ignore(1000,'\n');
        
      
        return;
               
      }

      else if(nodeone<1 || nodeone>maxNodeNumber){

        cout<<"Error: "<< errorArray[3]<< " 1-"<<maxNodeNumber<<endl;
        return;

      }
      else{

        int nodetwo;
        ss>>nodetwo;
        if(ss.fail()){       

        if(ss.eof()){
        cout<<"Error: "<< errorArray[6]<<endl;
        }
        else{
        cout<<"Error: "<< errorArray[1]<<endl;
        }

        ss.clear();
        ss.ignore(1000,'\n');
        
      
        return;
               
      }
      else if(nodetwo<1 || nodetwo>maxNodeNumber){

        cout<<"Error: "<< errorArray[3]<< " 1-"<<maxNodeNumber<<endl;
        return;

      }
      else if(nodeone==nodetwo){

        cout<< "Error: both terminals of resistor connect to same node"<<endl;
        return;
      }

      else{// All input is correct at this point

      int endpoints[2]={nodeone,nodetwo};

    resistors[resistorsCount]=new Resistor(resistancename,resvalue,endpoints);

    //Inputting nodes into node arrays by using nodeone-1, nodetwo-1

    if(nodes[nodeone-1].canAddResistor()){
      nodes[nodeone-1].addResistor(resistorsCount);   

    }
    else{
      cout<<"Error: Node" <<nodeone<< " has maximum resistors"<<endl;
      ss.clear();
      ss.ignore(1000,'\n');      
      return;

    }
     if(nodes[nodetwo-1].canAddResistor()){
      nodes[nodetwo-1].addResistor(resistorsCount);   

    }
    else{
      cout<<"Error: Node" <<nodeone<< " has maximum resistors"<<endl;
      ss.clear();
      ss.ignore(1000,'\n');      
      return;

    }
    // Used website to find how to set precision
    cout << std::fixed << std::setprecision(2);
cout << "Inserted: resistor " << resistancename << " " << resvalue << " Ohms " << nodeone << " -> " << nodetwo << endl;
    
     resistorsCount++;
     return;
      }
      //Else of nodetwo

      }
      //Else of nodeone

      }
      //Else of resistance
      }
      //Else of name

// Function close bracket
}

void handleModifyR(stringstream& ss){

  string resistorname;
  ss>>resistorname;
  if(ss.fail()){       

        if(ss.eof()){
        cout<<"Error: "<< errorArray[6]<<endl;
        }
        else{
        cout<<"Error: "<< errorArray[1]<<endl;
        }

        ss.clear();
        ss.ignore(1000,'\n');
        
      
        return;
               
      }
      else if(resistorname=="all"){
        ss.clear();
        ss.ignore(1000,'\n');
        cout<<"Error: "<< errorArray[4]<<endl;
        return;


      }
      //insert else if for a condition where R1 not found
      
      else {
        bool resistorfound=0;

         if (resistors==nullptr){
    cout<<"Error: resistor "<<resistorname<<" not found"<<endl;
      return;
    
  }

    for (int i = 0; i < maxResistors; i++) {
        if (resistors[i] != nullptr && resistorname == resistors[i]->getName()) {
            // We should continue the program from here
            resistorfound=1;
            double resvalue;
            ss >> resvalue;

            if (ss.fail()) {
                if (ss.eof()) {
                    cout << "Error: " << errorArray[6] << endl;
                } else {
                    cout << "Error: " << errorArray[1] << endl;
                }

                ss.clear();
                ss.ignore(1000, '\n');
                return;
            } 
            else if (resvalue < 0.0) {
                cout << "Error: " << errorArray[2] << endl;
                return;
            } 
            else {
                // Actually modify R by changing values
                double oldres;
                oldres=resistors[i]->getResistance();
                resistors[i]->setResistance(resvalue);
                cout <<"Modified: resistor "<< resistorname<<" from "<<oldres<< " Ohms to "<<resvalue << " Ohms"<<endl;
                return;


                // Code to modify the resistor goes here
            }
        }
        //if closing bracket inside the for loop

    }
    //Outside for loop 
    //creating condition for insufficent arguments
    double resvaluedummy;
            ss >> resvaluedummy;

            if (ss.fail()) {
                if (ss.eof()) {
                    cout << "Error: " << errorArray[6] << endl;
                } else {
                    cout << "Error: " << errorArray[1] << endl;
                }

                ss.clear();
                ss.ignore(1000, '\n');
                return;
            } 
             else if (resvaluedummy < 0.0) {
                cout << "Error: " << errorArray[2] << endl;
                return;
            } 




    if(!resistorfound){
      cout<<"Error: resistor "<<resistorname<<" not found"<<endl;
      return;
    }


}
 //Else loop for resistance name ends here 

}
//function closes here


void handlePrintR(stringstream& ss){

 

  string resname;
  ss>> resname;


  if(ss.fail()){
    if (ss.eof()) {
   cout << "Error: " << errorArray[6] << endl;
   } else {
    cout << "Error: " << errorArray[1] << endl;
  }

 ss.clear();
 ss.ignore(1000, '\n');
 return;


  }

   if (resistors==nullptr){
    cout<<"Error: resistor "<<resname<<" not found"<<endl;
      return;
    
  }
  bool resistorfound=0;

  for (int i = 0; i < maxResistors; i++) {
        if (resistors[i] != nullptr && resname == resistors[i]->getName()) {

          resistorfound=1;
          cout<<"Print:"<<endl;
          resistors[i]->print();
          return;


        }
  }

  if(!resistorfound){
      cout<<"Error: resistor "<<resname<<" not found"<<endl;
      return;
    }

}
//Function ends

void handleDeleteR(stringstream& ss){

  string all;
  ss>>all;

  if(ss.fail()){
    if (ss.eof()) {
   cout << "Error: " << errorArray[6] << endl;
   } else {
    cout << "Error: " << errorArray[1] << endl;
  }

 ss.clear();
 ss.ignore(1000, '\n');
 return;


  }
  else if(all=="all"){

    if (resistors != nullptr) {
        for (int i = 0; i < maxResistors; i++) {
            if (resistors[i] != nullptr) {
                delete resistors[i];
                resistors[i] = nullptr;
            }
        }
        delete[] resistors;
        resistors = nullptr;
    }

 


   if(nodes!=nullptr){
 delete [] nodes;
 nodes=nullptr;
}
resistorsCount=0;
deleted=true;

cout<<"Deleted: all resistors"<<endl;
return;


  }
 // If entered something like deleteR jifcjirj
  else{
    cout << "Error: " << errorArray[1] << endl;
    return;

  }

}
//Function ends

void handleSetV(stringstream& ss){

  int nodeid;
  ss>>nodeid;

  if(ss.fail()){
    if (ss.eof()) {
   cout << "Error: " << errorArray[6] << endl;
   } else {
    cout << "Error: " << errorArray[1] << endl;
  }

 ss.clear();
 ss.ignore(1000, '\n');
 return;


  }
  else if(nodeid<1 || nodeid>maxNodeNumber){

        cout<<"Error: "<< errorArray[3]<< " 1-"<<maxNodeNumber<<endl;
        return;

      }

      else{
        double vol;
        ss>>vol;
       if(ss.fail()){
       if (ss.eof()) {
       cout << "Error: " << errorArray[6] << endl;
       } else {
        cout << "Error: " << errorArray[1] << endl;
       }
        ss.clear();
        ss.ignore(1000, '\n');
       return;            
      }
      else{
        //Actually setting Voltage vol at node nodeid, where actual value = nodeid-1

        nodes[nodeid-1].setVoltage(vol);
        cout<<"Set: node " <<nodeid<< " to "<<vol<<" Volts"<<endl;
        return;

      }

}
//Else of valid nodeid
}
//Function edns


void handleSolve(){
//Initialize the voltage of all nodes without a specified (setV) voltage to 0.

//while (some node’s voltage has changed by more than MIN_ITERATION_CHANGE) {

  //  for (all nodes without a set voltage) {

    //    set voltage of node according to Eq. 3

    //}/

//}
//min iteration  0.0001

//KEYYYYYYYYYYY POINTS:::

//set up a case where null pointer enters
//dont forget to return
//while printing print node+1


//Referred steps used by student in piazza post @307 just to get an idea of how the solve command flow will work , code is written on my own. 

bool miniteration=false;

if(resistors==nullptr || nodes==nullptr){
  return;
}

for(int i=0; i<maxNodeNumber;i++){
  
  if(!(nodes[i].isVoltageSet())){
    nodes[i].setVoltageInternally(0);

  }
  
}
while (!miniteration){
 miniteration=true;

for(int i=0; i<maxNodeNumber;i++){

  
  if(!(nodes[i].isVoltageSet())){
  
  double resistanceparallel=0.00;
  double vsum=0.0;
  

 int resistornum=0;
 resistornum=nodes[i].getNumRes();
 int * arrayofres=nullptr;
 arrayofres=nodes[i].getResIDArray();

 for(int j=0;j<resistornum;j++){
  
  int resid=arrayofres[j];
  //pointer to access the resistors
  Resistor* respointer = resistors[resid];
  int othernode=0;
  //2nd node the resistor connects to

  othernode= respointer->getOtherEndpoint(i+1);
  if (othernode == -1) {
                        continue;
                    }

  //Net resistance
  double currentresis;  
  double othernodeV=nodes[othernode-1].getVoltage();
  currentresis=respointer->getResistance();
//KCL equation
  vsum= vsum + (othernodeV/currentresis);
  resistanceparallel=  resistanceparallel+1.00/currentresis;
 
 }

 double updatedvolt =vsum/resistanceparallel;

 double oldvoltage=nodes[i].getVoltage();

 if(abs(updatedvolt-oldvoltage)>0.0001){
  miniteration=false;
 }

 nodes[i].setVoltageInternally(updatedvolt);  
   

  }
  
}
}
//Setting voltages so that boolean flag is set to true
for (int i = 0; i < maxNodeNumber; i++) {
 if (!nodes[i].isVoltageSet()) {
 double voltage;
 voltage= nodes[i].getVoltage();
 nodes[i].setVoltage(voltage);
  }

 }

 cout<<"Solve:"<<endl;

 // Used chatgpt to set precision of outcome to 2 decimal places
 for (int i = 0; i < maxNodeNumber; i++) {
        if (nodes[i].getNumRes() != 0) {            
            cout << "Node " << (i + 1) << ": " << fixed << setprecision(2) << nodes[i].getVoltage() << " V" << endl;
        }
    }
}