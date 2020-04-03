#ifndef OPERATION_H
#define OPERATION_H

#include <functional>

namespace Operations {
    class Operation
    {
    public:
        double operator()(const double& lhs, const double& rhs) const;

    private:
        Operation(std::function<double(double, double)> operation, int priority);

    private:
        std::function<double(double, double)> operation_;
        int priority_;

    private:

        friend class OperationFactory;
        friend bool operator>(const Operation& lhs, const Operation& rhs);
        friend bool operator==(const Operation& lhs, const Operation& rhs);
    };

    inline bool operator>(const Operation& lhs, const Operation& rhs)
    {
        return lhs.priority_ > rhs.priority_;
    }

    inline bool operator==(const Operation& lhs, const Operation& rhs)
    {
        return lhs.priority_ == rhs.priority_;
    }
}

#endif // OPERATION_H
