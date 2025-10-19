#include "square.h"


Square::Square() : m_column(-1), m_row(-1), m_id(-1), m_hasBottomWall(true), m_hasRightWall(true), m_colorful(false), m_position(sf::Vector2f(0.f, 0.f))
{
}

Square::Square(int column, int row, int id) : m_column(column), m_row(row), m_id(id), m_hasBottomWall(true), m_hasRightWall(true), m_colorful(false)
{
    m_position = sf::Vector2f(column * SIZE_SQUARE, row * SIZE_SQUARE);
}

void Square::drawSquare(sf::RenderWindow &window)
{
    float bottomThickness = m_hasBottomWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;
    float rightThickness = m_hasRightWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;

    sf::RectangleShape rect(sf::Vector2f(rightThickness, bottomThickness));
    rect.setPosition(m_position);

    window.draw(rect);
}


void Square::animationSquare(sf::RenderWindow &window)
{
    float bottomThickness = m_hasBottomWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;
    float rightThickness = m_hasRightWall ? SIZE_SQUARE-THICKNESS : SIZE_SQUARE;

    sf::RectangleShape rect(sf::Vector2f(rightThickness, bottomThickness));
    rect.setPosition(m_position);

    rect.setFillColor( m_colorful ? returnColor() : sf::Color::Black );
    reduct_brightness();

    window.draw(rect);
}


void Square::debugSquare(sf::RenderWindow &window)
{
    drawSquare(window);

    sf::Font arial("Arial.ttf");
    sf::Text text(arial, std::to_string(m_id), SIZE_SQUARE/2);
    text.setFillColor(sf::Color::Red);
    text.setPosition(m_position);

    window.draw(text);
}

void Square::breakWall(Way way)
{
    if (way == BOTTOM) 
    {
        m_hasBottomWall = false;
    }
    else if (way == RIGHT)
    {
        m_hasRightWall = false;
    }
}

std::pair<bool,bool> Square::defineBottomAndRigthAcces()
{
    bool bottom_acces = m_hasBottomWall && m_row + 1 < NB_V_SQUARE;
    bool right_acces = m_hasRightWall && m_column + 1 < NB_H_SQUARE;

    return std::make_pair(bottom_acces, right_acces);
}

std::vector<Way> Square::returnWaysToNeighbors()
{
    std::vector<Way> ways;

    if (m_column > 0) { ways.push_back(LEFT); }
    if (m_column < NB_H_SQUARE-1) { ways.push_back(RIGHT); }
    if (m_row > 0) { ways.push_back(TOP); }
    if (m_row < NB_V_SQUARE-1) { ways.push_back(BOTTOM); }

    return ways;
}

void Square::reduct_brightness()
{
    m_percentage_brightness += STEP_FOR_PROCESS;

    if (m_percentage_brightness > 100)
    {
        m_colorful = false;
        m_percentage_brightness = 100;
    }
    
}

sf::Color Square::returnColor() {
    if (m_percentage_brightness < 60)
    {
        return sf::Color(
            RED_GRADIENT_1 * m_percentage_brightness + RED_VALUE_1,
            GREEN_GRADIENT_1 * m_percentage_brightness + GREEN_VALUE_1,
            BLUE_GRADIENT_1 * m_percentage_brightness + BLUE_VALUE_1
        );
    }
    else
    {
        return sf::Color(
            RED_GRADIENT_2 * (m_percentage_brightness-60) + RED_VALUE_2,
            GREEN_GRADIENT_2 * (m_percentage_brightness-60) + GREEN_VALUE_2,
            BLUE_GRADIENT_2 * (m_percentage_brightness-60) + BLUE_VALUE_2
        );
    }
    
}