#include "maze.h"

#include <iostream>
using namespace std;

Maze newMaze()
{
    Maze maze;

    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            int id = row * NB_H_SQUARE + column;
            maze.squares[row][column] = newSquare(column, row, id);
            maze.usable_indices.push_back(id);

            cout << "ID = " << id << endl;
        }
    }    
    
    return maze;
}

void drawMaze(sf::RenderWindow &window, Maze maze)
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            drawSquare(window, maze.squares[row][column]);
        }
    }
}

void debugMaze(sf::RenderWindow &window, Maze maze)
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            debugSquare(window, maze.squares[row][column]);
        }
    }
}

/*------------- LOGIQUE METIER -------------*/

Square& selectSquareRandomly(Maze &maze)
{
    int randomNumber = rand() % maze.usable_indices.size();
    int randomIndex = maze.usable_indices[randomNumber];

    int row = randomIndex/NB_H_SQUARE; //Round down automatically
    int column = randomIndex - row * NB_H_SQUARE;

    Square &randomSquare = maze.squares[row][column];

    printf("---------- DEBUT D'UN CYCLE ----------\n\n");
    printf("Index aléatoire : %d\nCoordonnées de l'index : (%d, %d)\nID du square : %d\n\n", randomIndex, row, column, randomSquare.id);

    return randomSquare;
}


Square& returnNeighbor(Maze &maze, Square currentSquare, Way way)
{
    int row = currentSquare.row;
    int column = currentSquare.column;

    switch (way)
    {
        case BOTTOM:
            if (row < NB_V_SQUARE) { return maze.squares[row+1][column]; }
            break;

        case RIGHT:
            if (column < NB_H_SQUARE) { return maze.squares[row][column+1]; }
            break;

        default:
            break;
    }

    exit(2);
}


Way chooseWay(Maze maze, Square currentSquare)
{

    printf("--------------------\n");
    printf("Determination de la way de l'id : %d\n", currentSquare.id);

    std::pair<bool, bool> accesses = defineBottomAndRigthAcces(currentSquare);

    printf("Accsesible en bas : %d ---- accesible à droite : %d\n", accesses.first, accesses.second);

    if (!accesses.first & !accesses.second) //If there isn't any acces
    {
        printf("WAY = NOTHING");
        return NOTHING;
    }

    else if (accesses.first & !accesses.second) //If there is just bottom acces
    {
        Square &bottomNeighbor = returnNeighbor(maze, currentSquare, BOTTOM);
        if (bottomNeighbor.id != currentSquare.id) {printf("WAY = BOTTOM"); return BOTTOM; } else { printf("WAY = NOTHING"); return NOTHING; }
    }

    else if (!accesses.first & accesses.second) //If there is just right acces
    {
        Square &rightNeighbor = returnNeighbor(maze, currentSquare, RIGHT);
        if (rightNeighbor.id != currentSquare.id) {printf("WAY = RIGHT"); return RIGHT; } else { printf("WAY = NOTHING"); return NOTHING; }
    }

    else if (accesses.first & accesses.second) //If there is the both acces
    {
        Square &bottomNeighbor = returnNeighbor(maze, currentSquare, BOTTOM);
        Square &rightNeighbor = returnNeighbor(maze, currentSquare, RIGHT);

        bool compatible_at_bottom = bottomNeighbor.id != currentSquare.id;
        bool compatible_on_right = rightNeighbor.id != currentSquare.id;

        if (compatible_at_bottom & compatible_on_right) {
            if (rand() % 2 == 0) { printf("WAY = BOTTOM"); return BOTTOM; } else { printf("WAY = RIGHT"); return RIGHT; }
        }

        else if (compatible_at_bottom & !compatible_on_right) {
            printf("WAY = BOTTOM");
            return BOTTOM;
        }

        else if (!compatible_at_bottom & compatible_on_right) {
            printf("WAY = RIGHT");
            return RIGHT;
        }

        else { return NOTHING; }
    }

    else {
        exit(3);
    }
    
}

void RemoveFromUsable(Maze &maze, Square &square)
{
    int index = square.row * NB_H_SQUARE + square.column;

    printf("\n\nSquare (%d, %d) a pour index : %d et doit être masquer\n\n", square.row, square.column, index);

    auto target = std::find(maze.usable_indices.begin(), maze.usable_indices.end(), index);

    if (target != maze.usable_indices.end())
    {
        maze.usable_indices.erase(target);
        cout << "Profil trouvé" << endl;
    }
}


void propagateNewID(Maze &maze, int oldID, int newID)
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            if (maze.squares[row][column].id == oldID)
            {   
                maze.squares[row][column].id = newID;
            }
            
        }
    }
}