#include "expressioncalculator.h"
#include "operationfactory.h"
#include "operationwithindex.h"

#include <vector>
#include <string>
#include <algorithm>

using namespace Operations;

inline double getNumberFromSubstring(const std::string& str, int index, int count)
{
    auto numberStr = str.substr(index, count);
    return stod(numberStr);
}

std::tuple<std::vector<OperationWithIndex>, std::vector<double>> getOperationsWithIndexesAndNumbersFromString(std::string str)
{
    std::vector<double> numbers;
    std::vector<OperationWithIndex> operationsWithIndexes;

    int operationRelativeIndex = 0;
    size_t prevIndex = 0, currentIndex = 0;
    for (; currentIndex < str.size(); ++currentIndex)
    {
        const auto& symbol = str[currentIndex];

        if (!isdigit(symbol))
        {
            if (symbol == '(')
            {
                size_t cLeftBrackerNotClosed = 1;
                size_t leftBracketIndexer = currentIndex + 1;

                for (; cLeftBrackerNotClosed != 0; ++leftBracketIndexer)
                {
                    switch (str[leftBracketIndexer]) {
                    case ')':
                        --cLeftBrackerNotClosed;
                        break;

                    case '(':
                        ++cLeftBrackerNotClosed;
                        break;
                    }
                }

                ExpressionCalculator calculator;
                size_t startPos = currentIndex + 1;
                std::string innerExpression = str.substr(startPos, leftBracketIndexer - startPos - 1);
                double value = calculator.CalculateExpression(std::move(innerExpression));
                std::string calculatedStr = std::to_string(value);
                str.replace(str.begin() + currentIndex + 1, str.begin() + leftBracketIndexer, calculatedStr.begin(), calculatedStr.end());

                if (isdigit(str[currentIndex - 1]))
                {
                    str[currentIndex] = '*';
                    --currentIndex;
                }
            }
            else
            {
                if (symbol != '.')
                {
                    operationsWithIndexes.emplace_back(OperationFactory::CreateOperation(symbol), operationRelativeIndex++);

                    size_t count = currentIndex - prevIndex;
                    numbers.emplace_back(getNumberFromSubstring(str, prevIndex, count));
                    prevIndex = currentIndex + 1;
                }
            }
        }
    }

    Operations::transformOperationsWithIndexes(operationsWithIndexes);

    size_t count = currentIndex - prevIndex + 1;
    numbers.emplace_back(getNumberFromSubstring(str, prevIndex, count));

    return std::make_tuple<>(operationsWithIndexes, numbers);
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

double ExpressionCalculator::CalculateExpression(std::string expression)
{
    auto operationsAndNumbers = getOperationsWithIndexesAndNumbersFromString(std::move(expression));
    return calculateOperationsWithNumbers(std::move(std::get<0>(operationsAndNumbers)), std::move(std::get<1>(operationsAndNumbers)));
}
