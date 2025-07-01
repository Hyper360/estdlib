
#define E_STACK_IMPLEMENTATION
#include "estack.h"
#include "stdio.h"

int main(){
    eStack stack;
    estack_create(&stack, sizeof(int)); // Creating a stack 

    for (int i = 5; i < 9; ++i){
        estack_add(&stack, &i); // Adding items
    }

    estack_remove(&stack); // Removing an item
    
    printf("Popped Item: %i\n", *(int*)estack_pop(&stack)); // Popping the top item

    printf("Top Item: %i\n", *(int*)estack_get(&stack)); // Getting the top item

    estack_clear(&stack); // Clearing the stack

    for (int i = 9; i < 15; ++i){
        estack_add(&stack, &i); // Adding items
    }

    size_t s = stack.size;
    for (size_t i = 0; i < s; ++i){
        printf("Popped Item After Clear: %i\n", *(int*)estack_pop(&stack)); // Popping the tp item and displaying it
    }

    estack_delete(&stack); // Deallocating the stack
    printf("Stack deleted!!!");
}