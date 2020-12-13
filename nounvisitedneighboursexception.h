#ifndef NOUNVISITEDNEIGHBOURSEXCEPTION_H
#define NOUNVISITEDNEIGHBOURSEXCEPTION_H

#include <string>
#include "cell.h"

class NoUnvisitedNeighboursException: std::exception
{
    // Class for no unvisited neighbours exception
public:
    NoUnvisitedNeighboursException(long long cellAddress);
    const char *what() const noexcept;
private:
    std::string message;
};

#endif // NOUNVISITEDNEIGHBOURSEXCEPTION_H
