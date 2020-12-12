#include "notoporleftneighbourexception.h"

NoTopOrLeftNeighbourException::NoTopOrLeftNeighbourException()
{

}

const char *NoTopOrLeftNeighbourException::what() const noexcept
{
    return "No top or left neighbour";
}
