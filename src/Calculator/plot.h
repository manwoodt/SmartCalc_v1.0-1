#ifndef PLOT_H
#define PLOT_H

#include <QWidget>

extern "C"{
#include "../calc.h"
}

namespace Ui {
class plot;
}

class plot : public QWidget
{
    Q_OBJECT

public:
    explicit plot(QWidget *parent = nullptr);
    ~plot();

private:
    Ui::plot *ui;

signals:
 void firstWindow();
};

#endif // PLOT_H
