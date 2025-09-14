#include "QueueList.h"

#include "Customer.h"

QueueList::QueueList() { head = nullptr; }

QueueList::QueueList(Customer* customer) { head = customer; }

QueueList::~QueueList() {
  delete head;
}

Customer* QueueList::get_head() { 
  return head;
 }

void QueueList::enqueue(Customer* customer) {
  // a customer is placed at the end of the queue
  // if the queue is empty, the customer becomes the head  
  if(head==nullptr){
  head=customer;
  }
  else{
    Customer*p=head;
    while(p->get_next()!=NULL){
      p =p->get_next();      
    }
    p-> set_next(customer);
  }  
}

Customer* QueueList::dequeue() {
  // remove a customer from the head of the queue 
  // and return a pointer to it
  if(head==nullptr){
    return nullptr;
  }
  Customer*p=head;
  head=p->get_next();
  p->set_next(nullptr);
  //No longer connected to the remaining customers
  return p;
  
}
int QueueList::get_items() {
  // count total number of items each customer in the queue has
  int sum=0;
  Customer*p=head;
  if(p==nullptr){
    return 0;
  }
  while(p!=NULL){
  sum= sum+p->get_numOfItems();
  p =p->get_next();      
  }
  return sum;

}

void QueueList::print() {
  // print customers in a queue
  Customer* temp = head;
  while (temp != nullptr) {
    temp->print();
    temp = temp->get_next();
  }
}
