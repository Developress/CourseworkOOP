#include "cell.h"

Cell::Cell()
{
    visited = false;

    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        neighbours.push_back(nullptr);
    }

    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        walls.push_back(true);
    }
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
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        if(neighbours[i] != nullptr && !neighbours[i]->visited){
            return true;
        }
    }
    return false;
}

void Cell::setNeighbours(std::vector<Cell*> _neighbours){
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        neighbours[i] = _neighbours[i];
    }
}

std::vector<std::pair<int, Cell*> > Cell::getUnvisitedNeighbours(){
    std::vector<std::pair<int, Cell*> > unvisitedNeighbours;
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        if(neighbours[i] != nullptr && !neighbours[i]->isVisited()){
            unvisitedNeighbours.emplace_back(i, neighbours[i]);
        }
    }
    return unvisitedNeighbours;
}

std::pair<int, Cell*> Cell::getRandomTopOrLeftNeighbour(){
    std::vector<std::pair<int, Cell*> > neededNeighbours;
    if(neighbours[TOP] != nullptr){
        neededNeighbours.emplace_back(TOP, neighbours[TOP]);
    }
    if(neighbours[LEFT] != nullptr){
        neededNeighbours.emplace_back(LEFT, neighbours[LEFT]);
    }
    if(!neededNeighbours.empty()){
        int index = std::rand() % neededNeighbours.size();
        return neededNeighbours[index];
    } else {
        return std::pair<int, Cell*>(-1, nullptr);
    }
}

std::pair<int, Cell*> Cell::getRandomUnvisitedNeighbour(){
    std::vector<std::pair<int, Cell*> > unvisitedNeighbours = getUnvisitedNeighbours();
    int index = std::rand() % unvisitedNeighbours.size();
    return unvisitedNeighbours[index];
}

void Cell::removeWall(std::pair<int, Cell*> neighbour){
    int wallToBreakFromCurrentCell = neighbour.first;
    int wallToBreakFromNeighbour;

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

    walls[wallToBreakFromCurrentCell] = false;

    if(neighbour.second != nullptr){
        (neighbour.second->walls)[wallToBreakFromNeighbour] = false;
    }

}

std::vector<bool> Cell::getWalls(){
    return walls;
}
