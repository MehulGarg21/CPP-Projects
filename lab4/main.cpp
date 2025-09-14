#include <cmath>
#include <cstdlib>
#include <iostream>
#include <sstream>

#include "Customer.h"
#include "QueueList.h"
#include "Register.h"
#include "RegisterList.h"

using namespace std;

// Function Declarations:

// Set mode of the simulation
string getMode();

// Register
void parseRegisterAction(stringstream &lineStream, string mode);
void openRegister(
    stringstream &lineStream,
    string mode);  // register opens (it is upto customers to join)
void closeRegister(stringstream &lineStream,
                   string mode);  // register closes 

// Customer
void addCustomer(stringstream &lineStream,
                 string mode);  // customer wants to join


// Helper functions
bool getInt(stringstream &lineStream, int &iValue);
bool getDouble(stringstream &lineStream, double &dValue);
bool foundMoreArgs(stringstream &lineStream);
//addeed a new function
void calculateStatistics(QueueList* doneList);
// Global variables
RegisterList *registerList; // holding the list of registers
QueueList *doneList; // holding the list of customers served
QueueList *singleQueue; // holding customers in a single virtual queue
double expTimeElapsed; // time elapsed since the beginning of the simulation

// List of commands:
// To open a register
// register open <ID> <secPerItem> <setupTime> <timeElapsed>
// To close register
// register close <ID> <timeElapsed>
// To add a customer
// customer <items> <timeElapsed>

int main() {
  registerList = new RegisterList();
  doneList = new QueueList();
  singleQueue = new QueueList();
  expTimeElapsed = 0;

  // Set mode by the user
  string mode = getMode();

  string line;
  string command;

  cout << "> ";  // Prompt for input
  getline(cin, line);

  while (!cin.eof()) {
    stringstream lineStream(line);
    lineStream >> command;
    if (command == "register") {
      parseRegisterAction(lineStream, mode);
    } else if (command == "customer") {
      addCustomer(lineStream, mode);
    } else {
      cout << "Invalid operation" << endl;
    }
    cout << "> ";  // Prompt for input
    getline(cin, line);
  }
    // We will be dynamically allocating in main, classes will just handle already allocated objects
    //on the heap


    //Remember to add exptimeelapsed for calculations 

     cout << "Finished at time " <<expTimeElapsed<< endl;

    // Func that displays stats
    calculateStatistics(doneList);

    
  // You have to make sure all dynamically allocated memory is freed 
  // before return 0
  delete registerList;
  delete doneList;
  delete singleQueue;
  //Every thing has a recursive delete call so all destructors clean up the memory

  return 0;
}

string getMode() {
  string mode;
  cout << "Welcome to ECE 244 Grocery Store Queue Simulation!" << endl;
  cout << "Enter \"single\" if you want to simulate a single queue or "
          "\"multiple\" to "
          "simulate multiple queues: \n> ";
  getline(cin, mode);

  if (mode == "single") {
    cout << "Simulating a single queue ..." << endl;
  } else if (mode == "multiple") {
    cout << "Simulating multiple queues ..." << endl;
  }

  return mode;
}

