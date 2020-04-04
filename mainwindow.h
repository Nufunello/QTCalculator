#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "expressioninput.h"

#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    ExpressionInput txtExpression_;
    QLineEdit       txtCalculation_;
    QLabel          lblErrors_;

};
#endif // MAINWINDOW_H
