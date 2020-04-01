#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "expressioncalculator.h"

#include <QLineEdit>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLineEdit            txtExpression_;
    QLineEdit            txtCalculation_;

    ExpressionCalculator calculator_;

};
#endif // MAINWINDOW_H
