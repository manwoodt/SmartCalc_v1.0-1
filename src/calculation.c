#include "calc.h"

int main() {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  // scanf("%s", input_str);
  strcpy(input_str, "86");
  // strcpy(input_str, "atan(0.5)");
  // strcpy(input_str, "sqrt(100)");
  //    strcpy(input_str, "sqrt(100)");
  //  strcpy(input_str, "tan(1)");

  // strcpy(input_str, "(42*((43+3-4)/23))^2");
  //  strcpy(input_str, "(43+43-5)/9");
  printf("BEF: %s\n", input_str);
  if (validator(input_str, cor_input_str)) {
    printf("AFT: %s\n", cor_input_str);
    double res = parser(cor_input_str);
    // printf("Output_str\n");
    // printStack(output_str);
    printf("res: %f\n", res);
  } else
    printf("ERROR\n");

  free(input_str);
  free(cor_input_str);

  return 0;
}

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
    default:
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
