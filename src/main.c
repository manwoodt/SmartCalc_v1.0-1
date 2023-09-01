
#include "calc.h"

int main() {
  create_stack output_str = {0};
  create_stack stack = {0};
  stack.char_or_not = 1;
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *lex_num = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  // scanf("%s", input_str);
  strcpy(input_str, "5465+6344-34534");
  int lex_num_index = 0;
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    // операнды
    if (input_str[i] >= '0' && input_str[i] <= '9') {
      lex_num[lex_num_index] = input_str[i];
      lex_num_index++;
      // смотрим следующее символ - цифра, если да, добавляем в массив числа
      while (input_str[i + 1] >= '0' && input_str[i + 1] <= '9') {
        i++;
        lex_num[lex_num_index] = input_str[i];
        lex_num_index++;
      }
      output_str.data[output_str.size] = atoi(lex_num);
      output_str.size++;
      memset(lex_num, '0', strlen(lex_num));
      lex_num_index = 0;
      // операции
    } else if (input_str[i] >= '(' && input_str[i] <= '/') {
      push(&stack, input_str[i]);
    }
  }
  printf("Stack\n");
  printStack(stack);
  printf("Output_str\n");
  printStack(output_str);

  free(input_str);
  free(lex_num);

  return 0;
}