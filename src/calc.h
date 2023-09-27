#ifndef S21_STRING_H
#define S21_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// #include <ctype.h>
#include <math.h>
// #include <stdarg.h>
// #include <stdint.h>
#define STACK_OVERFLOW 1
#define STACK_UNDERFLOW 2
#define STACK_MAX_SIZE 255
#define INPUT_STR_MAX_SIZE 255

typedef struct {
  int data[STACK_MAX_SIZE];
  char operation[STACK_MAX_SIZE];
  // size – это количество элементов, и вместе с тем указатель на вершину стека.
  size_t size;
  int char_or_not[STACK_MAX_SIZE];
  int priority[STACK_MAX_SIZE];
} create_stack;

void printStack(create_stack stack);
void push(create_stack *stack, int value);
int pop(create_stack *stack);
int peek(const create_stack *stack);
void nulldata(create_stack *stack);
int priority(int operation);
int isoperation(int operation);
int validator(char *input_str);
int garbage_for_validator(int operation);

int is_number(int operation);

double parser(char *input_str);
void parser_operand(const char *input_str, create_stack *output_str,
                    long unsigned int *i);
void parser_operation(char *input_str, create_stack *stack,
                      create_stack *output_str, long unsigned int i);

double calculation(create_stack *output_str);
#endif /*S21_STRING_H*/