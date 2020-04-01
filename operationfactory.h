#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

#include "operation.h"

class OperationFactory
{
public:
    static Operation CreateOperation(char operationCharRepresentation);

};

#endif // OPERATIONFACTORY_H
