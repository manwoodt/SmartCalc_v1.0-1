
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
  char *lex_oper = calloc(255, sizeof(char));
  // char *output_str = calloc(255, sizeof(char));
  // переделываем выражение из  классического в польскую нотацию
  scanf("%s", input_str);
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    if (input_str[i] >= '0' && input_str[i] <= '9') {
      lex_num[i] = input_str[i];
    } else if (input_str[i] >= '(' && input_str[i] <= '/') {
      lex_oper[i] = input_str[i];
    }
  }
  // printf("%s", input_str);
  printf("%s", lex_num);
  printf("%s", lex_oper);
  // переделываем выражение из польской нотации в обратную польскую нотацию

  free(input_str);
  free(lex_num);
  free(lex_oper);

  return 0;
}