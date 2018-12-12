#include "Stack.h"



bool StackOk(const Stack* stk)
{
    elem_type sum = 0;
    for(unsigned int i = 0; i < stk->size_stack; i++)
    {
        sum += stk->array_stack[i];
    }
    return stk && (0 <= stk->size_stack &&
                   stk->size_stack <= stk->memory_size) &&
                   stk->array_stack &&
                   stk->start_canary == CANARY_CONST &&
                   stk->end_canary == CANARY_CONST &&
                   stk->control_sum == sum;
}

void StackDump(const Stack* stk, const char* err_info)
{
    FILE* log = fopen(LOG_FILE, "a");

    fprintf(log, "Stack \"stk\": 0x%p\n", stk);
    fprintf(log, "%s\n", err_info);
    fprintf(log, "size = %d, memory = %d, array = 0x%p\n",
             stk->size_stack, stk->memory_size, stk->array_stack);
    printf("%d", stk->size_stack);

    for (unsigned int i = 0; i < stk->size_stack; i++)
    {
        fprintf(log, "array[%d] = %d\n", i, stk->array_stack[i]);
    }
    fclose(log);
}

void Stack_init(Stack* stack_test)
{
    stack_test->start_canary = CANARY_CONST;
    stack_test->size_stack = 0;
    stack_test->memory_size = START_MEM_SIZE;
    stack_test->array_stack = (
                elem_type*)calloc(stack_test->memory_size, sizeof(elem_type));
    stack_test->control_sum = 0;
    stack_test->end_canary = CANARY_CONST;

    if(!StackOk(stack_test))
    {
        StackDump(stack_test, "ERROR in end of stack_init");
        assert(!"stack_init");
    }
}

void push(Stack* our_stack, elem_type pushing_elem)
{
    if(!StackOk(our_stack))
    {
        StackDump(our_stack, "ERROR in start of push");
        assert(!"push");
    }
    if(our_stack->size_stack > our_stack->memory_size)
    {
        std::cout << "ERROR with size of stack and memory";
    }

    if(our_stack->size_stack == our_stack->memory_size)
    {
        our_stack->memory_size *= 2;
        our_stack->array_stack = (elem_type*)realloc(
                            our_stack->array_stack,
                            our_stack->memory_size * sizeof(elem_type));
        assert(our_stack->array_stack);
    }

    our_stack->size_stack++;
    our_stack->array_stack[our_stack->size_stack - 1] = pushing_elem;
    our_stack->control_sum += pushing_elem;

    if(!StackOk(our_stack))
    {
        StackDump(our_stack, "ERROR in end of push");
        assert(!"push");
    }
}

elem_type pop(Stack* our_stack)
{
    if(!StackOk(our_stack))
    {
        StackDump(our_stack, "ERROR in start of pop");
        assert(!"pop");
    }

    if(our_stack->size_stack == 0)
    {
        StackDump(our_stack, "ERROR: pop from empty stack");
        assert(!"pop");
    }

    elem_type result = our_stack->
        array_stack[our_stack->size_stack-1];
    our_stack->control_sum -= result;
    our_stack->size_stack--;

    if(!StackOk(our_stack))
    {
        StackDump(our_stack, "ERROR in end of pop");
        assert(!"pop");
    }
    return result;
}

void delete_Stack(Stack* our_stack)
{
    if(!StackOk(our_stack))
    {
        StackDump(our_stack, "ERROR in start of delete_stack");
        assert(!"delete_stack");
    }

    for(unsigned int i = 0; i < our_stack->memory_size; i++)
    {
        our_stack->array_stack[i] = CONST_FOR_FREE_MEM;
    }
    free(our_stack->array_stack);
    our_stack->size_stack = 0;
}
