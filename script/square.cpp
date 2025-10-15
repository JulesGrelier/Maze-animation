#include "square.h"


Square newSquare(int column, int row, int id)
{
    Square square;

    square.column = column;
    square.row = row;

    square.position = sf::Vector2f(column * SIZE_SQUARE, row * SIZE_SQUARE);

    square.id = id;
    
    square.hasBottomWall = true;
    square.hasRightWall = true;

    return square;
}

void drawSquare(sf::RenderWindow &window, Square square)
{
    float bottomThickness = square.hasBottomWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;
    float rightThickness = square.hasRightWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;

    sf::RectangleShape rect(sf::Vector2f(rightThickness, bottomThickness));
    rect.setPosition(square.position);

    window.draw(rect);
}

void animationSquare(sf::RenderWindow &window, Square square)
{
    float bottomThickness = square.hasBottomWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;
    float rightThickness = square.hasRightWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;

    sf::RectangleShape rect(sf::Vector2f(rightThickness, bottomThickness));
    rect.setPosition(square.position);
    rect.setFillColor(sf::Color::Red);

    window.draw(rect);
}

void debugSquare(sf::RenderWindow &window, Square square)
{
    drawSquare(window, square);

    sf::Font arial("Arial.ttf");
    sf::Text text(arial, std::to_string(square.id), SIZE_SQUARE/2);
    text.setFillColor(sf::Color::Red);
    text.setPosition(square.position);

    window.draw(text);
}

void breakWall(Square &square, Way way)
{
    if (way == BOTTOM) 
    {
        square.hasBottomWall = false;
    }
    else if (way == RIGHT)
    {
        square.hasRightWall = false;
    }
}

std::pair<bool,bool> defineBottomAndRigthAcces(Square square)
{
    bool bottom_acces = square.hasBottomWall && square.row + 1 < NB_V_SQUARE;
    bool right_acces = square.hasRightWall && square.column + 1 < NB_H_SQUARE;

    printf("Square (%d, %d) : bottom acces = %d --- right acces = %d (sans tenir compte des voisins)\n", square.row, square.column, bottom_acces, right_acces);

    return std::make_pair(bottom_acces, right_acces);
}