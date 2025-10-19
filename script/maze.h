#ifndef MAZE
#define MAZE

#include <cstdlib>
#include "square.h"

class Maze
{

public :

    /*---------- ATTRIBUTS ----------*/

    Square m_squares[NB_V_SQUARE][NB_H_SQUARE];
    std::vector<int> m_usableIndices;
    
    std::vector<std::pair<int, int>> m_positionOfColorfulOnes;

    /*---------- FONCTIONS ----------*/

    Maze();

    void drawConstruction(sf::RenderWindow &window);
    void debug(sf::RenderWindow &window);
    void drawAnimation(sf::RenderWindow &window);

    Square& selectSquareRandomly();
    Way chooseWay(Square currentSquare);
    Square& returnNeighbor(Square currentSquare, Way way);

    void propagateNewID(int oldID, int newID);
    void RemoveFromUsable(Square &square);

    void makeOneCreationCycle(bool &continueCreation);

    std::vector<Way> returnNeighborsWithoutWall(Square square, std::vector<Way> ways);

    void makeOneAnimationCycle();
};


#endif