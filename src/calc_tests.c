#include <check.h>

#include "calc.h"

START_TEST(validator_test_1) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;

  strcpy(input_str, "5.5.5-1");
  res1 = validator(input_str, cor_input_str, 0, 1);
  if (res1 != 0) res1 = 1;
  ck_assert_int_eq(res1, 1);
  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_2) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;

  strcpy(input_str, "5+5*5/5-sin(5)^ln(5)+log(10)-acos(3)-atan(7)+tan(3)";
  res1 = validator(input_str, cor_input_str, 0, 1);
  if (res1 != 0) res1 = 1;
  ck_assert_int_eq(res1, 1);
  free(input_str);
  free(cor_input_str);


  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_3) {
  int res = validator("5+5*5/5-sin(5)^ln(5)*asin(34)", "fff", 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_4) {
  int res = validator("5+5*5/5.3-sin(x)^ln(x)", "-49.8", 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_5) {
  int res = validator("5+(5*5)/5-sin(x)^ln(x)", "bbb.", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_6) {
  int res = validator(
      "5+5.",
      "56789009876543234567890098765432345678909876543234567898734"
      "567890098765432345678900987654323456789098765432345678987342345678903456"
      "789009876543234567890098765432345678909876543234567898734567"
      "89009876543234567890"
      "098765432345678909876543234567898734567890098765432345678900987654323456"
      "7890987654323456789873456789009876543234567890"
      "098765432345678909876543234567898709876543234567890098765432345678909876"
      "5432345678987654345987654",
      0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_7) {
  int res = validator("p", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_8) {
  int res = validator("(1.5+3))", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_9) {
  int res = validator("406+x", "11.", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_10) {
  int res = validator("406)", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_11) {
  int res = validator("406--", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_12) {
  int res = validator(
      "406+1+x",
      "567890098765432345656789009876543234565678900987654323456567890098765432"
      "345656789009876543234567890098765432345678909876543234567898"
      "734234567890345678900987654323456789009876543234567890987654323456789873"
      "456789009876543234567890987654323456789873423456789034567890"
      "098765432345678900987654323456789098765432345678987345678900987654323456"
      "789098765432345678987342345678903456789009876543234567890098"
      "765432345678909876543234567898734567890098765432345678909876543234567898"
      "734234567890345678900987654323456789009876543234567890987654"
      "323456789873456789009876543234567890987654323456789873423456789034567890"
      "0987654323456789009876543234567890987654323456789873456",
      0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_13) {
  int res = validator(
      "56789009876543234567890098765432345678909876543234567898734"
      "567890098765432345678900987654323456789098765432345678987342345678903456"
      "789009876543234567890098765432345678909876543234567898734567"
      "89009876543234567890"
      "098765432345678909876543234567898734567890098765432345678900987654323456"
      "7890987654323456789873456789009876543234567890"
      "098765432345678909876543234567898709876543234567890098765432345678909876"
      "5432345678987654345987654",
      "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_14) {
  int res = validator("5)", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_15) {
  int res = validator("(", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_16) {
  int res = validator("ln(-log(-cos(-sin(-acos(-asin(2))))))", "", 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_17) {
  int res = validator("asin(-sqrt(-tan(-ln(-atan(-asin(2))))))", "", 0);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_18) {
  int res = validator("pow1a", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_19) {
  int res = validator("x221powe", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_20) {
  int res = validator("221mod(1+1)-221mod(sin(x*x+xmodx-x^x))", "", 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(validator_test_21) {
  int res = validate_x_y("-4");
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_22) {
  int res = validate_x_y("4");
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_23) {
  int res = validate_x_y("4.4");
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(validator_test_24) {
  int res = validate_x_y("4.4.");
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(parser_calculator_test_1) {
  double res = parser("222+222", "0");
  ck_assert_double_eq_tol(res, 444.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_2) {
  double res = parser("24-42", "0");
  ck_assert_double_eq_tol(res, -18.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_3) {
  double res = parser("4*5", "0");
  ck_assert_double_eq_tol(res, 20.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_4) {
  double res = parser("20/4", "0");
  ck_assert_double_eq_tol(res, 5.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_5) {
  double res = parser("21%4", "0");
  ck_assert_double_eq_tol(res, 1.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_6) {
  double res = parser("2^2", "0");
  ck_assert_double_eq_tol(res, 4.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_7) {
  double res = parser("2*(4-3)/2", "0");
  ck_assert_double_eq_tol(res, 1.0, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_8) {
  double res = parser("2.2+1", "0");
  ck_assert_double_eq_tol(res, 3.2, 0.0000001);
}
END_TEST

START_TEST(parser_calculator_test_log) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "log(10)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "log(100)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 2.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "log(15)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.17609125906, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_ln) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "ln(2.71828182846)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "ln(100)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 4.60517018599, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "ln(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.0, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_sqrt) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "sqrt(4)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 2.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "sqrt(100)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 10.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "sqrt(5.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 2.34520787, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_sin) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "sin(0)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "sin(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.8414709848, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "sin(5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, -0.95892427466, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "sin(0.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.4794255386, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_cos) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "cos(0)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "cos(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.54030230586, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "cos(5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.28366218546, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "cos(0.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.87758256189, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_tan) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "tan(0)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.0, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "tan(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.55740772465, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "tan(5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, -3.38051500625, 0.0000001);

  memset(cor_input_str, 0, strlen(cor_input_str));
  strcpy(input_str, "tan(0.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.54630248984, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_asin) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "asin(0)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.0, 0.0000001);

  strcpy(input_str, "asin(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.57079633, 0.0000001);

  strcpy(input_str, "asin(0.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.523598776, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_acos) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "acos(0)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.57079633, 0.0000001);

  strcpy(input_str, "acos(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.0, 0.0000001);

  strcpy(input_str, "acos(0.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.04719755, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(parser_calculator_test_atan) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res1 = 0;
  double res2 = 0;

  strcpy(input_str, "atan(0)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.0, 0.0000001);

  strcpy(input_str, "atan(1)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.785398163, 0.0000001);

  strcpy(input_str, "atan(5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 1.37340077, 0.0000001);

  strcpy(input_str, "atan(0.5)");
  res1 = validator(input_str, cor_input_str, 0, 1);
  ck_assert_int_eq(res1, 0);
  res2 = parser(cor_input_str, "0");
  ck_assert_double_eq_tol(res2, 0.463647609, 0.0000001);

  free(input_str);
  free(cor_input_str);
}
END_TEST

// START_TEST(parser_calculator_test_2) {
//   double res = parser_calculator("2+x", "5", 0, 0.0);
//   ck_assert_double_eq_tol(res, 7.0, 0.0000001);
// }
// END_TEST

// START_TEST(parser_calculator_test_3) {
//   double res = parser_calculator("2+x", "-5", 0, 0.0);
//   ck_assert_double_eq_tol(res, -3.0, 0.0000001);
// }
// END_TEST

// START_TEST(parser_calculator_test_4) {
//   double res = parser_calculator(
//       "(atan(x-(1*8)^6)*(sqrt(sin(x)))*log(1))/100.678", "1", 0, 0.0);
//   ck_assert_double_eq_tol(res, 0.0, 0.0000001);
// }
// END_TEST

// START_TEST(parser_calculator_test_5) {
//   double res = parser_calculator("11mod3", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, 2.0, 0.0000001);
// }
// END_TEST

// START_TEST(parser_calculator_test_6) {
//   double res = parser_calculator("-7+1", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, -6.0, 0.0000001);
// }
// END_TEST

// START_TEST(parser_calculator_test_7) {
//   double res = parser_calculator("5---3", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, 2.0, 0.0000001);
// }
// END_TEST

// START_TEST(parser_calculator_test_8) {
//   double res = parser_calculator("ln(99)+tan(99)", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, -20.4974151295, 0.0000001);
// }

// START_TEST(parser_calculator_test_9) {
//   double res = parser_calculator("cos(99)", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, 0.03982088039, 0.0000001);
// }

// START_TEST(parser_calculator_test_10) {
//   double res = parser_calculator("2^3^2", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, 512, 0.0000001);
// }

// START_TEST(parser_calculator_test_11) {
//   double res = parser_calculator("5+++5", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, 10, 0.0000001);
// }

// START_TEST(parser_calculator_test_12) {
//   double res = parser_calculator("sin(1)^2", "", 0, 0.0);
//   ck_assert_double_eq_tol(res, 0.70807341827, 0.0000001);
// }

// START_TEST(credit_calc_test_1) {
//   double res = annuity_get_monthly_payment(100000, 5, 12);
//   int test_res = fabsl(res - (8560.748179)) < 1e-4 ? 0 : 1;
//   ck_assert_int_eq(test_res, 1);
// }

// START_TEST(credit_calc_test_2) {
//   double res = annuity_get_total_payment(8560.748, 12);
//   int test_res = fabsl(res - (102728.976000)) < 1e-4 ? 0 : 1;
//   ck_assert_int_eq(test_res, 0);
// }
// END_TEST

// START_TEST(credit_calc_test_3) {
//   double res = differentiated_get_monthly_payment(100000, 12);
//   int test_res = fabsl(res - (8333.333333)) < 1e-4 ? 0 : 1;
//   ck_assert_int_eq(test_res, 0);
// }
// END_TEST

// START_TEST(credit_calc_test_4) {
//   double res = get_overpayment_on_credit(102729, 100000);
//   ck_assert_ldouble_eq(res, 2729);
// }
// END_TEST

// START_TEST(credit_calc_test_5) {
//   double res = differentiated_get_total_payment(100, 1000, 10, 10);
//   ck_assert_ldouble_eq(res, 56000);
// }
// END_TEST

// START_TEST(credit_calc_test_6) {
//   int res = validate_it("14");
//   ck_assert_int_eq(res, 0);
// }
// END_TEST

// START_TEST(credit_calc_test_7) {
//   int res = validate_it("14.");
//   ck_assert_int_eq(res, 1);
// }
// END_TEST

// START_TEST(credit_calc_test_8) {
//   int res = validate_it("a");
//   ck_assert_int_eq(res, 1);
// }
// END_TEST

// START_TEST(deposit_calc_test_1) {
//   double res = convert_to_months(2);
//   ck_assert_double_eq(res, 24);
// }

// START_TEST(deposit_calc_test_2) {
//   double deposit_amount = 100000;
//   double res = get_accrued_interest(&deposit_amount, 12, 5, 0, 0, 0, 0);
//   ck_assert_ldouble_eq(res, 5000);
// }
// END_TEST

// START_TEST(deposit_calc_test_3) {
//   double res = get_tax_amount(104850, 3);
//   int test_res = fabsl(res - (3145.500000)) < 1e-4 ? 0 : 1;
//   ck_assert_int_eq(test_res, 0);
// }
// END_TEST

// START_TEST(deposit_calc_test_4) {
//   double res = get_deposit_amount_by_end(100000, 5000, 3);
//   int test_res = fabsl(res - (104997.000000)) < 1e-4 ? 0 : 1;
//   ck_assert_int_eq(test_res, 0);
// }
// END_TEST

Suite *s21_calc_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_calc");
  tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, validator_test_1);
  // tcase_add_test(tc_core, validator_test_2);
  // tcase_add_test(tc_core, validator_test_3);
  // tcase_add_test(tc_core, validator_test_4);
  // tcase_add_test(tc_core, validator_test_5);
  // tcase_add_test(tc_core, validator_test_6);
  // tcase_add_test(tc_core, validator_test_7);
  // tcase_add_test(tc_core, validator_test_8);
  // tcase_add_test(tc_core, validator_test_9);
  // tcase_add_test(tc_core, validator_test_10);
  // tcase_add_test(tc_core, validator_test_11);
  // tcase_add_test(tc_core, validator_test_12);
  // tcase_add_test(tc_core, validator_test_13);
  // tcase_add_test(tc_core, validator_test_14);
  // tcase_add_test(tc_core, validator_test_15);
  // tcase_add_test(tc_core, validator_test_16);
  // tcase_add_test(tc_core, validator_test_17);
  // tcase_add_test(tc_core, validator_test_18);
  // tcase_add_test(tc_core, validator_test_19);
  // tcase_add_test(tc_core, validator_test_20);
  // tcase_add_test(tc_core, validator_test_21);
  // tcase_add_test(tc_core, validator_test_22);
  // tcase_add_test(tc_core, validator_test_23);
  // tcase_add_test(tc_core, validator_test_24);

  tcase_add_test(tc_core, parser_calculator_test_1);
  tcase_add_test(tc_core, parser_calculator_test_2);
  tcase_add_test(tc_core, parser_calculator_test_3);
  tcase_add_test(tc_core, parser_calculator_test_4);
  tcase_add_test(tc_core, parser_calculator_test_5);
  tcase_add_test(tc_core, parser_calculator_test_6);
  tcase_add_test(tc_core, parser_calculator_test_7);
  tcase_add_test(tc_core, parser_calculator_test_8);
  tcase_add_test(tc_core, parser_calculator_test_log);
  tcase_add_test(tc_core, parser_calculator_test_ln);
  tcase_add_test(tc_core, parser_calculator_test_sqrt);
  tcase_add_test(tc_core, parser_calculator_test_cos);
  tcase_add_test(tc_core, parser_calculator_test_sin);
  tcase_add_test(tc_core, parser_calculator_test_tan);
  tcase_add_test(tc_core, parser_calculator_test_acos);
  tcase_add_test(tc_core, parser_calculator_test_asin);
  tcase_add_test(tc_core, parser_calculator_test_atan);
  // tcase_add_test(tc_core, parser_calculator_test_7);
  // tcase_add_test(tc_core, parser_calculator_test_8);
  // tcase_add_test(tc_core, parser_calculator_test_9);
  // tcase_add_test(tc_core, parser_calculator_test_10);
  // tcase_add_test(tc_core, parser_calculator_test_11);
  // tcase_add_test(tc_core, parser_calculator_test_12);

  // tcase_add_test(tc_core, credit_calc_test_1);
  // tcase_add_test(tc_core, credit_calc_test_2);
  // tcase_add_test(tc_core, credit_calc_test_3);
  // tcase_add_test(tc_core, credit_calc_test_4);
  // tcase_add_test(tc_core, credit_calc_test_5);
  // tcase_add_test(tc_core, credit_calc_test_6);
  // tcase_add_test(tc_core, credit_calc_test_7);
  // tcase_add_test(tc_core, credit_calc_test_8);

  // tcase_add_test(tc_core, deposit_calc_test_1);
  // tcase_add_test(tc_core, deposit_calc_test_2);
  // tcase_add_test(tc_core, deposit_calc_test_3);
  // tcase_add_test(tc_core, deposit_calc_test_4);

  return s;
}

int main() {
  int number_failed;
  Suite *s;
  SRunner *sr;
  s = s21_calc_suite();
  sr = srunner_create(s);
  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? 0 : 1;
}
