#ifndef EXPRESSIONINPUT_H
#define EXPRESSIONINPUT_H

#include <QLineEdit>
#include <QRegExpValidator>

class ExpressionInput : public QLineEdit
{
    Q_OBJECT
public:
    explicit ExpressionInput(QWidget *parent = nullptr);

signals:

private:
    std::string      mask_;
    QRegExpValidator validator_;

};

#endif // EXPRESSIONINPUT_H
