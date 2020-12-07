#include "cell.h"

Cell::Cell()
{
    visited = false;
    // 0 - top neighbour
    // 1 - right neighbour
    // 2 - bottom neighbour
    // 3 - left neighbour
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
        if(neighbours[i] != nullptr && !neighbours[i]->isVisited()){
            return true;
        }
    }
    return false;
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

std::pair<int, Cell*> Cell::getRandomUnvisitedNeighbour(){
    std::vector<std::pair<int, Cell*> > unvisitedNeighbours = getUnvisitedNeighbours();
    int index = std::rand() % unvisitedNeighbours.size();
    return unvisitedNeighbours[index];
}

void Cell::setNeighbours(std::vector<Cell*> _neighbours){
    for(int i = 0; i < NEIGHBOURS_COUNT; i++){
        neighbours[i] = _neighbours[i];
    }
}

void Cell::removeWall(std::pair<int, Cell*> neighbour){
    int index = neighbour.first;
    int neighbourIndex;
    switch (index) {
        case TOP:
            neighbourIndex = BOTTOM;
            break;
        case RIGHT:
            neighbourIndex = LEFT;
            break;
        case BOTTOM:
            neighbourIndex = TOP;
            break;
        case LEFT:
            neighbourIndex = RIGHT;
            break;
    }
    walls[index] = false;
    if(neighbour.second != nullptr){
        (neighbour.second->walls)[neighbourIndex] =false;
    }
}


std::vector<bool> Cell::getWalls(){
    return walls;
}
