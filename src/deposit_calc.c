#include "calc.h"

/*
Вход: сумма вклада, срок размещения, процентная ставка, налоговая ставка,
периодичность выплат, капитализация процентов, список пополнений, список
частичных снятий
Выход: начисленные проценты, сумма налога, сумма на вкладе к
концу срока
Input: deposit amount, deposit term, interest rate, tax rate, periodicity of
payments, capitalization of interest, replenishments list, partial withdrawals
list
Output: accrued interest, tax amount, deposit amount by the end of the term
*/

double get_total_ac(double *amount, double term, double interest_rate, int mode,
                    int capitalization, double replenishment, double withdrawal,
                    double tax_rate) {
  if (*amount < 0.01 || term < 0.01 || interest_rate < 0.01 || tax_rate < 0.01)
    return -1;
  double res = 0;
  mode = (mode == 0) ? 12 : 1;
  interest_rate /= 100;
  // пополнения
  replenishment *= mode;
  // снятия
  withdrawal *= mode;
  for (int i = 1; (double)i <= term; i++) {
    double tmp = 0;
    if (mode == 12) {
      tmp = *amount * interest_rate / mode;
    } else {
      if (i % 12 == 0) {
        tmp = *amount * interest_rate;
      }
    }
    *amount += replenishment;
    *amount -= withdrawal;
    if (capitalization) {
      *amount += tmp;
    }
    res += tmp;
  }
  return res;
}

double get_tax_am(double total, double tax_rate) {
  return total * tax_rate / 100;
}

double get_total_am(double amount, double accrued, double tax) {
  return amount + accrued - tax;
}
