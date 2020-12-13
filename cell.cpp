#include "cell.h"

Cell::Cell()
{
    // Constructor of Cell class. Initialises all the fields with initial values
    visited = false;

    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        neighbours.push_back(nullptr);
    }

    // initially the cell has all walls
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        walls.push_back(true);
    }

    // set the seed for random
    srand(time(nullptr));
}

bool Cell::isVisited() const
{
    return visited;
}

void Cell::setVisited(bool value)
{
    visited = value;
}

bool Cell::hasUnvisitedNeighbours(){
    // This method returns true if the cell has at least one unvisited neighbour
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        if(neighbours[i] != nullptr && !neighbours[i]->visited){
            return true;
        }
    }
    throw NoUnvisitedNeighboursException(reinterpret_cast<long long>(this));
}

void Cell::setNeighbours(std::vector<Cell*> _neighbours){
    // This method sets the pointers to neighbour cells
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        neighbours[i] = _neighbours[i];
    }
}

void Cell::removeWall(std::pair<int, Cell*> neighbour) {
    // This method removes the wall between the current cell and the neighbour cell

    // Declare the variables with direction of walls to break
    int wallToBreakFromCurrentCell = neighbour.first;
    int wallToBreakFromNeighbour;

    // Determine which wall to break from the neighbour basing on the wall to break from current cell
    switch (wallToBreakFromCurrentCell) {
        case TOP:
            wallToBreakFromNeighbour = BOTTOM;
            break;
        case RIGHT:
            wallToBreakFromNeighbour = LEFT;
            break;
        case BOTTOM:
            wallToBreakFromNeighbour = TOP;
            break;
        case LEFT:
            wallToBreakFromNeighbour = RIGHT;
            break;
    }

    // Break the wall from the current cell to the neighbour cell
    walls[wallToBreakFromCurrentCell] = false;

    // If the neighbour cell is defined, then break the wall from it to the current cell
    if(neighbour.second != nullptr){
        (neighbour.second->walls)[wallToBreakFromNeighbour] = false;
    }
}

std::vector<bool> Cell::getWalls(){
    return walls;
}


std::pair<int, Cell*> Cell::getRandomUnvisitedNeighbour(){
    // This method is used for depth first search algorithm and returns the random unvisited neighbour if exists
    // A vector with unvisited neihbours if exist
    std::vector<std::pair<int, Cell*> > unvisitedNeighbours;

    // For every neighbour check if it is not nullptr and not visited
    // If so, add the neighbour to the vector
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        if(neighbours[i] != nullptr && !neighbours[i]->isVisited()){
            unvisitedNeighbours.emplace_back(i, neighbours[i]);
        }
    }
    // Get the random item from unvisited neighbours list and return it
    if(unvisitedNeighbours.size() > 0){
        int index = std::rand() % unvisitedNeighbours.size();
        return unvisitedNeighbours[index];
    } else {
        throw NoUnvisitedNeighboursException(reinterpret_cast<long long>(this));
    }
}


std::pair<int, Cell*> Cell::getRandomTopOrLeftNeighbour(){
    // This method is used for binary tree algorithm and returns the top or left neighbour of the cell if exists
    // A vector with top and left neighbours if exist
    std::vector<std::pair<int, Cell*> > neededNeighbours;

    // If top neighbour exists, add it to the vector
    if(neighbours[TOP] != nullptr){
        neededNeighbours.emplace_back(TOP, neighbours[TOP]);
    }

    // If left neighbour exists, add it to the vector
    if(neighbours[LEFT] != nullptr){
        neededNeighbours.emplace_back(LEFT, neighbours[LEFT]);
    }

    // If the vector is not empty, then choose the random item from it, else return nullptr neighbour
    if(!neededNeighbours.empty()){
        int index = std::rand() % neededNeighbours.size();
        return neededNeighbours[index];
    } else {
        throw NoTopOrLeftNeighbourException(reinterpret_cast<long long>(this));
    }
}
