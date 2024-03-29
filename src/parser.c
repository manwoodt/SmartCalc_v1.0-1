#include "calc.h"

double parser(char *input_str, char *x_value) {
  create_stack output_str = {0};
  create_stack stack = {0};
  char *cor_input_str_with_x = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  replacement_x(input_str, cor_input_str_with_x, x_value);
  for (unsigned int i = 0; i < strlen(cor_input_str_with_x); i++) {
    if (cor_input_str_with_x[i] == '(') {
      push(&stack, cor_input_str_with_x[i]);
    }
    if (cor_input_str_with_x[i] == ')') {
      while (peek(&stack) != '(') {
        output_str.operation[output_str.size] = pop(&stack);
        output_str.priority[output_str.size] = stack.priority[stack.size];
        output_str.char_or_not[output_str.size] = 1;
        output_str.size++;
      }
      nulldata(&stack);
    }
    // операнды
    if (is_number(cor_input_str_with_x[i])) {
      parser_operand(cor_input_str_with_x, &output_str, &i);
      // операции
    } else if (is_operation(cor_input_str_with_x[i]) ||
               is_trigonometry(cor_input_str_with_x[i])) {
      parser_operation(cor_input_str_with_x, &stack, &output_str, i);
    }
  }

  while (stack.size != 0) {
    output_str.operation[output_str.size] = pop(&stack);
    output_str.priority[output_str.size] = stack.priority[stack.size];
    output_str.char_or_not[output_str.size] = 1;
    output_str.size++;
  }
  free(cor_input_str_with_x);
  return calculation(&output_str);
}

void replacement_x(char *cor_input_str, char *cor_input_str_with_x,
                   char *ch_x_value) {
  for (unsigned int i = 0; i < strlen(ch_x_value); i++) {
    if (ch_x_value[i] == '-') ch_x_value[i] = '~';
  }
  for (unsigned int i = 0, j = 0; i < strlen(cor_input_str); i++) {
    if (cor_input_str[i] == 'x') {
      strcat(cor_input_str_with_x, ch_x_value);
      printf("STR:%s\n", cor_input_str);
      int length = strlen(ch_x_value);
      j += length;
    } else {
      cor_input_str_with_x[j] = cor_input_str[i];
      j++;
    }
  }
}

void parser_operation(char *input_str, create_stack *stack,
                      create_stack *output_str, unsigned int i) {
  if (stack->size == 0) {
    push(stack, input_str[i]);
  } else {
    int diff_priority =
        priority(input_str[i]) - stack->priority[stack->size - 1];
    // больше 0 = текущее число имеет больший приоритет чем последнее
    // число в стеке
    if (diff_priority > 0) {
      push(stack, input_str[i]);
    } else {
      while (stack->size != 0 && peek(stack) != '(' && diff_priority <= 0) {
        output_str->operation[output_str->size] = pop(stack);
        output_str->char_or_not[output_str->size] = 1;
        output_str->priority[output_str->size] =
            priority(output_str->operation[output_str->size]);

        output_str->size++;
        diff_priority =
            priority(input_str[i]) - stack->priority[stack->size - 1];
      }
      // текущая операция, которая не вошла в стек
      if (input_str[i] != ')') {
        push(stack, input_str[i]);
      }
    }
  }
}

void parser_operand(const char *input_str, create_stack *output_str,
                    unsigned int *i) {
  char *num_in_arr = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  number_w_dot(input_str, num_in_arr, *i);
  *i += (strlen(num_in_arr) - 1);
  output_str->data[output_str->size] = atof(num_in_arr);
  output_str->size++;
  free(num_in_arr);
}

void number_w_dot(const char *input_str, char *num_in_arr, unsigned int i) {
  int lex_num_index = 0;
  num_in_arr[lex_num_index] = input_str[i];
  lex_num_index++;
  // смотрим следующее символ - цифра, если да, добавляем в массив числа
  while (is_number(input_str[i + 1]) || input_str[i + 1] == '.') {
    i++;
    num_in_arr[lex_num_index] = input_str[i];
    lex_num_index++;
  }
}