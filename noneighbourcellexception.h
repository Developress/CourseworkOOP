#ifndef NONEIGHBOURCELLEXCEPTION_H
#define NONEIGHBOURCELLEXCEPTION_H

#include "cell.h"

class NoNeighbourCellException: std::exception
{
public:
    NoNeighbourCellException();
    const char *what() const noexcept;
};

#endif // NONEIGHBOURCELLEXCEPTION_H
