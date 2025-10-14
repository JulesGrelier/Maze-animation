#ifndef MAZE
#define MAZE

#include <vector>
#include<list>
#include <cstdlib>
#include "square.h"


struct Maze
{
    Square squares[NB_V_SQUARE][NB_H_SQUARE];
    std::vector<int> usable_indices;
};

Maze newMaze();

void drawMaze(sf::RenderWindow &window, Maze maze);

void debugMaze(sf::RenderWindow &window, Maze maze);

Square& returnNeighbor(Maze &maze, Square currentSquare, Way way);

Square& selectSquareRandomly(Maze &maze);

///Replace the ID of each square that has the old ID for the new ID.
void propagateNewID(Maze &maze, int oldID, int newID);

Way chooseWay(Maze maze, Square currentSquare);

void RemoveFromUsable(Maze &maze, Square &square);

#endif