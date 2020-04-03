#ifndef OPERATIONFACTORY_H
#define OPERATIONFACTORY_H

#include "operation.h"

namespace Operations {
    class OperationFactory
    {
    public:
        static Operations::Operation CreateOperation(char operationCharRepresentation);

    };
}


#endif // OPERATIONFACTORY_H
