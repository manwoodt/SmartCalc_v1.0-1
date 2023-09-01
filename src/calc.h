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
  int data[255];
  // size – это количество элементов, и вместе с тем указатель на вершину стека.
  size_t size;
} create_stack;

void printStack(const create_stack stack);

#endif /*S21_STRING_H*/