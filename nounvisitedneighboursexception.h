#ifndef NOUNVISITEDNEIGHBOURSEXCEPTION_H
#define NOUNVISITEDNEIGHBOURSEXCEPTION_H

#include "cell.h"


class NoUnvisitedNeighboursException: std::exception
{
public:
    NoUnvisitedNeighboursException();
    const char *what() const noexcept;
};

#endif // NOUNVISITEDNEIGHBOURSEXCEPTION_H
