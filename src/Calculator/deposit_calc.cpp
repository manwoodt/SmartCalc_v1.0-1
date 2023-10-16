#include "deposit_calc.h"

#include "mainwindow.h"
#include "ui_deposit_calc.h"

Deposit_calc::Deposit_calc(QWidget *parent)
    : QWidget(parent), ui(new Ui::Deposit_calc) {
  ui->setupUi(this);
  connect(ui->pushButton_back, SIGNAL(clicked()), this, SLOT(back()));
  connect(ui->pushButton_calc, SIGNAL(clicked()), this, SLOT(equal()));
  connect(ui->pushButton_clear, SIGNAL(clicked()), this,
          SLOT(delete_all_text()));
}

void Deposit_calc::back() {
  this->close();
  emit firstWindow();
}

void Deposit_calc::delete_all_text() {
  ui->lineEdit_accruedInterest->clear();
  ui->lineEdit_interestRate->clear();
  ui->lineEdit_taxRate->clear();
  ui->lineEdit_loanAmount->clear();
  ui->lineEdit_replenishment->clear();
  ui->lineEdit_term->clear();
  ui->lineEdit_withdrawal->clear();
  ui->lineEdit_tax->clear();
  ui->lineEdit_totalAmount->clear();
}

void Deposit_calc::equal() {
  double amount = ui->lineEdit_loanAmount->text().toDouble();
  double term = ui->lineEdit_term->text().toDouble();

  if (ui->lineEdit_loanAmount->text().isEmpty() ||
      ui->lineEdit_term->text().isEmpty() ||
      ui->lineEdit_interestRate->text().isEmpty() ||
      ui->lineEdit_taxRate->text().isEmpty()) {
    QMessageBox::warning(this, "Error:", "Заполни все поля");
  }

  double interest_rate = ui->lineEdit_interestRate->text().toDouble();
  double tax_rate = ui->lineEdit_taxRate->text().toDouble();
  int mode = ui->periodOfPay->currentIndex();
  int capitalization = ui->Capitalization->isChecked();
  double monthly_replenishment = ui->lineEdit_replenishment->text().toDouble();
  double monthly_withdrawal = ui->lineEdit_withdrawal->text().toDouble();

  double accrued_interest =
      get_total_ac(&amount, term, interest_rate, mode, capitalization,
                   monthly_replenishment, monthly_withdrawal, tax_rate);

  if (accrued_interest == -1) {
    ui->lineEdit_accruedInterest->setText("Error");
    ui->lineEdit_tax->setText("Error");
    ui->lineEdit_totalAmount->setText("Error");
  } else {
    QString accrued_interest_str =
        QString::number(round(accrued_interest * 100) / 100, 'g', 15);
    ui->lineEdit_accruedInterest->setText(accrued_interest_str);
    double tax_amount = get_tax_am(accrued_interest, tax_rate);
    QString tax_amount_str =
        QString::number(round(tax_amount * 100) / 100, 'g', 15);
    ui->lineEdit_tax->setText(tax_amount_str);
    double total_amount = get_total_am(amount, accrued_interest, tax_amount);
    QString total_amount_str =
        QString::number(round(total_amount * 100) / 100, 'g', 15);
    ui->lineEdit_totalAmount->setText(total_amount_str);
  }
}

Deposit_calc::~Deposit_calc() { delete ui; }
