#ifndef OPERATORDETECTING_H
#define OPERATORDETECTING_H

#include <ctype.h>

namespace Operations {
    constexpr char UNARY_OPERATORS[] = {'+', '-'};

    constexpr char INNER_EXPRESION_START = '(';
    constexpr char INNER_EXPRESION_END = ')';

    constexpr char FLOAT_SEPARATOR = '.';

    constexpr char DEFAULT_BRACKET_OPERATOR = '*';

    inline bool isInnerExpressionStart(char symbol)
    {
        return symbol == INNER_EXPRESION_START;
    }

    inline bool isInnerExpressionEnd(char symbol)
    {
        return symbol == INNER_EXPRESION_END;
    }

    inline bool isInnerExpressionSymbol(char symbol)
    {
        return isInnerExpressionStart(symbol) || isInnerExpressionEnd(symbol);
    }

    inline bool isFloatSeparator(char symbol)
    {
        return symbol == FLOAT_SEPARATOR;
    }

    inline bool isUnaryOperator(char symbol)
    {
        for (const auto& unaryOperator : UNARY_OPERATORS)
        {
            if (symbol == unaryOperator)
                return true;
        }
        return false;
    }

    inline bool isOperator(char symbol)
    {
        return !isdigit(symbol) && !isFloatSeparator(symbol) && !isInnerExpressionSymbol(symbol);
    }
}


#endif // OPERATORDETECTING_H
