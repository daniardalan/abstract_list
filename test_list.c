#include<stdio.h>
#include<stdlib.h>
#include "list.h"

#define N 8

typedef struct pair_{
    int x;
    int y;
} Pair;

char* pair2str(void *data);
int pair_destroy(void *data);
Pair* newPair(int x, int y);
int equal(void *data1, void *data2);

int main(int argc, char **argv){
    int i,k;
    Pair *p1, *p2;

    List *list = malloc(sizeof(List));
    list_init(list, pair_destroy, pair2str, equal);
    
    list_append(list, newPair(1,1));
    list_prepend(list, newPair(-6,-6));
    
    printf("Append of (1,1), Prepend of (-6,-6):\n");
    list_print(list);

    for (i=0; i<N; ++i){
        list_add(list, i, newPair(i/3, i));
    }
    
    printf("Add (i/3,i) at index i:\n");
    list_print(list);

    list_add(list, 50, newPair(10,10)); /* try to add past end of list */
    printf("Add (10,10) past end of list:\n");
    list_print(list);

    list_add(list, 3, newPair(-1,-1));
    printf("Add (-1,-1) at index 3:\n");
    list_print(list);

    p1 = (Pair *) list_element_at(list, 3);
    printf("Value of element 3: %s\n", pair2str(p1));

    p2 = newPair(-1,-1);
    k = list_find_first(list, p2);
    printf("Index of first pair equal to (-1,-1): %d\n", k);
    
    list_remove(list, 3);
    printf("Remove element at index 3:\n");
    list_print(list);
    
    list_remove(list, 0);
    printf("Remove first element in list:\n");
    list_print(list);

    list_remove(list, 50); /* past end of list */
    list_remove(list, 9);
    printf("Remove last element in list:\n");
    list_print(list);

    list_destroy(list);
    pair_destroy(p2);

    return 0;
}

/* Print a pair as a string */
char* pair2str(void *data){
    static char str[10];
    Pair *p = (Pair *) data;
    sprintf(str, "[%d,%d]", p->x, p->y);
    return str;
}
/* Destroy a pair */
int pair_destroy(void *data){
    Pair *p = (Pair *) data;
    free(p);
    return 0;
}
/* Create a new pair */
Pair* newPair(int x, int y){
    Pair *p = malloc(sizeof(Pair));
    p->x = x; p->y = y;
    return p;
}
/* Determine whether two pairs are equal */
int equal(void *data1, void *data2){
    Pair *p1 = (Pair *) data1;
    Pair *p2 = (Pair *) data2;
    if (p1->x == p2->x && p1->y == p2->y){
        return 1;
    }
    else{
        return 0;
    }
}