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
int validator(char *input_str, char *cor_input_str, int is_there_x_value,
              char *ch_x_value);
int garbage_for_validator(int operation);

int is_good_expression(char *expression);

void number_w_dot(const char *input_str, char *num_in_arr, unsigned int i);
int how_much_dots(char *input_str, unsigned int i);

int is_operation(int operation);
int is_number(int operation);
int is_trigonometry(int operation);

int trigonometry_change(char *input_str, char *cor_input_str, unsigned int *i,
                        unsigned int *j, char *ch_x_value);
void unary(char *input_str, char znak, int *array, unsigned int i,
           int *correct);

double parser(char *input_str);
void parser_operand(const char *input_str, create_stack *output_str,
                    unsigned int *i);
void parser_operation(char *input_str, create_stack *stack,
                      create_stack *output_str, unsigned int i);

double calculation(create_stack *output_str);
void calculation_operation(create_stack *output_str, create_stack *stack_res,
                           unsigned int i);
void calculation_basic_operation(create_stack *output_str,
                                 create_stack *stack_res, unsigned int i,
                                 double num1);
void calculation_math_func_operation(create_stack *output_str,
                                     create_stack *stack_res, unsigned int i,
                                     double num1);

// deposit
double get_total_ac(double *amount, double term, double interest_rate, int mode,
                    int capitalization, double replenishment,
                    double withdrawal);
double get_tax_am(double total, double rate);
double get_total_am(double amount, double accrued, double tax);
#endif /*S21_STRING_H*/