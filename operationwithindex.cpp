#include "operationwithindex.h"
#include <algorithm>

void Operations::transformToRelativeIndexes(std::vector<OperationWithIndex> &operationsWithIndexes)
{
    for (size_t i = 0; i < operationsWithIndexes.size() - 1; ++i)
    {
        const size_t& outerIndex = operationsWithIndexes[i].Index;
        size_t counter = 1;

        for (size_t j = i + 1; j < operationsWithIndexes.size(); ++j)
        {
            auto& innerIndex = operationsWithIndexes[j].Index;
            if (innerIndex > outerIndex)
            {
                if (innerIndex >= counter)
                {
                    innerIndex -= counter++;
                }
            }
        }
    }
}

void Operations::transformOperationsWithIndexes(std::vector<OperationWithIndex> &operationsWithIndexes)
{
    std::make_heap(operationsWithIndexes.begin(), operationsWithIndexes.end(), [](const auto& lhs, const auto& rhs){
        return lhs.Operation < rhs.Operation;
    });
    std::sort(operationsWithIndexes.begin(), operationsWithIndexes.end(), [](const auto& lhs, const auto& rhs){
        return lhs.Operation == rhs.Operation ? lhs.Index > rhs.Index : false;
    });

    Operations::transformToRelativeIndexes(operationsWithIndexes);
}
