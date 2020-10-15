# abstract_list

## Running the Code 

Run the make file and then run ```./test``` for the test of the abstract list implementation. This will print instances of the list after performing all the available opperations. 

## Files Included
* abstract_list.c: The generalized list for any type 
* test_list.c: Code for testing the abstract list 
* list.h: the header file for the abstract list

## Functions Available in the List Implementation
* list_init(list, destroy, tostr, equal)
* list_print(list)
* list_add(list, index, data)
* list_append(list, data)
* list_prepend(list, data)
* list_destroy(list)
* list_remove(list, index)
* list_element_at(list, index) 
* list_find_first(list, data)