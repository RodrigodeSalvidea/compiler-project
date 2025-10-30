#include "./stateStack.h"
/*
 *
 *
*
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
}
typedef struct S_state_stack StateStack;

int pop(StateStack stack);
int push(StateStack stack);





#endif
 *
 */
void initialize_stateStack(StateStack *stack ){
  stack -> list = (int*) malloc(sizeof(int) * DEFAULT_STACK_SIZE);
  stack -> head = stack ->list;
  stack -> limit = stack -> list + DEFAULT_STACK_SIZE;
  stack -> size = DEFAULT_STACK_SIZE;
  push(stack, 0);
}
void delete_stateStack(StateStack *stack){
 free(stack ->list);

}


int pop(StateStack *stack){
	int x = *(stack -> head);
	if ((stack -> head) == (stack ->list)){return x;}
	stack -> head--;
	return x;
}
int push(StateStack *stack, int s){
  
  void resize(StateStack *stack){
	unsigned int newSize = stack -> size * 2;
	int *newList = (int *) malloc(sizeof(int) * newSize);
	if (newList == 0){exit(1);}
	for(int i = 0; i < (stack -> size); i++){
	  newList[i] = (stack -> list[i]);
	}
	int *newHead = ((stack -> head) - (stack -> list) + newList);
	int *newLimit = (newList + newSize);
	free(stack -> list);
	stack -> limit = newLimit;
	stack -> head = newHead;
	stack -> list = newList;
	stack -> size = newSize;
  }
  stack -> head++;
  if (stack -> head == stack -> limit){resize( stack );}
  *(stack -> head) = s;
  return 0;
	


}
void clear(StateStack *stack){
  stack -> head = stack -> list;
  push(stack, 0);
}

