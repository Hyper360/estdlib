#ifndef E_STACK_H
#define E_STACK_H
#include "string.h"
#include "stdlib.h"
#include "econstants.h"

typedef struct{
    size_t size;
    size_t maxSize;
    size_t objSize;
    // DO NOT MANUALLY EDIT THE "mem" ATTRIBUTE, UNLESS YOU REALLY KNOW WHAT YOU ARE DOING!!!
    void** mem;
}eStack;

// Initializes a new stack. Should only be used once
int estack_create(eStack * stack, size_t objSize);
// Deletes the stack, and the pointers inside the stack
void estack_delete(eStack * list);
// Adds a new item to the top of the stack
int estack_add(eStack * stack, const void * object);
// Returns a pointer to the top item in the stack
void* estack_get(eStack * stack);
// Expands the eStack's allocation by a certain number of objects (NOT BYTES)
int estack_expand(eStack * stack, size_t numOfObjects);
// Removes the top item from the stack and returns a new pointer to it.
void* estack_pop(eStack * stack);
// Removes the top item from the stack and deletes it.
void estack_remove(eStack * stack);
// Clears items from a stack. This function does not free the stack
void estack_clear(eStack * stack);

#ifdef E_STACK_IMPLEMENTATION

int estack_create(eStack * stack, size_t objSize){
    stack->mem = (void**)malloc(sizeof(void*)*ESTD_DEFAULT_SIZE);
    if (stack->mem == NULL) return ESTD_FAILURE;

    for (size_t i = 0; i < ESTD_DEFAULT_SIZE; ++i){
        stack->mem[i] = malloc(objSize);
        if (stack->mem[i] == NULL){
            estack_delete(stack);
            free(stack->mem);
            return ESTD_FAILURE;
        }
        ++stack->size; // Only increased so in case of failure, the stack can be properly deallocated
    }

    stack->size = 0;
    stack->maxSize = ESTD_DEFAULT_SIZE;
    stack->objSize = objSize;
    return ESTD_SUCCESS;
}

void estack_delete(eStack * stack){
    for (size_t i = 0; i < stack->size; ++i){
        free(stack->mem[i]);
    }
    free(stack->mem);

    stack->size = 0;
    stack->maxSize = 0;
    stack->objSize = 0;
    stack->mem = NULL; // Deal with dangling pointer or something
}

int estack_add(eStack * stack, const void * object){
    if (stack->size >= stack->maxSize){
        if (estack_expand(stack, stack->maxSize) == ESTD_FAILURE){ // Expands the stack by the current max size
            return ESTD_FAILURE;
        }
    }
    // Adding the object to the end of the stack
    memcpy(stack->mem[stack->size], object, stack->objSize);
    ++stack->size;
    return ESTD_SUCCESS;
}

void* estack_get(eStack * stack){
    if (stack->size > 0){
        return stack->mem[stack->size-1];
    }
    else{
        return NULL;
    }
}

int estack_expand(eStack * stack, size_t numOfObjects){
    // Creating the new memory block
    void ** newMemBlock = (void**)malloc(sizeof(void*)*(stack->maxSize+numOfObjects)); // Doubles size of array
    if (newMemBlock == NULL) return ESTD_FAILURE;
    for (size_t i = stack->size; i < stack->maxSize+numOfObjects; ++i){
        newMemBlock[i] = malloc(stack->objSize);
        if (newMemBlock[i] == NULL){
            free(newMemBlock);
            return ESTD_FAILURE;
        }
    }

    // Copying values from old block to new block, then deallocating the pointers in the old memory block
    memcpy(newMemBlock, stack->mem, sizeof(void*)*stack->size); // Faster then using memcpy, then freeing the old memory etc...
    free(stack->mem);
    stack->mem = newMemBlock;
    stack->maxSize = stack->maxSize+numOfObjects; // Changing the new maximum size
    newMemBlock = NULL; // Handle the dangling pointer
    return ESTD_SUCCESS;
}

void* estack_pop(eStack * stack){
    if (stack->size > 0){
        void * newMemLocation = malloc(stack->objSize);
        if (newMemLocation == NULL) return NULL;

        memcpy(newMemLocation, stack->mem[stack->size-1], stack->objSize);
        memset(stack->mem[stack->size-1], 0, stack->objSize);
        --stack->size;

        return newMemLocation;
    }
    else{
        return NULL;
    }
}

void estack_remove(eStack * stack){
    if (stack->size > 0){
        memset(stack->mem[stack->size-1], 0, stack->objSize);
        --stack->size;
    }
}

void estack_clear(eStack * stack){
    size_t s = stack->size;
    for (size_t i = 0; i < s; ++i){
        estack_remove(stack);
    }
    stack->size = 0;
}

#endif
#endif