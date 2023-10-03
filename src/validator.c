#include "calc.h"

int validator(char *input_str, char *cor_input_str) {
  int correct = 1;
  int is_left_bracket = 0;
  int is_right_bracket = 0;
  int number_flag = 0;
  int res = 0;
  for (unsigned int i = 0, j = 0; i < strlen(input_str); i++) {
    // 1 этап валидации (проверка на неправильные символы)
    if (garbage_for_validator(input_str[i])) {
      correct = 0;
    }
    // 2 этап валидации (проверка на закрытие/открытие скобок)
    if ((input_str[i]) == '(') {
      is_left_bracket++;
    }
    if ((input_str[i]) == ')') {
      is_right_bracket++;
    }
    // пустые скобки
    if (input_str[i] == '(' && input_str[i + 1] == ')') correct = 0;
    if (is_right_bracket > is_left_bracket) correct = 0;
    if (is_number(input_str[i])) number_flag = 1;
    if ((input_str[i]) == ' ') correct = 0;

    // cos...
    res = is_trigonometry(input_str[i]);
    if (res) {
      if (trigonometry_change(input_str, cor_input_str, &i, &j)) correct = 0;
    } else {
      cor_input_str[j] = input_str[i];
      j++;
    }
  }

  // неравное количество скобок
  if (is_left_bracket != is_right_bracket) correct = 0;

  if (!number_flag) correct = 0;
  return correct;
}

// cos - c, sin - s, tan - t, log - l, ln - n, sqrt - q
int trigonometry_change(char *input_str, char *cor_input_str, unsigned int *i,
                        unsigned int *j) {
  // cos
  if ((input_str[*i]) == 'c' && input_str[*i + 1] == 'o' &&
      input_str[*i + 2] == 's') {
    cor_input_str[*j] = 'c';
    *i += 2;
  } else if ((input_str[*i]) == 's' && input_str[*i + 1] == 'i' &&
             input_str[*i + 2] == 'n' && input_str[*i + 3] == '(') {
    cor_input_str[*j] = 's';
    *i += 2;
  } else if ((input_str[*i]) == 't' && input_str[*i + 1] == 'a' &&
             input_str[*i + 2] == 'n' && input_str[*i + 3] == '(') {
    cor_input_str[*j] = 't';
    *i += 2;
  } else if ((input_str[*i]) == 'l' && input_str[*i + 1] == 'o' &&
             input_str[*i + 2] == 'g' && input_str[*i + 3] == '(') {
    cor_input_str[*j] = 'l';
    *i += 2;
  } else if ((input_str[*i]) == 'l' && input_str[*i + 1] == 'n' &&
             input_str[*i + 2] == '(') {
    cor_input_str[*j] = 'n';
    *i += 1;
  } else if ((input_str[*i]) == 's' && input_str[*i + 1] == 'q' &&
             input_str[*i + 2] == 'r' && input_str[*i + 3] == 't' &&
             input_str[*i + 3] == '(') {
    cor_input_str[*j] = 'q';
    *i += 3;
  } else {
    return 1;
  }
  (*j)++;
  return 0;
}