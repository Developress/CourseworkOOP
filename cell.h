#ifndef CELL_H
#define CELL_H

#include <vector>
#include <cstdlib>
#include <ctime>

class Cell
{
public:
    enum {NEIGHBOURS_COUNT=4};
    enum {TOP, RIGHT, BOTTOM, LEFT};
    Cell();
    bool isVisited() const;
    void setVisited(bool value);
    bool hasUnvisitedNeighbours();
    void setNeighbours(std::vector <Cell*> _neighbours);
    std::vector<std::pair<int, Cell *> > getUnvisitedNeighbours();
    std::pair<int, Cell *> getRandomUnvisitedNeighbour();
    void removeWall(std::pair<int, Cell *> neighbour);
    std::vector<bool> getWalls();
private:
    std::vector<Cell*> neighbours;
    std::vector<bool> walls;
    bool visited;

};

#endif // CELL_H
