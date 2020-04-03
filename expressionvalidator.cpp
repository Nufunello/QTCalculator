#include "expressionvalidator.h"

#include "operatordetecting.h"

#include "adjacentoperatorpairexception.h"
#include "innerexpressioncountexception.h"

#include <algorithm>

std::string::const_iterator findAdjacentOperatorPair(const std::string& str);
int innerExpressionBracketCounter(const std::string& str);

void ValidateExpression(const std::string &str)
{
    auto itAdjacentOperatorPair = findAdjacentOperatorPair(str);
    if (itAdjacentOperatorPair != str.end())
    {
        size_t indexOfIterator = std::distance(str.cbegin(), itAdjacentOperatorPair);
        throw AdjacentOperatorPairException(std::move(indexOfIterator));
    }

    auto cNotClosedInnerExpressions = innerExpressionBracketCounter(str);
    if (cNotClosedInnerExpressions != 0)
    {
        throw InnerExpressionCountException(cNotClosedInnerExpressions);
    }
}

std::string::const_iterator findAdjacentOperatorPair(const std::string& str)
{
    return std::adjacent_find(str.begin(), str.end(), [](const char& lsymbol, const char& rsymbol) {
        return Operations::isOperator(lsymbol) && Operations::isOperator(rsymbol);
    });
}

int innerExpressionBracketCounter(const std::string& str)
{
    int innerExpressionNotClosed = 0;

    for (const auto& symbol : str)
        switch (symbol) {
            case Operations::INNER_EXPRESION_START:
                ++innerExpressionNotClosed;
                break;

            case Operations::INNER_EXPRESION_END:
                --innerExpressionNotClosed;
                break;
        }

    return innerExpressionNotClosed;
}
