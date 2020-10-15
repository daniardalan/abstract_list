#include<stdio.h>
#include<stdlib.h>
#include "list.h"

/* List Init */

void list_init(List *list,
  int (*des)(void *data),
  char* (*tostr)(void *data),
  int (*equal)(void *data1, void *data2)){
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    list->destroy = des; /* Function to destroy an element of the list */
    list->tostr = tostr; /* Function to format an element of the list as a string */
    list->equal = equal; /* Function to determine whether or not elements of the list is equal*/
    }

/* Print the full list */
void list_print(List *list){
  ListElmt *node = list->head;
  printf("[ ");
  while (node != NULL){
    printf("%s ", list->tostr(node->data));
    node=node->next;
  }
  printf("]\n");
}

/* Insert an element at a given index (0 indexed) */
void list_add(List *list, int index, void *data){
  ListElmt *node, *new;
  int count;
  
  if (list->size < index + 1){
    printf("Index value %d past end of list: appending\n", index);
    list_append(list, data);
    return;
  } 

  if (index == 0){
    list_prepend(list, data);
    return;
  }
  
  for (count = 0, node = list->head; node != NULL; node = node->next, ++count){
    if (count == index){
      break;
      }
  }
    /* Insert the new element before the node currently at index */
    new = malloc(sizeof(ListElmt));
    new->data = data;
    new->prev = node->prev;
    new->next = node;
    node->prev->next = new;
    node->prev = new;

    ++list->size;
}

/* Add element to the end of the list */
void list_append(List *list, void *data){
  ListElmt *new, *prev;

  prev = list->tail;
  new = malloc(sizeof(ListElmt));
  new->data = data;
  new->next = NULL;
  list->tail = new;

  /* If appending to empty list */
  if (list->head == NULL){
    list->head = new;
    new->prev = NULL;
  }
  else{
    new->prev=prev;
    prev->next = new;
  }

  ++list->size;
}

/* Add element to the beginning of the list */
void list_prepend(List *list, void *data){
  ListElmt *new, *next;

  next = list->head;
  new = malloc(sizeof(ListElmt));
  new->data = data;
  list->head = new;
  new->prev = NULL;
  new->next = next;

  if (next != NULL){
    next->prev = new;
  }

  /* If prepending to empty list */
  if(next == NULL){
    list->tail = new;
  }

  ++list->size;
}



/* Free all the elements of the list and the list itself */
void list_destroy(List *list){
  while(list->size > 0){
    list_remove(list, 0);
  }
  free(list);
}

/* Remove the list element at a given index */
void list_remove(List *list, int index){
  ListElmt *node;
  int count;

  if (list->size < index + 1){
    printf("Index value %d past end of list \n", index);
    return;
  } 

  for (count = 0, node = list->head; node != NULL; node = node->next, ++count){
    if (count == index){
      break;
    }
  }

  if(list->size > 1){
    /* if first element */
    if(node->prev == NULL){
      node->next->prev = NULL;
      list->head = node->next;
    }
    /* if last element */
    else if(node->next == NULL){
      node->prev->next = NULL;
      list->tail = node->prev;
    }
    /* middle of list */
    else{
      node->next->prev = node->prev;
      node->prev->next = node->next;
    }
  }

  list->destroy(node->data);
  free(node);
  --list->size; 
}

/* Find the element at a given index */
void* list_element_at(List *list, int index){
  ListElmt *node;
  int count;

  for (count = 0, node = list->head; node != NULL; node = node->next, ++count){
    if (count == index){
      return node->data;
    }
  }
  return NULL;
}

/* Find the first instance of a given element */
int list_find_first(List *list, void *data){
  ListElmt *node;
  int count;

  for (count = 0, node = list->head; node != NULL; node = node->next, ++count){
    if (list->equal(data, node->data) == 1){
      return count;
    }
  }
  return -1; 
}