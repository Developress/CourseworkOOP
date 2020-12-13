#ifndef NOTOPORLEFTNEIGHBOUREXCEPTION_H
#define NOTOPORLEFTNEIGHBOUREXCEPTION_H

#include <string>
#include "cell.h"

class NoTopOrLeftNeighbourException: std::exception
{
    // Class for no top or left neighbour exception
public:
    NoTopOrLeftNeighbourException(long long cellAddress);
    const char *what() const noexcept;
private:
    std::string message;
};

#endif // NOTOPORLEFTNEIGHBOUREXCEPTION_H
