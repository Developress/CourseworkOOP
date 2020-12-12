#ifndef CELL_H
#define CELL_H

#include <vector>
#include <cstdlib>
#include <ctime>

class Cell
{
public:
    enum {NEIGHBOURS_COUNT=4};
    // 0 - top neighbour, 1 - right neighbour, 2 - bottom neighbour, 3 - left neighbour
    enum {TOP, RIGHT, BOTTOM, LEFT};
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
    std::vector<Cell*> neighbours;
    std::vector<bool> walls;
    bool visited;
    std::vector<std::pair<int, Cell *> > getUnvisitedNeighbours();
};

#endif // CELL_H
