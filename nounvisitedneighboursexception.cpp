#include "nounvisitedneighboursexception.h"

NoUnvisitedNeighboursException::NoUnvisitedNeighboursException(long long cellAddress)
{
    message = "No unvisited neighbours for cell " + std::to_string(cellAddress);
}

const char *NoUnvisitedNeighboursException::what() const noexcept
{
    return message.c_str();
}
