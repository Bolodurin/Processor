#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define START_MEM_SIZE     8
#define LOG_FILE           "results.txt"
#define CANARY_CONST       0xBEDAEDAA
#define CONST_FOR_FREE_MEM 0xEA

typedef int elem_type;

typedef struct Stack
{
    unsigned int start_canary;
    unsigned int size_stack;
    unsigned int memory_size;
    elem_type* array_stack;
    elem_type control_sum;
    unsigned int end_canary;
}Stack;

/*!
    Function for verification stack
*/
bool StackOk(const Stack* stk);

/*!
    Function for writing info about stack in file
*/
void StackDump(const Stack* stk, const char* err_info);

/*!
    Function for creating elements of stack

    @param stack_test - stack for initialization
*/
void Stack_init(Stack* stack_test);

/*!
    Function for pushing element in stack

    @param stack_test - stack for pushing
    @param pushing_elem - element, which need pushing
*/
void push(Stack* our_stack, elem_type pushing_elem);

/*!
    Function for taking element from stack

    @param stack_test - stack from taking

    @return Last element of stack
*/
elem_type pop(Stack* our_stack);

/*!
    Function for deleting elements of stack

    @param stack_test - stack for deleting
*/
void delete_Stack(Stack* our_stack);
