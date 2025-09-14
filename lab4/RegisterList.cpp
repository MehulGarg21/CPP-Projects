#include "RegisterList.h"

#include <iostream>


#include "Register.h"
using namespace std;

RegisterList::RegisterList() {
  head = nullptr;
  size = 0;
}

RegisterList::~RegisterList() {
  // Delete all registers in the list
  delete head;
}

Register* RegisterList::get_head() {
  return head;
  }

int RegisterList::get_size() { 
  // return number of registers 
return size;
  
}


Register* RegisterList::get_min_items_register() {
  // loop all registers to find the register with least number of items
   if(head==nullptr){
    return nullptr;
  }
  else{
    int itemless=INT16_MAX;
    Register*p=head;
    while(p!=nullptr){
      if(p->get_queue_list()->get_items()<itemless)
      itemless=p->get_queue_list()->get_items();
      p=p->get_next();
    }
    //resetting p to head to navigate another loop
    p=head;

    while(p!=nullptr){
      if(p->get_queue_list()->get_items()==itemless){
        return p;
      }
      p=p->get_next();
    }
    // if nothing is free , which wont happen ut for safety
    return nullptr;
    
    
  } 

}

Register* RegisterList::get_free_register() {
  // return the register with no customers
  // if all registers are occupied, return nullptr
 Register*p=head;
 if(head==nullptr){
    return nullptr;
  }
 while(p!=nullptr){
      if(p->get_queue_list()->get_head()==nullptr){
        return p;
      }
      p=p->get_next();
    }
    return nullptr;
}

void RegisterList::enqueue(Register* newRegister) {
  // a register is placed at the end of the queue
  // if the register's list is empty, the register becomes the head
  // Assume the next of the newRegister is set to null
  // You will have to increment size 
  if(head==nullptr){
    head=newRegister;    
  }
  else{
  Register*p=head;
  while(p->get_next()!=nullptr){
  p=p->get_next();
  }
  p->set_next(newRegister);  
  }
  size++;
  return; 
}

bool RegisterList::foundRegister(int ID) {
  // look for a register with the given ID
  // return true if found, false otherwise
  Register*p=head;
  if(head==nullptr){
    return 0;
  }
  while(p!=nullptr){
      if(p->get_ID()==ID){
        return 1;
      }
      p=p->get_next();
    }
    return false;

}

Register* RegisterList::dequeue(int ID) {
  // dequeue the register with given ID

  // return the dequeued register
  // return nullptr if register was not found
Register*p=head;
  if(head==nullptr){
    return nullptr;
  } 

    if(head->get_ID()==ID){
      head=head->get_next();
      size--;
      p->set_next(nullptr);
      return p;
    }
  
  Register*pnext=head->get_next();
  while(pnext!=nullptr){
      if(pnext->get_ID()==ID){
        Register* link= pnext->get_next();
        p->set_next(link);
        pnext->set_next(nullptr); 
        size--;    
        return pnext;   
        
      }
      p=p->get_next();
      pnext=pnext->get_next();
      
    }
    return nullptr;

}

Register* RegisterList::calculateMinDepartTimeRegister(double expTimeElapsed) {
  // Return the register with minimum time of departure of its customer
  // If all registers are free, return nullptr

//In main we will depart the customers first
  // Check if the list is empty

  //Asked AI advice to remodify this function in a way that it adds customers to done list in a sequential manner
  
  if (head == nullptr) {
        return nullptr;  
    }

    Register* minReg = nullptr;
    double minDepTime = __DBL_MAX__;  
    Register* current = head;

    bool allRegistersFree = true;

    while (current != nullptr) {
      //Loops through the entire list to ensure that donelist is in order of least departure time to highest departure time
        double depTime = current->calculateDepartTime();
        if (depTime >= 0) {
            
            allRegistersFree = false;

            // Send the register which needs to be departed after elapsed time
            if (depTime <= expTimeElapsed && depTime < minDepTime) {
                minDepTime = depTime;
                minReg = current;
            }
        }
        current = current->get_next();
    }

    // If all registers are free , return nullptr
    if (allRegistersFree) {
        return nullptr;
    }

    return minReg;  
}