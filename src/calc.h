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
  double data[STACK_MAX_SIZE];
  char operation[STACK_MAX_SIZE];
  // size – это количество элементов, и вместе с тем указатель на вершину стека.
  size_t size;
  int char_or_not[STACK_MAX_SIZE];
  int priority[STACK_MAX_SIZE];
} create_stack;

void printStack(create_stack stack);
void push(create_stack *stack, double value);
double pop(create_stack *stack);
double peek(const create_stack *stack);
void nulldata(create_stack *stack);
int priority(int operation);
int validator(char *input_str, char *cor_input_str);
int garbage_for_validator(int operation);

int is_operation(int operation);
int is_number(int operation);
int is_trigonometry(int operation);

int trigonometry_change(char *input_str, char *cor_input_str, unsigned int *i,
                        unsigned int *j);

double parser(char *input_str);
void parser_operand(const char *input_str, create_stack *output_str,
                    long unsigned int *i);
void parser_operation(char *input_str, create_stack *stack,
                      create_stack *output_str, long unsigned int i);

double calculation(create_stack *output_str);
void calculation_operation(create_stack *output_str, create_stack *stack_res,
                           unsigned int i);
void calculation_basic_operation(create_stack *output_str,
                                 create_stack *stack_res, unsigned int i,
                                 double num1);
void calculation_math_func_operation(create_stack *output_str,
                                     create_stack *stack_res, unsigned int i,
                                     double num1);
#endif /*S21_STRING_H*/