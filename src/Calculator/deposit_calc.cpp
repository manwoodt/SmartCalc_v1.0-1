#include "deposit_calc.h"
#include "mainwindow.h"
#include "ui_deposit_calc.h"

Deposit_calc::Deposit_calc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit_calc)
{

    ui->setupUi(this);
    connect(ui->pushButton_back, SIGNAL(clicked()), this,SLOT(back()));
    connect(ui->pushButton_calc, SIGNAL(clicked()), this,SLOT(equal()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this,SLOT(delete_all_text()));
}


void Deposit_calc::back() {
  this->close();
  emit firstWindow();
}

void Deposit_calc::delete_all_text(){
  ui->lineEdit_accruedInterest->clear();
}

void Deposit_calc::equal() {
    long double amount = ui->lineEdit_loanAmount->text().toDouble();
    double term = ui->lineEdit_term->text().toDouble();
    if (ui->yearOrMonth->currentIndex() == 0) {
      term = term /12;
    }
    long double interest_rate = ui->lineEdit_interestRate->text().toDouble();
    long double tax_rate = ui->lineEdit_taxRate->text().toDouble();
    int mode = ui->periodOfPay->currentIndex();
    bool capitalization = ui->Capitalization->isChecked();
    long double monthly_replenishment = ui->lineEdit_replenishment->text().toDouble();
    long double monthly_withdrawal = ui->lineEdit_withdrawal->text().toDouble();
    long double accrued_interest =
        get_total_ac(&amount, term, interest_rate, mode, (int)capitalization,
                     monthly_replenishment, monthly_withdrawal);

    QString accrued_interest_str = QString::number(accrued_interest, 'g', 15);
    ui->lineEdit_accruedInterest->setText(accrued_interest_str);
    long double tax_amount = get_tax_am(accrued_interest, tax_rate);
    QString tax_amount_str = QString::number(tax_amount, 'g', 15);
    ui->lineEdit_tax->setText(tax_amount_str);
    long double total_amount = get_total_am(amount, accrued_interest, tax_amount);
    QString total_amount_str = QString::number(total_amount, 'g', 15);
    ui->lineEdit_totalAmount->setText(total_amount_str);
}

Deposit_calc::~Deposit_calc()
{
    delete ui;
}
