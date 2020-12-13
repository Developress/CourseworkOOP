#include "maze.h"

Maze::Maze()
{
    // The constructor with no parameters. Initializes the fields with initial values
    size = 0;
    grid = nullptr;
    cells = nullptr;
}

Maze::Maze(int _size)
{
    // The constructor with _size parameter. Initializes the fields with given values
    size = _size;

    // Alloc memory for cells array
    cells = new Cell*[size];

    for(int i = 0; i < size; i++){
        cells[i] = new Cell[size];
    }

    grid = nullptr;

    // set the neighbours for every cell
    setNeighbours();

    // set the seed for random
    srand(time(nullptr));
}

Maze::Maze(const Maze &_maze)
{
    // The copy constructor for maze class
    size = _maze.size;
    cells = new Cell*[size];

    for(int i = 0; i < size; i++){
        cells[i] = new Cell[size];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cells[i][j] = _maze.cells[i][j];
        }
    }

    grid = nullptr;

    // set the neighbours for every cell
    setNeighbours();

    // set the seed for random
    srand(time(nullptr));
}

Maze::~Maze()
{
    // The destructor of Maze class. Frees the memory allocated for cells and grid 2 dimentional arrays
    if(cells){
        for(int i = 0; i < size; i++){
            delete [] cells[i];
        }

        delete [] cells;

        cells = nullptr;
    }

    if(grid){
        for(int i = 0; i < 2*size + 1; i++){
            delete [] grid[i];
        }

        delete [] grid;
        grid = nullptr;
    }
}

void Maze::setNeighbours(){
    // This methods sets the neighbours for every cell
    {
        // set top left corner neighbours
        std::vector<Cell*> neighbours = {nullptr, &cells[0][1], &cells[1][0], nullptr};
        cells[0][0].setNeighbours(neighbours);
    }

    {
        // set top right corner neighbours
        std::vector<Cell*> neighbours = {nullptr, nullptr, &cells[1][size-1], &cells[0][size-2]};
        cells[0][size-1].setNeighbours(neighbours);
    }

    {
        // set bottom left corner neighbours
        std::vector<Cell*> neighbours = {&cells[size-2][0], &cells[size-1][1], nullptr, nullptr};
        cells[size-1][0].setNeighbours(neighbours);
    }

    {
        // set bottom right corner neighbours
        std::vector<Cell*> neighbours = {&cells[size-2][size-1], nullptr, nullptr, &cells[size-1][size-2]};
        cells[size-1][size-1].setNeighbours(neighbours);
    }

    for(int j = 1; j < size-1; j++){
        //set top edge as deadend
        std::vector<Cell*> neighbours = {nullptr, &cells[0][j+1], &cells[1][j], &cells[0][j-1]};
        cells[0][j].setNeighbours(neighbours);
    }

    for(int i = 1; i < size-1; i++){
        //set right edge as deadend
        std::vector<Cell*> neighbours = {&cells[i-1][size-1], nullptr, &cells[i+1][size-1], &cells[i][size-2]};
        cells[i][size-1].setNeighbours(neighbours);
    }

    for(int j = 1; j < size-1; j++){
        //set bottom edge as deadend
        std::vector<Cell*> neighbours = {&cells[size-2][j], &cells[size-1][j+1], nullptr, &cells[size-1][j-1]};
        cells[size-1][j].setNeighbours(neighbours);
    }

    for(int i = 1; i < size-1; i++){
        // set left edge as deadend
        std::vector<Cell*> neighbours = {&cells[i-1][0], &cells[i][1], &cells[i+1][0], nullptr};
        cells[i][0].setNeighbours(neighbours);
    }

    for(int i = 1; i < size-1; i++){
        for(int j = 1; j < size-1; j++){
            // set the neighbours for inner cells
            std::vector<Cell*> neighbours = {&cells[i-1][j], &cells[i][j+1], &cells[i+1][j], &cells[i][j-1]};
            cells[i][j].setNeighbours(neighbours);
        }
    }
}