void addCustomer(stringstream &lineStream, string mode) {
  int items;
  double timeElapsed;
  if (!getInt(lineStream, items) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments." << endl;
    return;
  }
  // Depending on the mode of the simulation (single or multiple),
  // add the customer to the single queue or to the register with
  // fewest items
  expTimeElapsed = expTimeElapsed+timeElapsed;
  // We will be dynamically allocating in main
//Arrival time= updated elapsed time.

//Loop to depart customers after elapsed time has passed, for multiple mode queueing functions automatically handle departure of customers
//For single mode we will have to manually assign customers from single queue to the registers.
  while (true) {    
        Register* regToDepart = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
      //Exits loop if no customers are ready to depart
        if (regToDepart == nullptr) {
            break;  
        }
      //Place each customer in order from calculate min depart time register
        regToDepart->departCustomer(doneList);

        cout << "Departed a customer at register ID " << regToDepart->get_ID() << " at " << regToDepart->get_availableTime() << endl;

        // In single mode, assign a new customer from the single queue if available, since we assign the free register to prior existing registers 
        //and then worry about newly added registers. Moreover the customer is added after single queue is updated
        if (mode == "single") {
            if (singleQueue->get_head() != nullptr) {
                Customer* nextCustomer = singleQueue->dequeue();
                regToDepart->get_queue_list()->enqueue(nextCustomer);              
                cout << "Queued a customer with free register " << regToDepart->get_ID() << endl;
            }
        }
    }

    // Create the new customer
    Customer* newCustomer = new Customer(expTimeElapsed, items);

    if (mode == "multiple") {
        // Queue customer with the register with the least number of items
        Register* targetRegister = registerList->get_min_items_register();
        if (targetRegister != nullptr) {          
            targetRegister->get_queue_list()->enqueue(newCustomer);
            cout << "A customer entered"<<endl;
            cout << "Queued a customer with quickest register " << targetRegister->get_ID() << endl;
        } else {           
            cout << "Error: no registers are open" << endl;
            //Remove the newly created customer
            delete newCustomer;  
        }
    } else if (mode == "single") {
        // Enqueue the customer to the singlequeue if no free registers
        if(registerList->get_free_register()!=nullptr){
           Register* freeRegister = registerList->get_free_register();
    freeRegister->get_queue_list()->enqueue(newCustomer);
          cout << "A customer entered" << endl;
          cout << "Queued a customer with free register "<<freeRegister->get_ID()<< endl;
        
        }
        else{
          singleQueue->enqueue(newCustomer);
        cout << "A customer entered" << endl;
        cout << "No free registers" << endl;
        }
    }


}

void parseRegisterAction(stringstream &lineStream, string mode) {
  string operation;
  lineStream >> operation;
  if (operation == "open") {
    openRegister(lineStream, mode);
  } else if (operation == "close") {
    closeRegister(lineStream, mode);
  } else {
    cout << "Invalid operation" << endl;
  }
}

void openRegister(stringstream &lineStream, string mode) {
  int ID;
  double secPerItem, setupTime, timeElapsed;
  // convert strings to int and double
  if (!getInt(lineStream, ID) || !getDouble(lineStream, secPerItem) ||
      !getDouble(lineStream, setupTime) ||
      !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }

  // Check if the register is already open
  // If it's open, print an error message
  // Otherwise, open the register
  // If we were simulating a single queue, 
  // and there were customers in line, then 
  // assign a customer to the new register

  if (registerList->foundRegister(ID)) {
   cout << "Error: register " << ID << " is already open" << endl;
   return; 
 }
 
  expTimeElapsed=expTimeElapsed+timeElapsed;
  // WE DYNAMICALLY ALLOCATE THE REGISTER HERE AS WELL so classes become simpler 
while (true) {    
        Register* regToDepart = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
      //Exits loop if no customers are ready to depart
        if (regToDepart == nullptr) {
            break;  
        }
      //Place each customer in order from calculate min depart time register
        regToDepart->departCustomer(doneList);

        cout << "Departed a customer at register ID " << regToDepart->get_ID() << " at " << regToDepart->get_availableTime() << endl;

        // In single mode, assign a new customer from the single queue if available, since we assign the free register to prior existing registers 
        //and then worry about newly added registers. Moreover the customer is added after single queue is updated
        if (mode == "single") {
            if (singleQueue->get_head() != nullptr) {
                Customer* nextCustomer = singleQueue->dequeue();
                regToDepart->get_queue_list()->enqueue(nextCustomer);              
                cout << "Queued a customer with free register " << regToDepart->get_ID() << endl;
            }
        }
    }

  
    Register* newReg = new Register(ID, secPerItem, setupTime, expTimeElapsed);
    registerList->enqueue(newReg);
    cout << "Opened register " << ID <<endl;

    // In single mode, assign a customer from the single queue to the newly created register
    //For multiple mode nothing happens since customers are already queued to their registers and will not move from them

    if (mode == "single") {
        if (singleQueue->get_head() != nullptr) {
            Customer* nextCustomer = singleQueue->dequeue();
            newReg->get_queue_list()->enqueue(nextCustomer);
            cout << "Queued a customer with free register " << newReg->get_ID() << endl;
        }
    }
    
}

