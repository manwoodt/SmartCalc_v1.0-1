#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton_0, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this,SLOT(digits_numbers()));

    connect(ui->pushButton_cos, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this,SLOT(digits_numbers()));

    connect(ui->pushButton_x, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_leftBracket, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_rightBracket, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_minus, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_plus, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_mul, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_unar_minus, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_deg, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this,SLOT(digits_numbers()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this,SLOT(digits_numbers()));
}

MainWindow::~MainWindow()
{
    delete ui;
}




  void MainWindow::digits_numbers(){
QPushButton *button = (QPushButton *) sender();
    ui->result->setText(ui->result->text() + button->text());
//    QString new_label;
//    double numbers;
//    numbers = (ui->result->text() + button->text()).toDouble();
//    new_label = QString::number(numbers,'g', 15);
//    ui->result->setText(new_label);

}



