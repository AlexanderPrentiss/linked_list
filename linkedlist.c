#include<stdio.h>
#include<stdlib.h>

#ifndef assert
#define assert(expr,m)     (expr ? 0:(printf("%s\n",m), exit(-1)))
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
// TODO: add_node creates nodes instead of being given nodes to insert
// add_node appends a node object to the node list attribute
void add_node(LinkedList_T* list, Node_T* node){
  if (list->head == NULL) {     // if the list is empty make the current node the head
    list->head = node;
    list->size = 1;
  } else {                      // if the list is not empty find the end and append node
    Node_T* cur = list->head;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    set_next(cur, node);
    list->size++;
  }
}

//get_node returns the node of a specified value
Node_T* get_node(LinkedList_T* list,int data) {
  if (list->size <= 0) {            // if the list is empty it's probably not there
    printf("Item not in list\n");
    return NULL;
  } else {                          // if it isn't empty loop through the list to check
    Node_T* cur = list->head;
    while (cur->next != NULL) {
      if (cur->data == data) return cur; // found!
      cur = cur->next;
    }
  }
  return NULL;                      // still not there 
}

// destroy_list frees each node object's memory, then frees the list
void destroy_list(LinkedList_T* list) {
  Node_T* cur = list->head;
  Node_T* to_free;
  while (cur != NULL) {
    to_free = cur;
    cur = cur->next;
    free(to_free);
  }
  free(cur);
  free(list);
}

// test checks the functionality of the list
void test(){
  Node_T* node1 = (Node_T*) malloc(sizeof(Node_T));
  Node_T* node2 = (Node_T*) malloc(sizeof(Node_T));
  Node_T* node3 = (Node_T*) malloc(sizeof(Node_T));
  Node_T* node4 = (Node_T*) malloc(sizeof(Node_T));
  LinkedList_T* list = (LinkedList_T*) malloc(sizeof(LinkedList_T));

  set_data(node1, 4);
  set_data(node2, 2);
  set_data(node3, 8);
  set_data(node4, 12);

  add_node(list, node1);
  add_node(list, node2);
  add_node(list, node3);
  add_node(list, node4);

  assert(get_node(list, 12) == NULL, "RAISE::EXCEPTION::FOUND::NON-EXISTANT::VALUE");
  assert(get_node(list, 2) == node2, "RAISE::EXCEPTION::NOT-FOUND::EXISTANT::VALUE");
  assert(get_node(list, 4) == list->head, "RAISE::EXCEPTION::UNEXPECTED::HEAD-NODE");
}

int main() {
  test();
  return 0;
}

