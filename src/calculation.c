#include "calc.h"

double calculation(create_stack *output_str) {
  create_stack stack_res = {0};
  for (unsigned int i = 0; i < output_str->size; i++) {
    // если число
    if (output_str->char_or_not[i] == 0) {
      push(&stack_res, output_str->data[i]);
    }
    // если операция
    else {
      calculation_operation(output_str, &stack_res, i);
    }
  }
  return peek(&stack_res);
}

// cos - c, sin - s, tg - t, ctg - g, log - l, ln - n, sqrt - q
void calculation_operation(create_stack *output_str, create_stack *stack_res,
                           unsigned int i) {
  double num1 = peek(stack_res);
  nulldata(stack_res);
  if (output_str->priority[i] >= 4) {
    calculation_math_func_operation(output_str, stack_res, i, num1);
  } else {
    calculation_basic_operation(output_str, stack_res, i, num1);
  }
}

void calculation_math_func_operation(create_stack *output_str,
                                     create_stack *stack_res, unsigned int i,
                                     double num1) {
  switch (output_str->operation[i]) {
    case 'c':
      push(stack_res, cos(num1));
      break;
    case 's':
      push(stack_res, sin(num1));
      break;
    case 't':
      push(stack_res, tan(num1));
      break;
    case 'o':
      push(stack_res, acos(num1));
      break;
    case 'i':
      push(stack_res, asin(num1));
      break;
    case 'a':
      push(stack_res, atan(num1));
      break;
    case 'l':
      push(stack_res, log10(num1));
      break;
    case 'n':
      push(stack_res, log(num1));
      break;
    case 'q':
      push(stack_res, sqrt(num1));
      break;
    case '~':
      push(stack_res, (num1) * (-1));
      break;
  }
}

void calculation_basic_operation(create_stack *output_str,
                                 create_stack *stack_res, unsigned int i,
                                 double num1) {
  double num2 = peek(stack_res);
  nulldata(stack_res);
  switch (output_str->operation[i]) {
    case '+':
      push(stack_res, num2 + num1);
      break;
    case '-':
      push(stack_res, num2 - num1);
      break;
    case '*':
      push(stack_res, num2 * num1);
      break;
    case '/':
      push(stack_res, num2 / num1);
      break;
    case '^':
      push(stack_res, pow(num2, num1));
      break;
    case '%':
      push(stack_res, fmod(num2, num1));
      break;
    default:
      break;
  }
}
