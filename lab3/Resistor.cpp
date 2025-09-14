//
//  Resistor.cpp
//  Lab 3 The Resistor Network Program
// Author:Mehul Garg
// Date:6th October

#include "Resistor.h"


#include <iomanip>
using namespace std;

void Resistor::print() {
  cout << std::left << std::setw(20) << name << std::right << std::setw(8)
       << std::fixed << std::setprecision(2) << resistance << " Ohms "
       << endpointNodeIDs[0] << " -> " << endpointNodeIDs[1] << endl;
}

Resistor::Resistor(string name_, double resistance_, int *endpoints_){

name=name_;
resistance=resistance_;
for(int i=0;i<2;i++){
endpointNodeIDs[i]=endpoints_[i];
}

}

std::string Resistor::getName(){

  return name;

}

double Resistor::getResistance(){

return resistance;
}

void Resistor::setResistance(double resistance_){

  resistance=resistance_;
}

int Resistor::getOtherEndpoint(int nodeIndex){

  for(int i=0;i<2;i++){

  if(endpointNodeIDs[i]!= nodeIndex){
    return endpointNodeIDs[i];
  } 
  

}
return -1;

}