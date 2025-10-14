#include <iostream>
#include "maze.h"

using namespace std;


int main(void)
{
    sf::RenderWindow window(sf::VideoMode({1080, 720}), "Maze animation");
    window.setFramerateLimit(60);

    if (WIDTH % SIZE_SQUARE != 0 || HEIGHT % SIZE_SQUARE != 0) {
        return 2;
    }

    Maze maze = newMaze();


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();

        for (int i = 0; i < 400; i++)
        {
            if (maze.usable_indices.size() == 0)
            {
                break;
            }

            Square &square = selectSquareRandomly(maze);
            Way way = chooseWay(maze, square);
            
            if (way == NOTHING)
            {
                RemoveFromUsable(maze, square);
                continue;
            }

            Square& neighbor = returnNeighbor(maze, square, way);

            breakWall(square, way);
            propagateNewID(maze, neighbor.id, square.id);
        }

        drawMaze(window, maze);
        window.display();
        
    } 
    return 0;
}