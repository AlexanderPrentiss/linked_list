#include<stdio.h>
#include<stdlib.h>

typedef struct node{
  int data;
  struct node* next;
} Node_T;

void set_data(Node_T* node, int num) {
  node->data = num;
}

void set_next(Node_T* node, Node_T* next) {
  node->next = next;
}

typedef struct linkedlist{
  int size;
  Node_T* head;
} LinkedList_T;

void add_node(LinkedList_T* list, Node_T* node){
  if (list->head == NULL) {
    list->head = node;
    list->size = 1;
  } else {
    Node_T* cur = list->head;
    while (cur->next != NULL) {
      cur = cur->next;
    }
    set_next(cur, node);
    list->size++;
    //free(cur);
  }
}

Node_T* get_node(LinkedList_T* list,int data) {
  if (list->size <= 0) {
    printf("Item not in list\n");
    return NULL;
  } else {
    Node_T* cur = list->head;
    while (cur->next != NULL) {
      if (cur->data == data) return cur;
      cur = cur->next;
    }
    //free(cur);
  }
  printf("Item not in list\n");
  return NULL;
}

void destroy_list(LinkedList_T* list) {
  Node_T* cur = list->head;
  Node_T* to_free;
  while (cur != NULL) {
    to_free = cur;
    cur = cur->next;
    //free(to_free);
  }
  free(cur);
}

int main(void){
  Node_T* node1 = (Node_T*) malloc(sizeof(Node_T));
  Node_T* node2 = (Node_T*) malloc(sizeof(Node_T));
  Node_T* node3 = (Node_T*) malloc(sizeof(Node_T));
  LinkedList_T* list = (LinkedList_T*) malloc(sizeof(LinkedList_T));

  set_data(node1, 4);
  set_data(node2, 2);
  set_data(node3, 8);

  add_node(list, node1);
  add_node(list, node2);
  add_node(list, node3);

  printf("Should be NULL: %p\n", get_node(list, 25));
  printf("Should be some pointer: %p\n", get_node(list,2));
  //destroy_list(list);
  return 0;
}
