
// #include <ctype.h>
// #include <math.h>
// #include <stdarg.h>
// #include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  char *input_str = calloc(255, sizeof(char));
  char *lex_num = calloc(255, sizeof(char));
  char *stek = calloc(255, sizeof(char));
  char *output_str = calloc(255, sizeof(char));
  // переделываем выражение из  классического в обратную польскую нотацию
  // scanf("%s", input_str);
  strcpy(input_str, "5+6");
  int lex_num_index = 0;
  int stek_index = 0;
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    if (input_str[i] >= '0' && input_str[i] <= '9') {
      lex_num[lex_num_index] = input_str[i];
      lex_num_index++;
      // смотрим следующее символ - цифра, если да, добавляем в массив числа
      while (input_str[i + 1] >= '0' && input_str[i + 1] <= '9') {
        i++;
        lex_num_index++;
        lex_num[i] = input_str[i];
      }
    } else if (input_str[i] >= '(' && input_str[i] <= '/') {
      stek[stek_index] = input_str[i];
      stek_index++;
    }
  }
  printf("%s", output_str);
  printf("final lex_num: %s\n", lex_num);
  printf("final stek: %s", stek);

  free(input_str);
  free(lex_num);
  free(stek);

  return 0;
}