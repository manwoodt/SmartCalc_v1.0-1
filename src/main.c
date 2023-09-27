#include "calc.h"
/*
int main() {


  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));

  // scanf("%s", input_str);
  strcpy(input_str, "3+5");
  // strcpy(input_str, "(42*((43+3-4)/23))^2");
  // strcpy(input_str, "(43+43-5)/9");

  if (validator(input_str)) {
    parser(input_str, &output_str, &stack);
    // printf("Output_str\n");
    // printStack(output_str);
    int res = calculation(&output_str, &stack_res);
    printf("res: %d", res);
  } else
    printf("ERROR\n");

  free(input_str);

  return 0;
}
*/

/*
 алгоритм преобразующий инфикс в постфикс:

Сканируйте вводимую строку слева направо символ за символом.
Если символ является операндом, поместите его в стек вывода.
Если символ является оператором, а стек оператора пуст, вставьте оператора в
стек операторов. Если стек оператора не пуст, могут быть следующие возможности.
Если приоритет сканируемого оператора больше, чем у самого верхнего оператора
стека операторов, поместите этот оператор в стек операндов. Если приоритет
отсканированного оператора меньше или равен самому верхнему оператору стека
операторов, извлекайте операторы из стека операндов до тех пор, пока мы не
найдем оператор с более низким приоритетом, чем отсканированный символ. Никогда
не выскакивайте ( ‘(‘ ) или ( ‘)’ ), каким бы ни был уровень приоритета
отсканированного символа. Если символ открывает круглую скобку ( ‘(‘ ), вставьте
его в стек оператора. Если символ закрывает круглую скобку ( ‘)’ ), вытаскивайте
операторы из стека операторов, пока мы не найдем открывающую скобку (‘(‘ ).
Теперь извлеките все оставшиеся операторы из стека оператора и вставьте в стек
вывода.
*/

int validator(char *input_str) {
  int correct = 1;
  int is_left_bracket = 0;
  int is_right_bracket = 0;
  int number_flag = 0;
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
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
  }
  // неравное количество скобок
  if (is_left_bracket != is_right_bracket) correct = 0;

  if (!number_flag) correct = 0;
  return correct;
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
    case ')':
      priority = 4;
      break;
    case '(':
      priority = 5;
      break;

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
      operation == ')' || is_number(operation))
    return 0;
  else
    return 1;
}
int is_number(int operation) {
  return (operation >= '0' && operation <= '9') ? 1 : 0;
}