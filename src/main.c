#include "calc.h"

int main() {
  create_stack output_str = {0};
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  // scanf("%s", input_str);
  // strcpy(input_str, "3+5");
  // strcpy(input_str, "cos(3)");
  strcpy(input_str, "log10");
  // strcpy(input_str, "sqrt(100)");
  // strcpy(input_str, "tg(1)");

  // strcpy(input_str, "(42*((43+3-4)/23))^2");
  //  strcpy(input_str, "(43+43-5)/9");
  printf("BEF: %s\n", input_str);
  if (validator(input_str, cor_input_str)) {
    parser(input_str);
    // printf("Output_str\n");
    // printStack(output_str);
    double res = calculation(&output_str);
    printf("res: %f\n", res);
  } else
    printf("ERROR\n");
  printf("AFT: %s\n", cor_input_str);
  free(input_str);
  free(cor_input_str);
  return 0;
}

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

// cos - c, sin - s, tg - t, ctg - g, log - l, ln - n, sqrt - q
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
  } else if ((input_str[*i]) == 't' && input_str[*i + 1] == 'g' &&
             input_str[*i + 3] == '(') {
    cor_input_str[*j] = 't';
    (*i)++;
  } else if ((input_str[*i]) == 'l' && input_str[*i + 1] == 'o' &&
             input_str[*i + 2] == 'g' && is_number(input_str[*i + 3])) {
    cor_input_str[*j] = 'l';
    *i += 2;
  } else if ((input_str[*i]) == 'l' && input_str[*i + 1] == 'n' &&
             is_number(input_str[*i + 2])) {
    cor_input_str[*j] = 'g';
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

double parser(char *input_str) {
  create_stack output_str = {0};
  create_stack stack = {0};
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    // while (input_str[i] == ' ') i++;

    if (input_str[i] == '(') {
      push(&stack, input_str[i]);
    }
    if (input_str[i] == ')') {
      while (peek(&stack) != '(') {
        output_str.operation[output_str.size] = pop(&stack);
        output_str.char_or_not[output_str.size] = 1;
        output_str.size++;
      }
      nulldata(&stack);
    }
    // операнды
    if (is_number(input_str[i])) {
      parser_operand(input_str, &output_str, &i);
      // операции
    } else if (isoperation(input_str[i])) {
      parser_operation(input_str, &stack, &output_str, i);
    }
  }
  // опустошение стека
  while (stack.size != 0) {
    output_str.operation[output_str.size] = pop(&stack);
    output_str.char_or_not[output_str.size] = 1;
    output_str.size++;
  }

  return calculation(&output_str);
}

void parser_operation(char *input_str, create_stack *stack,
                      create_stack *output_str, long unsigned int i) {
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

int priority(int operation) {
  int priority = 0;
  switch (operation) {
    case '+':
      priority = 1;
      break;
    case '-':
      priority = 1;
      break;
    case '*':
      priority = 2;
      break;
    case '/':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case 'c':
      priority = 4;
      break;
    case 's':
      priority = 4;
      break;
    case 't':
      priority = 4;
      break;
    case 'q':
      priority = 4;
      break;
    case 'l':
      priority = 4;
      break;
    case 'n':
      priority = 4;
      break;
    case ')':
      priority = 5;
      break;
    case '(':
      priority = 6;
      break;
    // cos - c, sin - s, tg - t, ctg - g, log - l, ln - n, sqrt - q
    default:
      priority = 0;
      break;
  }
  return priority;
}

double calculation(create_stack *output_str) {
  create_stack stack_res = {0};
  for (long unsigned int i = 0; i < output_str->size; i++) {
    // если число
    if (output_str->char_or_not[i] == 0) {
      push(&stack_res, output_str->data[i]);
    }
    // если операция
    else {
      double num1 = peek(&stack_res);
      nulldata(&stack_res);
      if (output_str->priority[i] == 4) {
        switch (output_str->operation[i]) {
          case 'c':
            push(&stack_res, cos(num1));
            break;
          case 's':
            push(&stack_res, sin(num1));
            break;
          case 't':
            push(&stack_res, tan(num1));
            break;
          case 'l':
            push(&stack_res, log(num1));
            break;
          case 'n':
            push(&stack_res, log10(num1));
            break;
          case 'q':
            push(&stack_res, sqrt(num1));
            break;
          default:
            break;
        }
      } else {
        double num2 = peek(&stack_res);
        nulldata(&stack_res);
        switch (output_str->operation[i]) {
          case '+':
            push(&stack_res, num2 + num1);
            break;
          case '-':
            push(&stack_res, num2 - num1);
            break;
          case '*':
            push(&stack_res, num2 * num1);
            break;
          case '/':
            push(&stack_res, num2 / num1);
            break;
          case '^':
            push(&stack_res, pow(num2, num1));
            break;
          default:
            break;
        }
      }
      // cos - c, sin - s, tg - t, ctg - g, log - l, ln - n, sqrt - q
    }
  }
  return peek(&stack_res);
}

int isoperation(int operation) {
  if (operation == '+' || operation == '-' || operation == '*' ||
      operation == '/' || operation == '^')
    return 1;
  else
    return 0;
}

int garbage_for_validator(int operation) {
  if (operation == '+' || operation == '-' || operation == '*' ||
      operation == '/' || operation == '^' || operation == '(' ||
      operation == ')' || is_number(operation) || is_trigonometry(operation))
    return 0;
  else
    return 1;
}

int is_number(int operation) {
  return (operation >= '0' && operation <= '9') ? 1 : 0;
}

int is_trigonometry(int operation) {
  return (operation == 'c' || operation == 'o' || operation == 's' ||
          operation == 'i' || operation == 'n' || operation == 't' ||
          operation == 'g' || operation == 'l' || operation == 'q' ||
          operation == 'r')
             ? 1
             : 0;
}
