//
//  BST.cpp
//  Lab 5 Search Through A Database
//
//  Created by Author Name: Mehul Garg, Date: 11th November 2024
#include "BST.h"

#include "Employee.h"
#include <string>
using namespace std;
#include <sstream>


BST::BST(string order_) {
  root = nullptr;
  order = order_;
}
BST::~BST(){
  delete root;  
}

void BST::insert(Employee *newEmployee){
if(order=="name"){
  if(root==nullptr){
    root=newEmployee;
    return;
  }
  string newName= newEmployee->getName();
  Employee*temp=root;
  bool inserted= false;

while(!inserted){
  //Going right in the bst since current value is greater
if(newName.compare(temp->getName())>0){
  if(temp->getRight()== nullptr){
    temp->setRight(newEmployee);
    inserted=true;
  }
  else{
    temp=temp->getRight();
  }
}//Sending everything to the left (the equal case and the case when it is lesser)
else{
  //Insert if empt left node
  if(temp->getLeft()== nullptr){
    temp->setLeft(newEmployee);
    inserted=true;
  } 
  else{ 
    temp=temp->getLeft();
  } 
}
} 


}
else if(order=="ID"){

  if(root==nullptr){
    root=newEmployee;
    return;
  }
  int newID=newEmployee->getID();
  Employee* temp= root;
  bool inserted=false;

  //Same iteration as above for name
  while(!inserted){
  //Going right in the bst since current value is greater
if(newID>temp->getID()){
  if(temp->getRight()== nullptr){
    temp->setRight(newEmployee);
    inserted=true;
  }
  else{
    temp=temp->getRight();
  }
}//Since no 2 IDS can be equal other condition has to be ID<
else{
  //Insert if empt left node
  if(temp->getLeft()== nullptr){
    temp->setLeft(newEmployee);
    inserted=true;
  } 
  else{ // Continue navigating
    temp=temp->getLeft();
  } 
}
} 

}
else
//This will be for age
//Assuming no other condition and only passed when valid
{
  if(root==nullptr){
    root=newEmployee;
    return;
  }   
  double newAge=newEmployee->getAge();
  Employee* temp= root;
  bool inserted=false;

  //Same iteration as above for name
  while(!inserted){
  //Going right in the bst since current value is greater
if(newAge>temp->getAge()){
  if(temp->getRight()== nullptr){
    temp->setRight(newEmployee);
    inserted=true;
  }
  else {
    temp=temp->getRight();
  }
}
else //Since 2 ppl have same age we will compare NAMES or IDS 
{
  //Insert if empt left node
  if(temp->getLeft()== nullptr){
    temp->setLeft(newEmployee);
    inserted=true;
  } 
  else{ // Continue navigating
    temp=temp->getLeft();
  } 
}
} 
}
}
void printHelper (Employee* n){  

  if(n!=nullptr){
    printHelper(n->getLeft());
    n->print();
    printHelper(n->getRight());
  }  

}


void BST::printInOrder(){
  //Order of name , age , id should matter , depends on what is passed in the main
 if(order=="age"){
  if (root == nullptr){
    return;
  }
 printHelper(root);
 }
 else if(order=="ID"){
  if (root == nullptr){
    return;
  }
  printHelper(root);

 }
 else {
  if (root == nullptr){
    return;
  }
  printHelper(root);
 }
}



Employee *BST::searchID(int ID){
//Keep going left or right in the tree until we reach a null ptr , if nullptr
//reached this implies that ID dne.
//SHOULD BE IMPLEMENTED ON ID TREE
if(root==nullptr){
  return nullptr;
}
Employee*temp=root;
bool found=false;
while(temp!=nullptr && !found){
  if(ID>temp->getID()){
    temp=temp->getRight();
  }
   else if(ID<temp->getID()){
    temp=temp->getLeft();
  }
  else{
    found=true;    
  }
}
if(!found){  
  return nullptr;
}
else{
  return temp;
}
}
void searchAgeHelper(Employee * n, double lowAge, double highAge){
  if(n!=nullptr){
    if(n->getLeft()!= nullptr){
      searchAgeHelper(n->getLeft(),lowAge,highAge);
    }
    if(n->getAge()>=lowAge && n->getAge()<=highAge){
      n->print();
    }
    if(n->getRight()!= nullptr){
      searchAgeHelper(n->getRight(),lowAge,highAge);
    }
    
  }
}

void BST::searchAgeRange(double lowAge, double highAge){
//Need to find solution to arranging individuals with same age--> we will be taking a norm of sending them to the left hand suide
searchAgeHelper(root,lowAge,highAge);
}

void autocompleteHelper(Employee *n, string userEntry,std::string::size_type length){
  if(n!=nullptr){
    if(n->getLeft()!=nullptr){
      autocompleteHelper(n->getLeft(),userEntry,length);      
    }
    //Here we chk comparison for current
    string foundName=n->getName();
    foundName=foundName.substr(0,length);
    if(userEntry.compare(foundName)== 0){
      n->print();
    }
    if(n->getRight()!=nullptr){
      autocompleteHelper(n->getRight(),userEntry,length);      
    }
  }
} 

void BST::autocomplete(string userEntry){
//Check if  space in between or not as a first step--> will be using string streams i think
//For a user operating the database, the <prefix of a name> can be any part of a first name
//without the last name or first name followed by a space and a part of the last name of an employee
/*stringstream ss (prefix);
string userFirstName;
string userLastName;
string userEntry;

//Will catenate firstname with last name as employee class does the same for get name
//easier to check;
ss>>userFirstName;
ss>>userLastName;
if(ss.fail()){
  //Last name not enetered
  ss.clear();
  ss.ignore(1000,'\n');
  userEntry=userFirstName;
}
else{
  userEntry=userFirstName+userLastName;
}
*/
//Calculating length of user entry so we can compare that with getname function in helper func
//13th NOvember 2024 :Producing error so google type of length aand changed it to "std::string::size_type"
//Link:https://stackoverflow.com/questions/73463592/what-type-of-data-does-string-length-return-in-c#:~:text=length()%20function%20returns%20a,an%20unsigned%20type%2C%20for%20sure.&text=%22what%20type%20of%20data%20does%20string.
std::string::size_type length;
length=userEntry.length();
autocompleteHelper(root,userEntry,length);
}
