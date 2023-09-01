#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <ctype.h>
// #include <math.h>
// #include <stdarg.h>
// #include <stdint.h>
#define STACK_OVERFLOW 1
#define STACK_UNDERFLOW 2
#define STACK_MAX_SIZE 255
#define INPUT_STR_MAX_SIZE 255

typedef struct {
  int data[STACK_MAX_SIZE];
  // size – это количество элементов, и вместе с тем указатель на вершину стека.
  size_t size;
  int char_or_not;
  int priority[STACK_MAX_SIZE];
} create_stack;

void printStack(create_stack stack);
void push(create_stack *stack, int value);
int pop(create_stack *stack);
int peek(const create_stack *stack);
void priority(create_stack *stack);

#endif /*S21_STRING_H*/