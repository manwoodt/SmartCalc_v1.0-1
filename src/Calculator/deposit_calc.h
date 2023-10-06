#ifndef DEPOSIT_CALC_H
#define DEPOSIT_CALC_H

#include <QWidget>

extern "C"{
#include "../calc.h"
}

namespace Ui {
class Deposit_calc;
}

class Deposit_calc : public QWidget
{
    Q_OBJECT

public:
    explicit Deposit_calc(QWidget *parent = nullptr);
    ~Deposit_calc();

signals:
 void firstWindow();

private:
    Ui::Deposit_calc *ui;
};

#endif // DEPOSIT_CALC_H
