#include "maze.h"

using namespace std;

Maze::Maze()
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            int id = row * NB_H_SQUARE + column;
            m_squares[row][column] = Square(column, row, id);

            m_usableIndices.push_back(id);
        }
    }

    m_positionOfColorfulOnes.push_back(make_pair(0, 0));
    m_squares[0][0].m_colorful = true;
    m_squares[0][0].m_percentage_brightness = 100;

    
}

/*------------- VISUALISATION -------------*/

void Maze::drawConstruction(sf::RenderWindow &window)
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            m_squares[row][column].drawSquare(window);
        }
    }
}

void Maze::debug(sf::RenderWindow &window)
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            m_squares[row][column].debugSquare(window);
        }
    }
}

void Maze::drawAnimation(sf::RenderWindow &window)
{
    for (int row = 0; row < NB_V_SQUARE; row++)
    {
        for (int column = 0; column < NB_H_SQUARE; column++)
        {
            m_squares[row][column].animationSquare(window);
        }
    }
}



Square& Maze::selectSquareRandomly()
{
    int randomNumber = rand() % m_usableIndices.size();
    int randomIndex = m_usableIndices[randomNumber];

    int row = randomIndex/NB_H_SQUARE; //Round down automatically
    int column = randomIndex - row * NB_H_SQUARE;

    Square &randomSquare = m_squares[row][column];

    return randomSquare;
}


Square& Maze::returnNeighbor(Square currentSquare, Way way)
{
    int row = currentSquare.m_row;
    int column = currentSquare.m_column;

    switch (way)
    {
        case BOTTOM:
            if (row < NB_V_SQUARE) { return m_squares[row+1][column]; }
            break;

        case RIGHT:
            if (column < NB_H_SQUARE) { return m_squares[row][column+1]; }
            break;

        case TOP:
            if (row > 0) { return m_squares[row-1][column]; }
            break;

        case LEFT:
            if (column > 0) { return m_squares[row][column-1]; }
            break;

        default:
            break;
    }

    exit(1);
}


Way Maze::chooseWay(Square currentSquare)
{

    std::pair<bool, bool> accesses = currentSquare.defineBottomAndRigthAcces();
    bool differenceAtTheBottom = false, differenceAtTheRight = false;

    if (accesses.first)
    {
        Square &bottomNeighbor = returnNeighbor(currentSquare, BOTTOM);
        if (bottomNeighbor.m_id != currentSquare.m_id) { differenceAtTheBottom = true; }
    }

    if (accesses.second)
    {
        Square &rightNeighbor = returnNeighbor(currentSquare, RIGHT);
        if (rightNeighbor.m_id != currentSquare.m_id) { differenceAtTheRight = true; }
    }

    if (!differenceAtTheBottom & !differenceAtTheRight) {
        return NOTHING;
    }
    else if (differenceAtTheBottom & !differenceAtTheRight) {
        return BOTTOM;
    }
    else if (!differenceAtTheBottom & differenceAtTheRight) {
        return RIGHT;
    }
    else {
        if (rand() % 2 == 0) { return BOTTOM; } else { return RIGHT; }
    }
}


void Maze::RemoveFromUsable(Square &square)
{
    int index = square.m_row * NB_H_SQUARE + square.m_column;

    auto target = std::find(m_usableIndices.begin(), m_usableIndices.end(), index);

    if (target != m_usableIndices.end())
    {
        m_usableIndices.erase(target);
    }
}


void Maze::propagateNewID(int oldID, int newID)
{
    for (int row = 0; row < NB_V_SQUARE; row++) {
        for (int column = 0; column < NB_H_SQUARE; column++) {
            if (m_squares[row][column].m_id == oldID) {   
                m_squares[row][column].m_id = newID;
            }
        }
    }
}


void Maze::makeOneCreationCycle(bool &continueCreation)
{
    for (int i = 0; i < 500; i++)
    {
        if (m_usableIndices.size() == 0)
        {
            continueCreation = false;
            break;
        }

        Square &square = selectSquareRandomly();
        Way way = chooseWay(square);
        
        if (way == NOTHING)
        {
            RemoveFromUsable(square);
            continue;
        }

        square.breakWall(way);
        Square& neighbor = returnNeighbor(square, way);
        propagateNewID(neighbor.m_id, square.m_id);
    }
}


std::vector<Way> Maze::returnNeighborsWithoutWall(Square square, vector<Way> ways)
{
    std::vector<Way> output;

    for (auto const way : ways)
    {
        switch (way)
        {
            case BOTTOM:
                if (!square.m_hasBottomWall) { output.push_back(BOTTOM); }
                break;

            case RIGHT:
                if (!square.m_hasRightWall) { output.push_back(RIGHT); }
                break;

            case TOP:
                if (!(returnNeighbor(square, TOP).m_hasBottomWall)) { output.push_back(TOP); }
                break;

            case LEFT:
                if (!(returnNeighbor(square, LEFT).m_hasRightWall)) { output.push_back(LEFT); }
                break;
            
            default:
                break;
        }
    }

    return output;
}

void Maze::makeOneAnimationCycle()
{
    std::vector<std::pair<int, int>> new_positions;

    for (auto const position : m_positionOfColorfulOnes)
    {
        Square &square = m_squares[position.first][position.second];
        
        std::vector<Way> ways = square.returnWaysToNeighbors();
        ways = returnNeighborsWithoutWall(square, ways);
        
        
        for (auto const way : ways)
        {
            Square &neighbor = returnNeighbor(square, way);

            if (!neighbor.m_colorful)
            {

                neighbor.m_colorful = true;
                neighbor.m_percentage_brightness = 0;

                new_positions.push_back(make_pair(neighbor.m_row, neighbor.m_column));
            }   
            
        }
        
    }
    m_positionOfColorfulOnes = new_positions;    
}