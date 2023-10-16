#include "credit_calc.h"

#include "mainwindow.h"
#include "ui_credit_calc.h"

Credit_calc::Credit_calc(QWidget *parent)
    : QWidget(parent), ui(new Ui::Credit_calc) {
  ui->setupUi(this);
  connect(ui->pushButton_back, SIGNAL(clicked()), this, SLOT(back()));
  connect(ui->pushButton_calc, SIGNAL(clicked()), this, SLOT(equal()));
}

void Credit_calc::back() {
  this->close();
  emit firstWindow();
}

void Credit_calc::equal() {
  double loanAmount = ui->lineEdit_loanAmount->text().toDouble();
  double term = ui->lineEdit_term->text().toDouble();
  if (ui->comboBox_year_or_month->currentIndex() == 0) term *= 12;

  double interest_rate = ui->lineEdit_interestRate->text().toDouble();

  if (ui->lineEdit_loanAmount->text().isEmpty() ||
      ui->lineEdit_term->text().isEmpty() ||
      ui->lineEdit_interestRate->text().isEmpty()) {
    QMessageBox::warning(this, "Error:", "Заполни все поля");
  }

  double monthlyPayment = 0, totalPayment = 0, overpayment = 0;
  int error = 0;
  if (ui->comboBox_diff_or_ann->currentIndex() == 0)
    error =
        calculateDifferentiated(loanAmount, term, interest_rate,
                                &monthlyPayment, &totalPayment, &overpayment);
  else
    error = calculateAnnuity(loanAmount, term, interest_rate, &monthlyPayment,
                             &totalPayment, &overpayment);

  if (error == -1) {
    ui->lineEdit_monthlyPayment->setText("Error");
    ui->lineEdit_totalPayment->setText("Error");
    ui->lineEdit_overpayment->setText("Error");
  } else {
    QString monthlyPayment_str =
        QString::number(round(monthlyPayment * 100) / 100, 'g', 15);
    ui->lineEdit_monthlyPayment->setText(monthlyPayment_str);

    QString totalPayment_str =
        QString::number(round(totalPayment * 100) / 100, 'g', 15);
    ui->lineEdit_totalPayment->setText(totalPayment_str);

    QString overpayment_str =
        QString::number(round(overpayment * 100) / 100, 'g', 15);
    ui->lineEdit_overpayment->setText(overpayment_str);
  }
}

Credit_calc::~Credit_calc() { delete ui; }
