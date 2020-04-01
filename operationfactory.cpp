#include "operationfactory.h"

Operation OperationFactory::CreateOperation(char operationCharRepresentation)
{
    switch (operationCharRepresentation) {
    case '+':
        return Operation(std::plus<double>(), 0);

    case '-':
        return Operation(std::minus<double>(), 0);

    case '*':
        return Operation(std::multiplies<double>(), 1);

    case '/':
        return Operation(std::divides<double>(), 1);

    default:
        throw std::exception("Invalid char operator");
    }
}
