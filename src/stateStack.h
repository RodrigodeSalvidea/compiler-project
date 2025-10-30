#include "../include/logging.h"
#include <stdlib.h>
#include "./scanner.h"


#ifndef STATE_STACK_DEFINITIONS
#define STATE_STACK_DEFINITIONS

struct S_state_stack{
        int *limit;
        int *head;
        int *list;
        unsigned int size;
};
typedef struct S_state_stack StateStack;
void delete_stateStack(StateStack *stack);
void clear(StateStack *stack);
int pop(StateStack *stack);
int push(StateStack *stack, int s);
void initialize_stateStack(StateStack *stack);
#define DEFAULT_STACK_SIZE 0x100

#endif

