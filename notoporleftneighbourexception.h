#ifndef NOTOPORLEFTNEIGHBOUREXCEPTION_H
#define NOTOPORLEFTNEIGHBOUREXCEPTION_H

#include "cell.h"

class NoTopOrLeftNeighbourException: std::exception
{
public:
    NoTopOrLeftNeighbourException();
    const char *what() const noexcept;
};

#endif // NOTOPORLEFTNEIGHBOUREXCEPTION_H
