#include "maze.h"

Maze::Maze()
{
    rows = 0;
    columns = 0;
    cells = nullptr;
}

Maze::Maze(int _rows, int _columns)
{
    srand(time(nullptr));
    rows = _rows;
    columns = _columns;

    cells = new Cell*[rows];

    for(int i = 0; i < rows; i++){
        cells[i] = new Cell[columns];
    }

    setNeighbours();
    cellsToVisit = rows * columns;
}

void Maze::setNeighbours(){
    {
        // set top left corner neighbours
        std::vector<Cell*> neighbours = {nullptr, &cells[0][1], &cells[1][0], nullptr};
        cells[0][0].setNeighbours(neighbours);
    }

    {
        // set top right corner neighbours
        std::vector<Cell*> neighbours = {nullptr, nullptr, &cells[1][columns-1], &cells[0][columns-2]};
        cells[0][columns-1].setNeighbours(neighbours);
    }

    {
        // set bottom left corner neighbours
        std::vector<Cell*> neighbours = {&cells[rows-2][0], &cells[rows-1][1], nullptr, nullptr};
        cells[rows-1][0].setNeighbours(neighbours);
    }

    {
        // set bottom right corner neighbours
        std::vector<Cell*> neighbours = {&cells[rows-2][columns-1], nullptr, nullptr, &cells[rows-1][columns-2]};
        cells[rows-1][columns-1].setNeighbours(neighbours);
    }

    for(int j = 1; j < columns-1; j++){
        //set top edge as deadend
        //cells[0][j]
        std::vector<Cell*> neighbours = {nullptr, &cells[0][j+1], &cells[1][j], &cells[0][j-1]};
        cells[0][j].setNeighbours(neighbours);
    }

    for(int i = 1; i < rows-1; i++){
        //set right edge as deadend
        //cells[i][columns-1]
        std::vector<Cell*> neighbours = {&cells[i-1][columns-1], nullptr, &cells[i+1][columns-1], &cells[i][columns-2]};
        cells[i][columns-1].setNeighbours(neighbours);
    }

    for(int j = 1; j < columns-1; j++){
        //set bottom edge as deadend
        //cells[rows-1][j]
        std::vector<Cell*> neighbours = {&cells[rows-2][j], &cells[rows-1][j+1], nullptr, &cells[rows-1][j-1]};
        cells[rows-1][j].setNeighbours(neighbours);
    }

    for(int i = 1; i < rows-1; i++){
        // set left edge as deadend
        //cells[i][0]
        std::vector<Cell*> neighbours = {&cells[i-1][0], &cells[i][1], &cells[i+1][0], nullptr};
        cells[i][0].setNeighbours(neighbours);
    }

    for(int i = 1; i < rows-1; i++){
        for(int j = 1; j < columns-1; j++){
            std::vector<Cell*> neighbours = {&cells[i-1][j], &cells[i][j+1], &cells[i+1][j], &cells[i][j-1]};
            cells[i][j].setNeighbours(neighbours);
        }
    }
}

void Maze::depthFirstSearch(){
    int row = rand() % rows;
    int column = rand() % columns;
    Cell *current = &cells[row][column];
    int visitedCells = 1;
    current->setVisited(true);
    while (visitedCells < cellsToVisit){
        if(current->hasUnvisitedNeighbours()){
            std::pair<int, Cell*> newCell = current->getRandomUnvisitedNeighbour();
            current->removeWall(newCell);
            cellsStack.push(current);
            current = newCell.second;
            visitedCells += 1;
            current->setVisited(true);
        } else {
            current = cellsStack.top();
            cellsStack.pop();
        }
    }
}

void Maze::binaryTree(){
    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            Cell *current = &cells[i][j];
            if(current->getRandomTopOrLeftNeighbour().second == nullptr){
                continue;
            } else {
                std::pair<int, Cell*> newCell = current->getRandomTopOrLeftNeighbour();
                current->removeWall(newCell);
            }
        }
    }
}

int** Maze::generateGrid(){
    int newRows = 2*rows + 1;
    int newColumns = 2*columns + 1;

    grid = new int*[newRows];
    for(int i = 0; i < newRows; i++){
        grid[i] = new int[newColumns];
    }

    for(int i = 0; i < newRows; i++){
        for(int j = 0; j < newColumns; j++){
            grid[i][j] = 0;
        }
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < columns; j++){
            grid[2*i+1][2*j+1] = 1;

            // destroy the top wall if needed
            if(!cells[i][j].getWalls()[Cell::TOP]){
                grid[2*i][2*j+1] = 1;
            }

            // destroy the right wall if needed
            if(!cells[i][j].getWalls()[Cell::RIGHT]){
                grid[2*i+1][2*j+2] = 1;
            }

            // destroy the bottom wall if needed
            if(!cells[i][j].getWalls()[Cell::BOTTOM]){
                grid[2*i+2][2*j+1] = 1;
            }

            // destroy the left wall if needed
            if(!cells[i][j].getWalls()[Cell::LEFT]){
                grid[2*i+1][2*j] = 1;
            }
        }
    }

    return grid;
}

int** Maze::generateMaze(int difficulty){
    switch (difficulty) {
    case LOW:{
        binaryTree();
        break;
    }
    case MEDIUM:
    case HIGH: {
        depthFirstSearch();
    }
    }
    return generateGrid();
}
