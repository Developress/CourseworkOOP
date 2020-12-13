#include "notoporleftneighbourexception.h"

NoTopOrLeftNeighbourException::NoTopOrLeftNeighbourException(long long cellAddress)
{
    message = "No top or left neighbour for cell " + std::to_string(cellAddress);
}

const char *NoTopOrLeftNeighbourException::what() const noexcept
{
    return message.c_str();
}
