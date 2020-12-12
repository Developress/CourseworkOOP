#ifndef CELL_H
#define CELL_H

#include <vector>
#include <cstdlib>
#include <ctime>

class Cell
{
// The class for a maze cell
public:
    enum {NEIGHBOURS_COUNT=4};
    enum {TOP, RIGHT, BOTTOM, LEFT}; // 0 - top neighbour, 1 - right neighbour, 2 - bottom neighbour, 3 - left neighbour
    Cell();
    bool isVisited() const;
    void setVisited(bool value);
    bool hasUnvisitedNeighbours();
    void setNeighbours(std::vector <Cell*> _neighbours);
    void removeWall(std::pair<int, Cell *> neighbour);
    std::vector<bool> getWalls();
    std::pair<int, Cell *> getRandomUnvisitedNeighbour();
    std::pair<int, Cell*> getRandomTopOrLeftNeighbour();
private:
    std::vector<Cell*> neighbours; // The vector of neighbours of the cell
    std::vector<bool> walls; // The vector of the walls of the cell
    bool visited; // The bool value, which indicates whether the cell is visited (used for depth first search algorithm)
};

#endif // CELL_H
