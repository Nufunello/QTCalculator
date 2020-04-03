#include "expressioncalculator.h"
#include "operationfactory.h"
#include "operationwithindex.h"
#include "operatordetecting.h"

#include <vector>
#include <algorithm>

using namespace Operations;

inline double getNumberFromSubstring(const std::string& str, int index, int count)
{
    std::string substr = str.substr(index, count);
    return stod(substr);
}

void moveIndexerToInnerExpressionEnd(const std::string& str, size_t& indexer)
{
    size_t cLeftBrackerNotClosed = 1;
    for (; cLeftBrackerNotClosed != 0; ++indexer)
    {
        const char& symbol = str[indexer];

        switch (symbol) {
            case INNER_EXPRESION_START:
                ++cLeftBrackerNotClosed;
                break;

            case INNER_EXPRESION_END:
                --cLeftBrackerNotClosed;
                break;
        }
    }
}

void transformInnerBracketExpression(std::string& str, size_t startInnerExpressionIndex)
{
    size_t endInnerExpresionIndex = startInnerExpressionIndex + 1;
    moveIndexerToInnerExpressionEnd(str, endInnerExpresionIndex);

    size_t startPos = startInnerExpressionIndex + 1;
    std::string innerExpressionStr = str.substr(startPos, endInnerExpresionIndex - startPos - 1);

    double value = CalculateExpression(std::move(innerExpressionStr));

    std::string calculatedStr = std::to_string(value);

    if (startInnerExpressionIndex != 0 && isdigit(str[startInnerExpressionIndex - 1]))
    {
        str[startInnerExpressionIndex++] = DEFAULT_BRACKET_OPERATOR;
    }

    str.replace(str.begin() + startInnerExpressionIndex, str.begin() + endInnerExpresionIndex, calculatedStr.begin(), calculatedStr.end());
}

void skipUnaryOperation(const std::string& str, size_t& indexer)
{
    if (isUnaryOperator(str[indexer]))
    {
        auto lastDigitPos = std::find_if(str.begin() + 1, str.end(), [](const char& symbol){
            return isOperator(symbol);
        });

        auto count = std::distance(str.begin(), lastDigitPos);
        indexer += count;
    }
}

void setOperationsWithIndexesAndNumbersFromString(std::string str, std::vector<OperationWithIndex>& operationsWithIndexes, std::vector<double>& numbers)
{
    int operationRelativeIndex = 0;
    size_t prevIndex = 0, currentIndex = 0;

    skipUnaryOperation(str, currentIndex);

    for (; currentIndex < str.size(); ++currentIndex)
    {
        const auto& symbol = str[currentIndex];

        switch (symbol) {
            case FLOAT_SEPARATOR:
                continue;

            case INNER_EXPRESION_START:
                transformInnerBracketExpression(str, currentIndex);
                if (!isUnaryOperator(str[currentIndex]))
                {
                    --currentIndex;
                }
                break;

            default:
                if (!isdigit(symbol))
                {
                    operationsWithIndexes.emplace_back(OperationFactory::CreateOperation(symbol), operationRelativeIndex++);

                    size_t count = currentIndex - prevIndex;
                    numbers.emplace_back(getNumberFromSubstring(str, prevIndex, count));
                    prevIndex = currentIndex + 1;
                }

                break;
        }
    }

    Operations::transformOperationsWithIndexes(operationsWithIndexes);

    const auto& lastSymbol = str[currentIndex];
    if (isdigit(lastSymbol))
    {
        ++currentIndex;
    }
    size_t count = currentIndex - prevIndex;
    numbers.emplace_back(getNumberFromSubstring(str, prevIndex, count));
}

double calculateOperationsWithNumbers(std::vector<OperationWithIndex> operations, std::vector<double> numbers)
{
    auto operationsEnd = operations.end();
    for (auto it = operations.begin(); it != operationsEnd; ++it)
    {
        auto& operation = *it;

        size_t currentIndex = operation.Index;
        numbers[currentIndex] = operation.Operation(numbers[currentIndex], numbers[currentIndex + 1]);

        numbers.erase(numbers.begin() + currentIndex + 1);
    }

    return numbers.front();
}

double CalculateExpression(std::string expression)
{
    size_t cOperations = std::count_if(expression.begin(), expression.end(), [](const char& symbol){ return isOperator(symbol); });

    std::vector<OperationWithIndex> operationsWithIndexes;
    operationsWithIndexes.reserve(cOperations);

    std::vector<double> numbers;
    numbers.reserve(cOperations + 1);

    setOperationsWithIndexesAndNumbersFromString(std::move(expression), operationsWithIndexes, numbers);

    return calculateOperationsWithNumbers(std::move(operationsWithIndexes), std::move(numbers));
}
