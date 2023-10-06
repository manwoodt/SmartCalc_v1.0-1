#include "calc.h"

int is_operation(int operation) {
  if (operation == '+' || operation == '-' || operation == '~' ||
      operation == '*' || operation == '%' || operation == '/' ||
      operation == '^' || is_trigonometry(operation))
    return 1;
  else
    return 0;
}

int garbage_for_validator(int operation) {
  if (is_operation(operation) || operation == '(' || operation == '.' ||
      operation == ')' || is_number(operation) || is_trigonometry(operation) ||
      operation == 'x')
    return 0;
  else
    return 1;
}

int is_number(int operation) {
  return (operation >= '0' && operation <= '9') ? 1 : 0;
}

int is_good_expression(char* expression) {
  for (unsigned int i = 0; i < strlen(expression); i++) {
    if (expression[i] != '.' && expression[i] > '9' && expression[i] < '0')
      return 0;
  }
  return 1;
}

int is_trigonometry(int operation) {
  return (operation == 'c' || operation == 's' || operation == 't' ||
          operation == 'q' || operation == 'l' || operation == 'a' ||
          operation == 'i' || operation == 'o' || operation == 'n')
             ? 1
             : 0;
}

// int is_trigonometry(int operation) {
//   return (operation == 'c' || operation == 'o' || operation == 's' ||
//           operation == 'i' || operation == 'n' || operation == 't' ||
//           operation == 'g' || operation == 'l' || operation == 'q' ||
//           operation == 'r' || operation == 'a')
//              ? 1
//              : 0;
// }

int priority(int operation) {
  int priority = 0;
  switch (operation) {
    case '+':
    case '-':
      priority = 1;
      break;
    case '*':
    case '/':
      priority = 2;
      break;
    case '^':
      priority = 3;
      break;
    case 'c':
    case 's':
    case 't':
    case 'q':
    case 'l':
    case 'n':
    case 'o':
    case 'i':
    case 'a':
      priority = 4;
      break;
    case '~':
      priority = 5;
      break;
    case ')':
      priority = 6;
      break;
    case '(':
      priority = 7;
      break;
    // cos - c, sin - s, tan - t, log - l, ln - n, sqrt - q
    default:
      priority = 0;
      break;
  }
  return priority;
}