

#include "calc.h"
// положить число в стек
void push(create_stack *stack, int value) {
  if (stack->size >= STACK_MAX_SIZE) {
    exit(STACK_OVERFLOW);
    printf("STACK_OVERFLOW");
  }
  stack->data[stack->size] = value;
  if (stack->char_or_not) {
    stack->priority[stack->size] = priority(value);
  }
  stack->size++;
}

// взять число из стека
int pop(create_stack *stack) {
  if (stack->size == 0) {
    printf("STACK_UNDERFLOW pop");
    exit(STACK_UNDERFLOW);
  }
  stack->size--;
  return stack->data[stack->size];
}

// посмотреть последнее число из стека
int peek(const create_stack *stack) {
  if (stack->size <= 0) {
    printf("STACK_UNDERFLOW peek");
    exit(STACK_UNDERFLOW);
  }
  return stack->data[stack->size - 1];
}

void nulldata(create_stack *stack) {
  if (stack->size == 0) {
    printf("STACK_UNDERFLOW");
    exit(STACK_UNDERFLOW);
  }
  stack->size--;
  stack->data[stack->size] = 0;
  stack->priority[stack->size] = 0;
}
/*
void printStack(create_stack stack) {
  printf("stack size: %ld\n", stack.size);
  for (long unsigned int i = 0; i < stack.size; i++) {
    if (stack.char_or_not) {
      printf("%c | ", stack.data[i]);
      printf("%i | ", stack.priority[i]);
    } else if (isoperation(stack.data[i])) {
      printf("%c | ", stack.data[i]);
    } else
      printf("%d | ", stack.data[i]);
  }
  printf("\n\n");
}
*/

void printStack(create_stack stack) {
  printf("stack size: %ld\n", stack.size);
  for (long unsigned int i = 0; i < stack.size; i++) {
    if (stack.char_or_not[i])
      printf("%c | ", stack.operation[i]);
    else
      printf("%i | ", stack.data[i]);
  }
  printf("\n\n");
}