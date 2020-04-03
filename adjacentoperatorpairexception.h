#ifndef ADJACENTOPERATORPAIREXCEPTION_H
#define ADJACENTOPERATORPAIREXCEPTION_H

#include <string>
#include <vcruntime_exception.h>

struct AdjacentOperatorPairException : public std::exception
{
public:
    inline AdjacentOperatorPairException(size_t startIndex)
        : StartIndex{std::move(startIndex)}
        , msg{"Adjacent pair of operators was found by index: " + std::to_string(StartIndex)}
    {}

public:
    size_t StartIndex;

    // exception interface
public:
    inline const char *what() const override
    {
        return msg.c_str();
    }

private:
    std::string msg;
};

#endif // ADJACENTOPERATORPAIREXCEPTION_H
