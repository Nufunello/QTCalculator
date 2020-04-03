#ifndef INNEREXPRESSIONCOUNTEXCEPTION_H
#define INNEREXPRESSIONCOUNTEXCEPTION_H

#include <vcruntime_exception.h>
#include <string>

struct InnerExpressionCountException : public std::exception
{
public:
    inline InnerExpressionCountException(int count)
        : Count(abs(count))
    {
        msg = (count > 0
                ? "Unclosed inner expressions(curve brackets): "
                : "Extra closing inner expressions tokens(curve brackets): "
                  ) + std::to_string(Count);
    }

public:
    size_t Count;

    // exception interface
public:
    inline const char *what() const override
    {
        return msg.c_str();
    }
private:
    std::string msg;
};

#endif // INNEREXPRESSIONCOUNTEXCEPTION_H
