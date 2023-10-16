#include "calc.h"

// 0 - все ок, 1 - неверный ввод, 2 - ошибка со скобками, 3 - ошибка с вводом x,
// 4 - отсутствует число/значение x, 5 - отсутствует операция
int validator(const char *input_str, char *cor_input_str, int is_there_x_value,
              int is_x_correct) {
  int correct = 0, is_left_bracket = 0, is_right_bracket = 0, number_flag = 0,
      operation_flag = 0;
  int unar_minus[255] = {0}, unar_plus[255] = {0};

  for (unsigned int i = 0, j = 0; i < strlen(input_str); i++) {
    if (garbage_for_validator(input_str[i])) return 1;

    if ((input_str[i]) == '(') is_left_bracket++;
    if ((input_str[i]) == ')') is_right_bracket++;
    if (input_str[i] == '(' && input_str[i + 1] == ')') return 2;
    if (is_right_bracket > is_left_bracket) return 2;

    if (is_x_correct == 0) return 3;

    unary(input_str, '+', unar_plus, i, &correct);
    unary(input_str, '-', unar_minus, i, &correct);
    // переименовать функции на мат. функции
    int res = is_trigonometry(input_str[i]);
    if (res) {
      if (trigonometry_change(input_str, cor_input_str, &i, &j)) correct = 1;
    } else {
      if ((unar_minus[i] && unar_minus[i + 1]) || unar_plus[i]) {
        i++;
      }
      if (unar_minus[i]) {
        cor_input_str[j] = '~';
        j++;
      } else {
        cor_input_str[j] = input_str[i];
        j++;
      }
    }
    if (is_number(input_str[i]) || is_there_x_value) {
      if (!is_number(input_str[i + 1])) number_flag++;
      // точки
      if (how_much_dots(input_str, i) > 1) return 1;
    }
    if (is_operation(cor_input_str[i])) operation_flag++;
    if (cor_input_str[i] == '~') operation_flag--;
  }
  // if (operation_flag == 0) return 5;
  if (is_left_bracket != is_right_bracket) return 2;
  if (operation_flag >= number_flag) return 4;
  if (number_flag == 0) return 4;
  return correct;
}

void unary(const char *input_str, char znak, int *array, unsigned int i,
           int *correct) {
  if (input_str[0] == znak) array[0] = 1;
  if (is_operation(input_str[i] || is_trigonometry(input_str[i])) &&
      input_str[i + 1] == znak)
    array[i + 1] = 1;
  if (input_str[i] == '(' && input_str[i + 1] == znak) array[i + 1] = 1;
  if (input_str[i] == znak && input_str[i + 1] == '(') array[i] = 1;
  if (input_str[i] == znak && is_trigonometry(input_str[i + 1])) *correct = 1;
}

int how_much_dots(const char *input_str, unsigned int i) {
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
int trigonometry_change(const char *input_str, char *cor_input_str,
                        unsigned int *i, unsigned int *j) {
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