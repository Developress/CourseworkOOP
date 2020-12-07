#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include "cell.h"
#include <cstdlib>
#include <ctime>

class Maze
{
public:
    Maze(int _rows, int _columns);
    void setNeighbours();
    void generateMaze();
    int** generateGrid();
private:
    std::stack<Cell*> cellsStack;
    Cell **cells;
    int **grid;
    int rows;
    int columns;
    int cellsToVisit;
};

#endif // MAZE_H
