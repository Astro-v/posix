#ifndef QUERY_HPP
#define QUERY_HPP

#include <string>

struct Query
{
    std::string message;
    enum class Type
    {
        RECEIVE,
        SEND
    } type;

    Query(std::string message, Type type) : message(message), type(type) {}
};

#endif // QUERY_HPP