#include<stdio.h>
#include<stdlib.h>

#ifndef assert
#define assert(expr,m)     (expr ? 0:(printf("%s\n",m), exit(-1))) /* assert checks a expression. If the expression is not true, an error message m is thrown and the program exits on code -1*/
#endif

// Node struct
typedef struct node{
  int data;
  struct node* next;
} Node_T;

// --Node methods--
// set data changes the data attribute
void set_data(Node_T* node, int num) {
  node->data = num;
}

// set_next changes the pointer to next of type node attribute
void set_next(Node_T* node, Node_T* next) {
  node->next = next;
}

// Linked List struct
typedef struct linkedlist{
  int size;
  Node_T* head;
} LinkedList_T;

// --Linked List methods--
// add_node appends a node object to the node list attribute
void add_node(LinkedList_T* list, int data){
  Node_T* new = (Node_T*) malloc(sizeof(Node_T)); // create new node
  set_data(new, data);
  if (list->head == NULL) {     // if the list is empty make the current node the head
    list->head = new;
    list->size = 1;
  } else {                      // if the list is not empty find the end and append node
    Node_T* cur = list->head;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    set_next(cur, new);
    list->size++;
  }
}

//get_node returns the node of a specified value
Node_T* get_node(LinkedList_T* list, int data) {
  if (list->size <= 0) {            // if the list is empty it's probably not there
    printf("Item not in list\n");
    return NULL;
  } else {                          // if it isn't empty loop through the list to check
    Node_T* cur = list->head;
    while (cur != NULL) {
      if (cur->data == data) return cur; // found!
      cur = cur->next;
    }
  }
  return NULL;                      // still not there 
}

// remove_node removes a node of certain value from the list, then returns removed node
Node_T* remove_node(LinkedList_T* list, int data) {
  Node_T* cur = list->head;
  Node_T* prev = (Node_T*) malloc(sizeof(Node_T));
  if (cur->data == data) { // if the node is the head just change the list head pointer
    list->head = cur->next;
    free(cur);
  } else { // if not it's more complicated
    prev = cur; // since the head is not the node we can skip to node #2
    cur = cur->next;
    while (cur != NULL) { 
      if (cur->data == data) {
          prev->next = cur->next; // set the pointer of the previous node to the next node , skip cur
          free(cur); // destroy cur
          return cur; // return the destroyed node
      }
      prev = cur; // move forward in the list
      cur = cur->next;
    }
  }
  return NULL; // not does not exist
}

// destroy_list frees each node object's memory, then frees the list
void destroy_list(LinkedList_T* list) {
  Node_T* cur = list->head;
  Node_T* to_free;
  while (cur != NULL) { // free node until we hit NULL
    to_free = cur;
    cur = cur->next;
    free(to_free);
  }
  free(list);
}

// test checks the functionality of the list
void test(){
  LinkedList_T* list = (LinkedList_T*) malloc(sizeof(LinkedList_T));

  add_node(list, 4);
  add_node(list, 2);
  add_node(list, 8);
  add_node(list, 12);


  // Check insertion & get_node
  assert(get_node(list, 100) == NULL, "RAISE::EXCEPTION::FOUND::NON-EXISTANT::VALUE");
  assert(get_node(list, 2) != NULL, "RAISE::EXCEPTION::NOT-FOUND::EXISTANT::VALUE");
  assert(get_node(list, 4) == list->head, "RAISE::EXCEPTION::UNEXPECTED::HEAD-NODE");
  assert(get_node(list, 8) != NULL, "RAISE::EXCEPTION::NOT-FOUND::EXISTANT::VALUE");
  assert(get_node(list, 12) != NULL, "RAISE::EXCEPTION::NOT-FOUND::EXISTANT::VALUE");

  // Check removeal
  assert(remove_node(list, 2) != NULL, "RAISE::EXCEPTION::REMOVAL::EXISTANT::VALUE::FAILED");
  assert(remove_node(list, 100) == NULL, "RAISE::EXCEPTION::REMOVAL::NON-EXISTANT::VALUE::SUCCEEDED");
  assert(get_node(list, 2) == NULL, "RAISE::EXCEPTION::REMOVED::FOUND");

  destroy_list(list);
}

int main() {
  test();
  return 0;
}

