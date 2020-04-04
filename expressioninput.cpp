#include "expressioninput.h"

#include "operatordetecting.h"

#include <QKeyEvent>
#include <QRegExpValidator>

ExpressionInput::ExpressionInput(QWidget *parent)
    : QLineEdit(parent)
    , mask_{"[0-9\
             \\-\
             \\+\
             \\*\
             \\/\
             \\.\
             \\(\
             \\)\
             ]*"}
    , validator_{QRegExp(mask_.c_str())}
{
    this->setValidator(&validator_);
}
