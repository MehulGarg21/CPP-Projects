#ifndef QUEUELIST_HPP
#define QUEUELIST_HPP

#include "Customer.h"
#include "QueueList.h"

class QueueList {
 private:
  Customer* head;

 public:
  QueueList();
  QueueList(Customer* customer);
  ~QueueList();
//These above are constructors
  Customer* get_head();
  //returns the first element/customer of the queue

  int get_items();  // gets the number of items in a queue

  void enqueue(
      Customer* customer);  // insert a customer at the tail of the list
  Customer* dequeue();      // remove a customer from the head of the list

  //There is no tail pointer in the queue so we navigate stuff using the pointer p and go till p->next == NUll;


  void print();  // prints the customers in a queue
};

#endif /* QUEUELIST_HPP */
