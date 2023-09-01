
#include "calc.h"

int main() {
  create_stack stack = {0};
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *lex_num = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *stek = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *output_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  // переделываем выражение из  классического в обратную польскую нотацию
  // scanf("%s", input_str);
  strcpy(input_str, "5465+6344");
  int lex_num_index = 0;
  int stek_index = 0;
  int num = 0;
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
      num = atoi(lex_num);
      stack.data[stack.size] = num;
      stack.size++;
      num = 0;
      memset(lex_num, '0', strlen(lex_num));
      lex_num_index = 0;
      // операции
    } else if (input_str[i] >= '(' && input_str[i] <= '/') {
      stek[stek_index] = input_str[i];
      stek_index++;
    }
  }
  printf("final output: %s\n", output_str);
  printf("final lex_num: %s\n", lex_num);
  printf("final stek: %s\n", stek);
  printStack(stack);
  free(input_str);
  free(lex_num);
  free(stek);

  return 0;
}