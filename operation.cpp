#include "operation.h"

using namespace Operations;

double Operation::operator()(const double &lhs, const double &rhs) const
{
    return operation_(lhs, rhs);
}

Operation::Operation(std::function<double (double, double)> operation, int priority)
    : operation_{std::move(operation)}
    , priority_{std::move(priority)}
{
}

