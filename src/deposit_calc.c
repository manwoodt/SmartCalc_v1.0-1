#include "calc.h"

// int main() {
//   long double amount = 1000000;
//   double accrued_interest, tax, res;

//   //  calculateAnnuity(loanAmount, term, interestRate);

//   accrued_interest = get_total_ac(&amount, 24, 5, 0, 1, 5000, 5000);

//   printf("начисленные проценты: %.2f\n", accrued_interest);
//   printf("сумма налога: %.2f\n", tax);
//   printf("сумма на вкладе к концу срока: %.2f\n", res);
//   return 0;
// }

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
// вычисляем начисленные проценты
long double get_total_ac(long double *amount, double term,
                         long double interest_rate, int mode,
                         int capitalization, long double replenishment,
                         long double withdrawal) {
  long double res = 0;
  mode = (mode == 0) ? 12 : 1;
  interest_rate /= 100;
  // пополнения
  replenishment *= mode;
  // снятия
  withdrawal *= mode;
  for (int i = 0; (double)i < term; i++) {
    long double tmp = 0;
    if (mode == 12) {
      tmp = *amount * interest_rate / mode;
    } else {
      if (i % 11 == 0 && i != 0) {
        tmp = *amount * interest_rate / 100;
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

long double get_tax_am(long double total, long double rate) {
  return total * rate / 100;
}

long double get_total_am(long double amount, long double accrued,
                         long double tax) {
  return amount + accrued - tax;
}

/*
    long double amount = ui->line_amount->text().toDouble();
    double term = ui->line_term->text().toDouble();
    if (ui->check_ym->currentIndex() == 1) {
      term = convert_to_months(term);
    }
    long double interest_rate = ui->line_interest->text().toDouble();
    long double tax_rate = ui->line_tax_rate->text().toDouble();
    int mode = ui->check_my_p->currentIndex();
    bool capitalization = ui->check_capit->isChecked();
    long double monthly_replenishment = ui->line_replenish->text().toDouble();
    long double monthly_withdrawal = ui->line_withdraw->text().toDouble();
    long double total_accrued =
        get_total_ac(&amount, term, interest_rate, mode, (int)capitalization,
                     monthly_replenishment, monthly_withdrawal);
    long double tax_amount = get_tax_am(total_accrued, tax_rate);
    long double total_amount = get_total_am(amount, total_accrued, tax_amount);
    QString accrued = QString::number(total_accrued, 'g', 7);
    QString tax_amt = QString::number(tax_amount, 'g', 7);
    QString tot_amt = QString::number(total_amount, 'g', 7);
    ui->line_accrued->setText(accrued);
    ui->line_tax->setText(tax_amt);
    ui->line_total->setText(tot_amt);
*/
