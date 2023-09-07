#include "calc.h"

int main() {
  // создаем стек и выходную строку
  create_stack output_str = {0};
  create_stack stack = {0};
  stack.char_or_not = 1;
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));

  // scanf("%s", input_str);
  strcpy(input_str, "(1*((2+3-4)/23))^2");

  parser(input_str, &output_str, &stack);

  printf("Stack\n");
  printStack(stack);
  printf("Output_str\n");
  printStack(output_str);

  free(input_str);

  return 0;
}

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

void parser(char *input_str, create_stack *output_str, create_stack *stack) {
  int diff_priority = 0;
  for (long unsigned int i = 0; i < strlen(input_str); i++) {
    if (input_str[i] == '(') {
      push(stack, input_str[i]);
    }
    if (input_str[i] == ')') {
      while (peek(stack) != '(') {
        output_str->data[output_str->size] = pop(stack);
        output_str->size++;
      }
      nulldata(stack);
    }
    // операнды
    if (input_str[i] >= '0' && input_str[i] <= '9') {
      parser_operand(input_str, output_str, &i);
      // операции
    } else if (isoperation(input_str[i])) {
      if (stack->size == 0) {
        push(stack, input_str[i]);
      } else {
        // больше 0 = текущее число имеет больший приоритет чем последнее
        // число в стеке
        diff_priority =
            priority(input_str[i]) - stack->priority[stack->size - 1];

        if (diff_priority > 0) {
          push(stack, input_str[i]);
        }

        else if (diff_priority <= 0) {
          while (stack->size != 0 && peek(stack) != '(' && diff_priority <= 0) {
            output_str->data[output_str->size] = pop(stack);
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
  }
  while (stack->size != 0) {
    output_str->data[output_str->size] = pop(stack);
    output_str->size++;
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

int isoperation(int operation) {
  if (operation == '+' || operation == '-' || operation == '*' ||
      operation == '/' || operation == '^')
    return 1;
  else
    return 0;
}