void Maze::depthFirstSearch(){
    // This algorithm is used when generating maze of middle or high difficulty

    // Define the cells stack, to rollback when the deadend is met
    std::stack<Cell*> cellsStack;
    // Define the variable to indicate amount of cells to be visited
    int cellsToVisit = size*size;

    // Choose the random cell to start
    int row = rand() % size;
    int column = rand() % size;
    Cell *current = &cells[row][column];

    // Define the variable to indicate the amount of visited cells and mark the current cell as visited
    int visitedCells = 1;
    current->setVisited(true);

    while (visitedCells < cellsToVisit){
        // if the current cell has unvisited neighbours, then choose the random unvisited neighbour, remove the walls,
        // push the current cell to the stack, mark the neighbour cell as current and visited and increase the amount of visited cells
        try {
            current->hasUnvisitedNeighbours();
            std::pair<int, Cell*> newCell = current->getRandomUnvisitedNeighbour();
            current->removeWall(newCell);
            cellsStack.push(current);
            current = newCell.second;
            visitedCells += 1;
            current->setVisited(true);
        }  catch (NoUnvisitedNeighboursException& e) {
            // if the current cell has no unvisited neighbours, then mark it as current and pop it from the stack
            current = cellsStack.top();
            cellsStack.pop();
            qDebug(e.what());
        }
    }
}

void Maze::binaryTree(){
    // This algorithm is used when generating maze of low difficulty
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            // for every cell of the grid, choose the top or left neighbour, if no such neighbour exists, then go to next cell,
            // else remove the wall between the current cell and the chosen neighbour
            Cell *current = &cells[i][j];
            try {
                std::pair<int, Cell*> newCell = current->getRandomTopOrLeftNeighbour();
                current->removeWall(newCell);
            }  catch (NoTopOrLeftNeighbourException& e) {
                qDebug(e.what());
                continue;
            }
        }
    }
}

void Maze::generateGrid(){
    // This method is used to create a maze grid, after the maze is generated, which consists of 0 and 1,
    // 0 - represent walls, 1 - the cell which can be passed

    // Declare the variables with new dimentions of rows and columns
    int newRows = 2*size + 1;
    int newColumns = 2*size + 1;

    // Alloc the memory for the grid
    grid = new int*[newRows];
    for(int i = 0; i < newRows; i++){
        grid[i] = new int[newColumns];
    }

    // Initialise each item of the grid with 0
    for(int i = 0; i < newRows; i++){
        for(int j = 0; j < newColumns; j++){
            grid[i][j] = 0;
        }
    }

    // For each cell of the grid, destroy the needed walls and set the 1 instead of destroyed wall
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            // set the 1, because values under such indexes represent the cells themselves
            grid[2*i+1][2*j+1] = 1;

            // destroy the top wall if not exists
            if(!cells[i][j].getWalls()[Cell::TOP]){
                grid[2*i][2*j+1] = 1;
            }

            // destroy the right wall if not exists
            if(!cells[i][j].getWalls()[Cell::RIGHT]){
                grid[2*i+1][2*j+2] = 1;
            }

            // destroy the bottom wall if not exists
            if(!cells[i][j].getWalls()[Cell::BOTTOM]){
                grid[2*i+2][2*j+1] = 1;
            }

            // destroy the left wall if not exists
            if(!cells[i][j].getWalls()[Cell::LEFT]){
                grid[2*i+1][2*j] = 1;
            }
        }
    }
}

int** Maze::generateMaze(int difficulty){
    // This method generates a maze based on a given difficulty
    switch (difficulty) {
        // If difficulty is low, then generate the maze with binary tree algorithm
        case LOW:{
            binaryTree();
            break;
        }
        // If difficulty is medium or high, then generate the maze with depth first search algorithm
        case MEDIUM:
        case HIGH: {
            depthFirstSearch();
        }
    }

    // call the generate grid method to initialise the grid field, which will be returned
    generateGrid();
    return grid;
}

Maze &Maze::operator=(const Maze &_maze)
{
    // The overloaded operator= for maze class

    // if we are assing the object to itself, then simply return it
    if(this == &_maze){
        return *this;
    }

    // Free memory
    if(cells){
        for(int i = 0; i < size; i++){
            delete [] cells[i];
        }

        delete [] cells;

        cells = nullptr;
    }

    if(grid){
        for(int i = 0; i < 2*size + 1; i++){
            delete [] grid[i];
        }

        delete [] grid;
        grid = nullptr;
    }

    size = _maze.size;

    // Alloc memory again
    cells = new Cell*[size];

    for(int i = 0; i < size; i++){
        cells[i] = new Cell[size];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            cells[i][j] = _maze.cells[i][j];
        }
    }

    grid = nullptr;

    // set the neighbours for every cell
    setNeighbours();

    // Return the object
    return *this;
}
