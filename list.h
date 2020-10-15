typedef struct ListElmt_{
    void *data;
    struct ListElmt_ *prev;
    struct ListElmt_ *next;
} ListElmt;

typedef struct List_{
    int size;
    int (*destroy)(void *data); /* Function to destroy an element of the list */
    char* (*tostr)(void *data); /* Function to format an element of the list as a string */
    int (*equal)(void *data1, void *data2); /* Function to determine whether or not elements of the list is equal*/
    ListElmt *head;
    ListElmt *tail;
} List;

void list_init(List *list,
                int (*destroy)(void *data), 
                char* (*tostr)(void *data), 
                int (*equal)(void *data1, void *data2) 
                );
void list_print(List *list);
void list_add(List *list, int index, void *data);
void list_append(List *list, void *data);
void list_prepend(List *list, void *data);
void list_destroy(List *list);
void list_remove(List *list, int index);
void* list_element_at(List *list, int index);
int list_find_first(List *list, void *data);