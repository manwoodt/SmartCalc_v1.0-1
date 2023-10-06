#include "deposit_calc.h"
#include "ui_deposit_calc.h"

Deposit_calc::Deposit_calc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Deposit_calc)
{
    ui->setupUi(this);
}

Deposit_calc::~Deposit_calc()
{
    delete ui;
}
