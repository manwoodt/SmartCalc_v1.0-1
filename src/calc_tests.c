#include <check.h>

#include "calc.h"

START_TEST(validator_test_1) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "5.5.5-1");
  res = validator(input_str, cor_input_str, 0, 1);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 1);
  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_2) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "5+");
  res = validator(input_str, cor_input_str, 0, 1);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 1);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_3) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "sin(x)+ln(x)+log(x)-acos(x)-atan(x)+tan(x)");
  res = validator(input_str, cor_input_str, 1, 1);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 0);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_4) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "sin(x)+ln(x)+log(x)-acos(x)-atan(x)+tan(x)");
  res = validator(input_str, cor_input_str, 1, 0);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 1);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_5) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "5--4++3");
  res = validator(input_str, cor_input_str, 1, 1);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 0);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_6) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "5-f");
  res = validator(input_str, cor_input_str, 1, 1);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 1);

  free(input_str);
  free(cor_input_str);
}
END_TEST

START_TEST(validator_test_7) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  char *cor_input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  int res = 0;

  strcpy(input_str, "(5*6)-4*3-(3");
  res = validator(input_str, cor_input_str, 1, 1);
  if (res != 0) res = 1;
  ck_assert_int_eq(res, 1);

  free(input_str);
  free(cor_input_str);
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

START_TEST(parser_calculator_test_9) {
  double res = parser("~5+3", "0");
  ck_assert_double_eq_tol(res, -2, 0.0000001);
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

START_TEST(credit_calc_test_1) {
  double overpayment, totalPayment, monthlyPayment;

  int res = calculateAnnuity(1000000, 12, 15, &monthlyPayment, &totalPayment,
                             &overpayment);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(monthlyPayment, 90258);
  ck_assert_int_eq(totalPayment, 1083099.7);
  ck_assert_int_eq(overpayment, 83099.7);
}

START_TEST(credit_calc_test_2) {
  double overpayment, totalPayment, monthlyPayment;

  int res = calculateDifferentiated(1000000, 12, 15, &monthlyPayment,
                                    &totalPayment, &overpayment);
  ck_assert_int_eq(res, 0);
  ck_assert_int_eq(monthlyPayment, 84375);
  ck_assert_int_eq(totalPayment, 1081250);
  ck_assert_int_eq(overpayment, 81250);
}

START_TEST(credit_calc_test_3) {
  double overpayment, totalPayment, monthlyPayment;

  int res = calculateAnnuity(-1000000, 12, 15, &monthlyPayment, &totalPayment,
                             &overpayment);
  ck_assert_int_eq(res, -1);
}

START_TEST(deposit_calc_test_1) {
  double amount = 1000000;
  double ac_interest = get_total_ac(&amount, 12, 7, 1, 0, 0, 0, 3);
  double tax_amount = get_tax_am(ac_interest, 3);
  double total_amount = get_total_am(amount, ac_interest, tax_amount);

  ck_assert_int_eq(ac_interest, 70000);
  ck_assert_int_eq(tax_amount, 2100);
  ck_assert_int_eq(total_amount, 1067900);
}

START_TEST(deposit_calc_test_2) {
  double amount = 1000000;
  double ac_interest = get_total_ac(&amount, 12, 7, 0, 1, 0, 0, 3);
  double tax_amount = get_tax_am(ac_interest, 3);
  double total_amount = get_total_am(amount, ac_interest, tax_amount);

  ck_assert_int_eq(ac_interest, 72290);
  ck_assert_int_eq(tax_amount, 2168);
  ck_assert_int_eq(total_amount, 1142411);
}
END_TEST

START_TEST(deposit_calc_test_3) {
  double amount = 1000000;
  double ac_interest = get_total_ac(&amount, 12, 7, 1, 1, 0, 0, 3);
  double tax_amount = get_tax_am(ac_interest, 3);
  double total_amount = get_total_am(amount, ac_interest, tax_amount);

  ck_assert_int_eq(ac_interest, 70000);
  ck_assert_int_eq(tax_amount, 2100);
  ck_assert_int_eq(total_amount, 1137900);
}
END_TEST

START_TEST(deposit_calc_test_4) {
  double amount = -1000000;
  double ac_interest = get_total_ac(&amount, 12, 7, 1, 1, 0, 0, 3);
  ck_assert_int_eq(ac_interest, -1);
}
END_TEST

START_TEST(is_good_exp_1) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  strcpy(input_str, "g");
  int res = is_good_expression(input_str);
  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(is_good_exp_2) {
  char *input_str = calloc(INPUT_STR_MAX_SIZE, sizeof(char));
  strcpy(input_str, "5.9");
  int res = is_good_expression(input_str);
  ck_assert_int_eq(res, 1);
}
END_TEST
Suite *s21_calc_suite(void) {
  Suite *s;
  TCase *tc_core;
  s = suite_create("s21_calc");
  tc_core = tcase_create("Core");
  suite_add_tcase(s, tc_core);
  tcase_add_test(tc_core, validator_test_1);
  tcase_add_test(tc_core, validator_test_2);
  tcase_add_test(tc_core, validator_test_3);
  tcase_add_test(tc_core, validator_test_4);
  tcase_add_test(tc_core, validator_test_5);
  tcase_add_test(tc_core, validator_test_6);
  tcase_add_test(tc_core, validator_test_7);

  tcase_add_test(tc_core, parser_calculator_test_1);
  tcase_add_test(tc_core, parser_calculator_test_2);
  tcase_add_test(tc_core, parser_calculator_test_3);
  tcase_add_test(tc_core, parser_calculator_test_4);
  tcase_add_test(tc_core, parser_calculator_test_5);
  tcase_add_test(tc_core, parser_calculator_test_6);
  tcase_add_test(tc_core, parser_calculator_test_7);
  tcase_add_test(tc_core, parser_calculator_test_8);
  tcase_add_test(tc_core, parser_calculator_test_9);
  tcase_add_test(tc_core, parser_calculator_test_log);
  tcase_add_test(tc_core, parser_calculator_test_ln);
  tcase_add_test(tc_core, parser_calculator_test_sqrt);
  tcase_add_test(tc_core, parser_calculator_test_cos);
  tcase_add_test(tc_core, parser_calculator_test_sin);
  tcase_add_test(tc_core, parser_calculator_test_tan);
  tcase_add_test(tc_core, parser_calculator_test_acos);
  tcase_add_test(tc_core, parser_calculator_test_asin);
  tcase_add_test(tc_core, parser_calculator_test_atan);

  tcase_add_test(tc_core, credit_calc_test_1);
  tcase_add_test(tc_core, credit_calc_test_2);
  tcase_add_test(tc_core, credit_calc_test_3);

  tcase_add_test(tc_core, deposit_calc_test_1);
  tcase_add_test(tc_core, deposit_calc_test_2);
  tcase_add_test(tc_core, deposit_calc_test_3);
  tcase_add_test(tc_core, deposit_calc_test_4);

  tcase_add_test(tc_core, is_good_exp_1);
  tcase_add_test(tc_core, is_good_exp_2);

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
