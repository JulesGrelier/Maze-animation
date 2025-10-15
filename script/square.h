#ifndef SQUARE
#define SQUARE

#include "const.h"
#include <SFML/Graphics.hpp>
#include <utility>

struct Square
{
    int column; // x rank
    int row; // y rank

    sf::Vector2f position;

    int id;

    bool hasBottomWall;
    bool hasRightWall;
};

enum Way {
    BOTTOM,
    RIGHT,
    NOTHING,
};

Square newSquare(int column, int row, int id);

void drawSquare(sf::RenderWindow &window, Square square);

void animationSquare(sf::RenderWindow &window, Square square);

void debugSquare(sf::RenderWindow &window, Square square);

void breakWall(Square &square, Way way);

std::pair<bool,bool> defineBottomAndRigthAcces(Square square);

#endif