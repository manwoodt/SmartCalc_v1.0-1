#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDoubleValidator>
extern "C"{
#include "../calc.h"
}

#include "credit_calc.h"
#include "deposit_calc.h"
#include "plot.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    plot *plot_Window;
    Credit_calc *credit_Window;
    Deposit_calc *deposit_Window;

private slots:
    void digits_numbers();
    void math_func();
    void delete_all_text();
    void backspace();
    void equal();
    void plot_window();
    void credit_window();
    void deposit_window();
};

#endif // MAINWINDOW_H
