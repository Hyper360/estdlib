
#define E_LIST_IMPLEMENTATION
#include "elist.h"
#include "stdio.h"

int main(){
    eList list;
    elist_create(&list, sizeof(int)); // Creating a list 

    for (int i = 5; i < 9; ++i){
        elist_add(&list, &i); // Adding items
    }

    elist_remove(&list, 2); // Removing the second item

    printf("First Item: %i\n", *(int*)elist_get(&list, 0)); // Getting the first item

    elist_clear(&list); // Clearing the list

    for (int i = 9; i < 15; ++i){
        elist_add(&list, &i); // Adding items to a list
    }
    
    int num = 2048;
    elist_replace(&list, &num, 0); // Inserting a number to the first index
    printf("First Item: %i\n", *(int*)elist_get(&list, 0));

    size_t s = list.size;
    for (size_t i = 0; i < s; ++i){
        printf("%i\n", *(int*)elist_get(&list, i)); // Getting items from the list
    }

    elist_delete(&list); // Deallocating the list
    printf("List deleted!!!\n");
}