#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <stack>
#include "cell.h"
#include <cstdlib>
#include <ctime>

class Maze
{
// The class for a maze
public:
    Maze();
    Maze(int _rows, int _columns);
    int **generateMaze(int difficulty);
private:
    enum {LOW, MEDIUM, HIGH}; // The enum with difficulty values, 0 - low, 1 - medium, 2 - high
    int rows; // The row count of the maze
    int columns; // The column count of the maze
    int **grid; // The maze grid, created after the maze is generated, consists of 0 and 1, 0 - represent walls, 1 - the cell which can be passed
    Cell **cells; // The 2 dimentional array of cells
    void setNeighbours();
    void depthFirstSearch();
    void binaryTree();
    void generateGrid();
};

#endif // MAZE_H