void closeRegister(stringstream &lineStream, string mode) {
  int ID;
  double timeElapsed;
  // convert string to int
  if (!getInt(lineStream, ID) || !getDouble(lineStream, timeElapsed)) {
    cout << "Error: too few arguments." << endl;
    return;
  }
  if (foundMoreArgs(lineStream)) {
    cout << "Error: too many arguments" << endl;
    return;
  }
  // Check if the register is open
  // If it is open dequeue it and free it's memory
  // Otherwise, print an error message 
  expTimeElapsed += timeElapsed;

    // Process any departures due up to the new expTimeElapsed
    //Same system update commands
   while (true) {    
        Register* regToDepart = registerList->calculateMinDepartTimeRegister(expTimeElapsed);
      //Exits loop if no customers are ready to depart
        if (regToDepart == nullptr) {
            break;  
        }
      //Place each customer in order from calculate min depart time register
        regToDepart->departCustomer(doneList);

        cout << "Departed a customer at register ID " << regToDepart->get_ID() << " at " << regToDepart->get_availableTime() << endl;

        // In single mode, assign a new customer from the single queue if available, since we assign the free register to prior existing registers 
        //and then worry about newly added registers. Moreover the customer is added after single queue is updated
        if (mode == "single") {
            if (singleQueue->get_head() != nullptr) {
                Customer* nextCustomer = singleQueue->dequeue();
                regToDepart->get_queue_list()->enqueue(nextCustomer);              
                cout << "Queued a customer with free register " << regToDepart->get_ID() << endl;
            }
        }
    }
    
    Register* regClose = registerList->dequeue(ID);
   //Chk if registers even exists
    if (regClose == nullptr) {
        cout << "Error: register " << ID << " is not open" << endl;
        return;
    }
     // Delete the dynamically allocated register if found , since cases when customers are still there are not considered
    cout << "Closed register " << ID << endl;
    delete regClose;  
  
}

bool getInt(stringstream &lineStream, int &iValue) {
  // Reads an int from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  iValue = stoi(command);
  return true;
}

bool getDouble(stringstream &lineStream, double &dvalue) {
  // Reads a double from the command line
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  }
  dvalue = stod(command);
  return true;
}

bool foundMoreArgs(stringstream &lineStream) {
  string command;
  lineStream >> command;
  if (lineStream.fail()) {
    return false;
  } else {
    return true;
  }
}

void calculateStatistics(QueueList* doneListED) {
  //Case for statistics when no customers are done, output everything as 0
    if (doneListED->get_head() == nullptr) {
        cout << "Statistics:" << endl;
        cout << "  Maximum wait time: " << 0<< endl;
        cout << "  Average wait time: " << 0 << endl;
        cout << "  Standard Deviation of wait time: " << 0 << endl;
        return;
    }

    double maxWaitTime = __DBL_MIN__;  
    double sumWaitTime = 0;
    int countCust = 0;

    Customer* currentCustomer = doneListED->get_head();

    //Loop to find avg wait time, max wait time
    while (currentCustomer != nullptr) {
        double waitTime = currentCustomer->get_departureTime() - currentCustomer->get_arrivalTime();
        if (waitTime > maxWaitTime) {
        maxWaitTime = waitTime;
        }        
        sumWaitTime += waitTime;
        countCust++;        
        currentCustomer = currentCustomer->get_next();
    }
    
    double avgWaitTime = sumWaitTime / countCust;

    // Reesetting current customer to head to find squared diff
    double squaredDiff = 0;
    currentCustomer = doneListED->get_head();

    while (currentCustomer != nullptr) {
        double waitTime = currentCustomer->get_departureTime() - currentCustomer->get_arrivalTime();
        double difference = waitTime - avgWaitTime;
        squaredDiff =squaredDiff+ difference * difference;        
        currentCustomer = currentCustomer->get_next();
    }

    
    double stdDev= sqrt(squaredDiff / countCust);
    
   cout << "Statistics:" << endl;
cout << "  Maximum wait time: " << maxWaitTime << endl;
cout << "  Average wait time: " << avgWaitTime << endl;
cout << "  Standard Deviation of wait time: " << stdDev<< endl;
}