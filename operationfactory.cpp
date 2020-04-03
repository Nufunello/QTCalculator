#include "operationfactory.h"

constexpr int PLUS_PRIORITY = 0;
constexpr int MINUS_PRIORITY = 0;
constexpr int MULTIPLY_PRIORITY = 1;
constexpr int DIVIDE_PRIORITY = 1;

using namespace Operations;

Operation OperationFactory::CreateOperation(char operationCharRepresentation)
{
    switch (operationCharRepresentation) {
    case '+':
        return Operation(std::plus<double>(), PLUS_PRIORITY);

    case '-':
        return Operation(std::minus<double>(), MINUS_PRIORITY);

    case '*':
        return Operation(std::multiplies<double>(), MULTIPLY_PRIORITY);

    case '/':
        return Operation(std::divides<double>(), DIVIDE_PRIORITY);

    default:
        throw std::exception("Invalid char operator");
    }
}
