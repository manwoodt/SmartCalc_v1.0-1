#ifndef S21_STRING_H
#define S21_STRING_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void push(create_stack *stack, double value);
double pop(create_stack *stack);
double peek(const create_stack *stack);
void nulldata(create_stack *stack);
int priority(int operation);
int is_good_expression(char *expression);

int validator(const char *input_str, char *cor_input_str, int is_there_x_value,
              int is_x_correct);
int garbage_for_validator(int operation);
int trigonometry_change(const char *input_str, char *cor_input_str,
                        unsigned int *i, unsigned int *j);
void unary(const char *input_str, char znak, int *array, unsigned int i,
           int *correct);
int how_much_dots(const char *input_str, unsigned int i);
void replacement_x(char *cor_input_str, char *cor_input_str_with_x,
                   char *ch_x_value);

int is_operation(int operation);
int is_number(int operation);
int is_trigonometry(int operation);

double parser(char *input_str, char *x_value);
void parser_operand(const char *input_str, create_stack *output_str,
                    unsigned int *i);
void parser_operation(char *input_str, create_stack *stack,
                      create_stack *output_str, unsigned int i);
void number_w_dot(const char *input_str, char *num_in_arr, unsigned int i);

double calculation(create_stack *output_str);
void calculation_operation(create_stack *output_str, create_stack *stack_res,
                           unsigned int i);
void calculation_basic_operation(create_stack *output_str,
                                 create_stack *stack_res, unsigned int i,
                                 double num1);
void calculation_math_func_operation(create_stack *output_str,
                                     create_stack *stack_res, unsigned int i,
                                     double num1);

// credit
int calculateAnnuity(double loanAmount, int term, double interestRate,
                     double *monthlyPayment, double *totalPayment,
                     double *overpayment);
int calculateDifferentiated(double loanAmount, int term, double interestRate,
                            double *monthlyPayment, double *totalPayment,
                            double *overpayment);

// deposit
double get_total_ac(double *amount, double term, double interest_rate,
                    int period_of_pay_y, int capitalization,
                    double replenishment, double withdrawal, double tax_rate);
double get_tax_am(double total, double rate);
double get_total_am(double amount, double accrued, double tax);
#endif /*S21_STRING_H*/