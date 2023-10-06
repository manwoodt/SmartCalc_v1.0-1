#include <math.h>
#include <stdio.h>

// Предусмотреть специальный режим "калькулятор доходности вкладов" (за образец
// можно взять сайты banki.ru и calcus.ru):

// Вход: сумма вклада, срок размещения, процентная ставка, налоговая ставка,
// периодичность выплат, капитализация процентов, список пополнений, список
// частичных снятий Выход: начисленные проценты, сумма налога, сумма на вкладе к
// концу срока

void calculateAnnuity(double loanAmount, int term, char month_or_year,
                      double interestRate, double* monthlyPayment,
                      double* totalPayment, double* overpayment);
void calculateDifferentiated(double loanAmount, int term, char month_or_year,
                             double interestRate, double* monthlyPayment,
                             double* totalPayment, double* overpayment);

// Вход: общая сумма кредита, срок, процентная ставкаgit , тип (аннуитетный,
// дифференцированный) rate -%, loan - кредит, term - срок (в годах)
// Выход: ежемесячный платеж, переплата по кредиту, общая выплата

void calculateAnnuity(double loanAmount, int term, char month_or_year,
                      double interestRate, double* monthlyPayment,
                      double* totalPayment, double* overpayment) {
  double monthlyInterestRate = interestRate / 100 / 12;
  if (month_or_year == 'y') term *= 12;
  *monthlyPayment = loanAmount *
                    (monthlyInterestRate * pow(1 + monthlyInterestRate, term)) /
                    (pow(1 + monthlyInterestRate, term) - 1);
  *totalPayment = *monthlyPayment * term;
  *overpayment = *totalPayment - loanAmount;
}

void calculateDifferentiated(double loanAmount, int term, char month_or_year,
                             double interestRate, double* monthlyPayment,
                             double* totalPayment, double* overpayment) {
  if (month_or_year == 'y') term *= 12;
  double monthlyInterestRate = interestRate / 100 / 12;
  double loanBalance = 0;
  for (int i = 1; i <= term; i++) {
    loanBalance = (loanAmount - ((loanAmount / term) * (i - 1)));
    *monthlyPayment = (loanAmount / term) + loanBalance * monthlyInterestRate;
    *totalPayment += *monthlyPayment;
    *overpayment += *monthlyPayment - loanAmount / term;
  }
}

int main() {
  double overpayment, totalPayment, monthlyPayment;

  //  calculateAnnuity(loanAmount, term, interestRate);

  calculateAnnuity(1000000, 1, 'm', 20, &monthlyPayment, &totalPayment,
                   &overpayment);

  printf("Ежемесячный платеж: %.2f\n", monthlyPayment);
  printf("Переплата по кредиту: %.2f\n", overpayment);
  printf("Общая выплата: %.2f\n", totalPayment);
  return 0;
}
