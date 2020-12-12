#include "noneighbourcellexception.h"

NoNeighbourCellException::NoNeighbourCellException()
{

}

const char *NoNeighbourCellException::what() const noexcept
{
    return "No neighbour cell";
}
