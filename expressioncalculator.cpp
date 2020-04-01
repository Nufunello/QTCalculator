#include "expressioncalculator.h"
#include "operationfactory.h"

#include <set>
#include <vector>
#include <algorithm>
#include <string>


struct OperationWithIndex
{
    OperationWithIndex(Operation operation, size_t index)
        : Operation{std::move(operation)}
        , Index{std::move(index)}
    {};

    Operation Operation;
    size_t    Index;
};

bool operator<(const OperationWithIndex& lhs, const OperationWithIndex& rhs)
{
    return lhs.Operation != rhs.Operation
            ? lhs.Operation < rhs.Operation
            : lhs.Index < rhs.Index;
}

std::vector<OperationWithIndex> getOperationsWithIndexesFromString(const std::string& str)
{
    std::vector<OperationWithIndex> operationsWithIndexes;

    int operationRelativeIndex = 0;
    for (size_t i = 0; i < str.size(); ++i)
    {
        const auto& symbol = str[i];

        if (!isalnum(symbol))
        {
            operationsWithIndexes.emplace_back(OperationFactory::CreateOperation(symbol), operationRelativeIndex++);
        }
    }

    std::make_heap(operationsWithIndexes.begin(), operationsWithIndexes.end());
    return operationsWithIndexes;
}

std::vector<double> getNumbersFromString(const std::string& str)
{
    std::vector<double> numbers;
    auto it = str.begin(), prev = it, end = str.end();

    while(true)
    {
        it = std::find_if(prev, end, [](const char& symbol){
            return !isalnum(symbol);
        });

        int numberStrSize = &it - &prev + 1;

        char *numberStr = new char[numberStrSize];

        std::copy(prev, it, numberStr);
        numberStr[numberStrSize - 1] = '\0';

        numbers.emplace_back(atoi(numberStr));

        delete []numberStr;

        if (it != end)
        {
            prev = std::move(++it);
        }
        else
        {
            break;
        }
    }

    return numbers;
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
        std::for_each(it + 1, operationsEnd, [currentIndex](auto& operation){
            if (currentIndex < operation.Index)
            {
                --operation.Index;
            }
        });
    }

    return numbers.front();
}

double ExpressionCalculator::CalculateExpression(const std::string& expression)
{
    std::vector<OperationWithIndex> operationsWithIndexes = getOperationsWithIndexesFromString(expression);
    std::vector<double> numbers = getNumbersFromString(expression);

    return calculateOperationsWithNumbers(std::move(operationsWithIndexes), std::move(numbers));
}
