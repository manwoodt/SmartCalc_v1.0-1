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
    if ((input_str[i]) == ' ') correct = 0;

    // мат функции
    res = is_trigonometry(input_str[i]);
    if (res) {
      if (trigonometry_change(input_str, cor_input_str, &i, &j)) correct = 0;
    } else {
      cor_input_str[j] = input_str[i];
      j++;
    }
    // точки
    if (is_number(input_str[i])) {
      number_flag = 1;
      if (how_much_dots(input_str, i) > 1) correct = 0;
    }
  }

  // неравное количество скобок
  if (is_left_bracket != is_right_bracket) correct = 0;

  if (!number_flag) correct = 0;
  return correct;
}

int how_much_dots(char *input_str, unsigned int i) {
  int count_of_dots = 0;
  char *num_in_arr = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  number_w_dot(input_str, num_in_arr, i);
  for (unsigned int k = 0; k < strlen(num_in_arr); k++) {
    if (num_in_arr[k] == '.') count_of_dots++;
  }
  free(num_in_arr);
  return count_of_dots;
}

// cos - c, sin - s, tan - t, log - l, ln - n, sqrt - q, acos - o, asin - i,
// atan - a
int trigonometry_change(char *input_str, char *cor_input_str, unsigned int *i,
                        unsigned int *j) {
  // cos
  if ((input_str[*i]) == 'c' && input_str[*i + 1] == 'o' &&
      input_str[*i + 2] == 's' && input_str[*i + 3] == '(') {
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
  } else if ((input_str[*i]) == 'a' && input_str[*i + 1] == 'c' &&
             input_str[*i + 2] == 'o' && input_str[*i + 3] == 's' &&
             input_str[*i + 4] == '(') {
    cor_input_str[*j] = 'o';
    *i += 3;
  } else if ((input_str[*i]) == 'a' && input_str[*i + 1] == 's' &&
             input_str[*i + 2] == 'i' && input_str[*i + 3] == 'n' &&
             input_str[*i + 4] == '(') {
    cor_input_str[*j] = 'i';
    *i += 3;
  } else if ((input_str[*i]) == 'a' && input_str[*i + 1] == 't' &&
             input_str[*i + 2] == 'a' && input_str[*i + 3] == 'n' &&
             input_str[*i + 4] == '(') {
    cor_input_str[*j] = 'a';
    *i += 3;
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
             input_str[*i + 4] == '(') {
    cor_input_str[*j] = 'q';
    *i += 3;
  } else {
    return 1;
  }
  (*j)++;
  return 0;
}