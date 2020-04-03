#include "expressioncalculator.h"
#include "operationfactory.h"
#include "operationwithindex.h"

#include <vector>
#include <string>

using namespace Operations;

inline double getNumberFromSubstring(const std::string& str, int index, int count)
{
    auto numberStr = str.substr(index, count);
    return atoi(numberStr.c_str());
}

std::tuple<std::vector<OperationWithIndex>, std::vector<double>> getOperationsWithIndexesAndNumbersFromString(const std::string& str)
{
    std::vector<double> numbers;
    std::vector<OperationWithIndex> operationsWithIndexes;

    int operationRelativeIndex = 0;
    size_t strSize = str.size(), prevIndex = 0, currentIndex = 0;
    for (; currentIndex < strSize; ++currentIndex)
    {
        const auto& symbol = str[currentIndex];

        if (!isdigit(symbol))
        {
            operationsWithIndexes.emplace_back(OperationFactory::CreateOperation(symbol), operationRelativeIndex++);

            size_t count = currentIndex - prevIndex;
            numbers.emplace_back(getNumberFromSubstring(str, prevIndex, count));
            prevIndex = currentIndex + 1;
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

double ExpressionCalculator::CalculateExpression(const std::string& expression)
{
    auto operationsAndNumbers = getOperationsWithIndexesAndNumbersFromString(expression);
    return calculateOperationsWithNumbers(std::move(std::get<0>(operationsAndNumbers)), std::move(std::get<1>(operationsAndNumbers)));
}
