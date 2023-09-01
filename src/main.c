
#include "calc.h"
void parser(char *input_str, create_stack *output_str, create_stack *stack);
void parser_operand(char *input_str, create_stack *output_str,
                    long unsigned int *i);
int main() {
  // создаем стек и выходную строку
  create_stack output_str = {0};
  create_stack stack = {0};
  stack.char_or_not = 1;
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));

  // scanf("%s", input_str);
  strcpy(input_str, "5465+6344-34534");

  parser(input_str, &output_str, &stack);

  printf("Stack\n");
  printStack(stack);
  printf("Output_str\n");
  printStack(output_str);

  free(input_str);

  return 0;
}

void parser(char *input_str, create_stack *output_str, create_stack *stack) {
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    // операнды
    if (input_str[i] >= '0' && input_str[i] <= '9') {
      parser_operand(input_str, output_str, &i);

      // операции
    } else if (input_str[i] >= '(' && input_str[i] <= '/') {
      push(stack, input_str[i]);
      priority(stack);
    }
  }
}

void parser_operand(char *input_str, create_stack *output_str,
                    long unsigned int *i) {
  char *lex_num = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int lex_num_index = 0;
  lex_num[lex_num_index] = input_str[*i];
  lex_num_index++;
  // смотрим следующее символ - цифра, если да, добавляем в массив числа
  while (input_str[*i + 1] >= '0' && input_str[*i + 1] <= '9') {
    (*i)++;
    lex_num[lex_num_index] = input_str[*i];
    lex_num_index++;
  }
  output_str->data[output_str->size] = atoi(lex_num);
  output_str->size++;
  memset(lex_num, '0', strlen(lex_num));
  free(lex_num);
}

void priority(create_stack *stack) {
  switch (stack->data[stack->size - 1]) {
    case '+':
      stack->priority[stack->size - 1] = 1;
      break;
    case '-':
      stack->priority[stack->size - 1] = 1;
      break;
    case '*':
      stack->priority[stack->size - 1] = 2;
      break;
    case '/':
      stack->priority[stack->size - 1] = 2;
      break;
    case '^':
      stack->priority[stack->size - 1] = 3;
      break;
    case '(':
      stack->priority[stack->size - 1] = 4;
      break;
    case ')':
      stack->priority[stack->size - 1] = 5;
      break;
    default:
      stack->priority[stack->size - 1] = 0;
      break;
  }
}