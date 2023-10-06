#ifndef CREDIT_CALC_H
#define CREDIT_CALC_H

#include <QWidget>

extern "C"{
#include "../calc.h"
}

namespace Ui {
class Credit_calc;
}

class Credit_calc : public QWidget
{
    Q_OBJECT

public:
    explicit Credit_calc(QWidget *parent = nullptr);
    ~Credit_calc();

signals:
 void firstWindow();

private:
    Ui::Credit_calc *ui;
};

#endif // CREDIT_CALC_H
