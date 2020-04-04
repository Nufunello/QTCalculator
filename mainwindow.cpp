#include "mainwindow.h"
#include "expressionvalidator.h"
#include "expressioncalculator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , txtExpression_{this}
    , txtCalculation_{this}
    , lblErrors_{this}
{
    this->resize(600, 800);

    txtExpression_.move(0, 0);
    txtExpression_.resize(this->width(), 30);

    txtCalculation_.move(txtExpression_.x(), txtExpression_.y() + txtExpression_.height());
    txtCalculation_.resize(this->width(), 30);

    lblErrors_.move(txtCalculation_.x(), txtCalculation_.y() + txtCalculation_.height());
    lblErrors_.resize(this->width(), 60);

    connect(&txtExpression_, &QLineEdit::returnPressed, [this](){
        std::string expression = txtExpression_.text().toStdString();

        try
        {
            lblErrors_.clear();
            ValidateExpression(expression);

            double expressionCalculationResult = CalculateExpression(std::move(expression));
            txtCalculation_.setText(QString::number(expressionCalculationResult));

        } catch (std::exception& exception)
        {
            lblErrors_.setText(exception.what());
        }
    });
}

MainWindow::~MainWindow()
{
}

