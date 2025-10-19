#ifndef SQUARE
#define SQUARE

#include "const.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <utility>
#include <vector>

enum Way {
    BOTTOM,
    RIGHT,
    TOP,
    LEFT,
    NOTHING,
};


class Square
{

public:

    /*---------- ATTRIBUTS ----------*/

    int m_column; // x rank
    int m_row; // y rank

    sf::Vector2f m_position;

    int m_id;

    bool m_hasBottomWall;
    bool m_hasRightWall;

    bool m_colorful;
    int m_percentage_brightness;

    /*---------- FONCTIONS ----------*/

    Square();
    Square(int column, int row, int id);

    void drawSquare(sf::RenderWindow &window);
    void animationSquare(sf::RenderWindow &window);

    void breakWall(Way way);

    std::pair<bool,bool> defineBottomAndRigthAcces();

    std::vector<Way> returnWaysToNeighbors();

    void reduct_brightness();
    sf::Color returnColor();
};


#endif