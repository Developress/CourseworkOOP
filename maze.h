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
    Maze();
    Maze(int _rows, int _columns);
    void depthFirstSearch();
    void binaryTree();
    int** generateGrid();
    int **generateMaze(int difficulty);
private:
    enum {LOW, MEDIUM, HIGH};
    int **grid;
    int rows;
    int columns;
    Cell **cells;
    int cellsToVisit;
    std::stack<Cell*> cellsStack;
    void setNeighbours();
};

#endif // MAZE_H
