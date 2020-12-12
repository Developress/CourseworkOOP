#include "nounvisitedneighboursexception.h"

NoUnvisitedNeighboursException::NoUnvisitedNeighboursException()
{

}

const char *NoUnvisitedNeighboursException::what() const noexcept
{
    return "No neighbours for given cell";
}
