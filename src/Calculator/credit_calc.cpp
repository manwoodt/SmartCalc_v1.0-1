#include "credit_calc.h"
#include "ui_credit_calc.h"

Credit_calc::Credit_calc(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credit_calc)
{
    ui->setupUi(this);
}

Credit_calc::~Credit_calc()
{
    delete ui;
}
