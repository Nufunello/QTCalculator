#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , txtExpression_{this}
    , txtCalculation_{this}
{
    this->resize(600, 800);

    txtExpression_.move(0, 0);
    txtExpression_.resize(this->width(), 30);

    txtCalculation_.move(txtExpression_.x(), txtExpression_.y() + txtExpression_.height());
    txtCalculation_.resize(this->width(), 30);

    connect(&txtExpression_, &QLineEdit::returnPressed, [this](){
        std::string expression = txtExpression_.text().toStdString();

        double expressionCalculationResult = CalculateExpression(std::move(expression));

        txtCalculation_.setText(QString::number(expressionCalculationResult));
    });
}

MainWindow::~MainWindow()
{
}

