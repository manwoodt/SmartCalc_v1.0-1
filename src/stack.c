#include "calc.h"

void push(create_stack *stack, double value) {
  if (stack->size >= STACK_MAX_SIZE) {
    printf("STACK_OVERFLOW\n");
    exit(STACK_OVERFLOW);
  }
  stack->data[stack->size] = value;
  stack->priority[stack->size] = priority(value);
  stack->size++;
}

double pop(create_stack *stack) {
  if (stack->size == 0) {
    printf("STACK_UNDERFLOW pop\n");
    exit(STACK_UNDERFLOW);
  }
  stack->size--;
  return stack->data[stack->size];
}

double peek(const create_stack *stack) {
  if (stack->size == 0) {
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

// second version

// void printStack(create_stack stack) {
//   printf("stack size: %ulu\n", stack.size);
//   for (long unsigned int i = 0; i < stack.size; i++) {
//     if (stack.char_or_not[i])
//       printf("%c | ", stack.operation[i]);
//     else
//       printf("%f | ", stack.data[i]);
//   }
//   printf("\n\n");
// }