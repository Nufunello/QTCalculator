#ifndef OPERATIONWITHINDEX_H
#define OPERATIONWITHINDEX_H

#include "operation.h"

#include <vector>

namespace Operations {
    struct OperationWithIndex
    {
        inline OperationWithIndex(Operation operation, size_t index)
            : Operation{std::move(operation)}
            , Index{std::move(index)}
        {};

        Operation Operation;
        size_t    Index;
    };

    void transformToRelativeIndexes(std::vector<OperationWithIndex>& operationsWithIndexes);
    void transformOperationsWithIndexes(std::vector<OperationWithIndex>& operationsWithIndexes);
}

#endif // OPERATIONWITHINDEX_H
