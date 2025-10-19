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

    Maze maze;
    bool begin = true;


    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear();

        if (begin)
        {
            maze.makeOneCreationCycle(begin);
            if (SHOW_CONSTRUCTION) { maze.drawConstruction(window); }
        } 
        else
        {       
            maze.makeOneAnimationCycle();
            maze.drawAnimation(window);
        }
        
        window.display();
    } 
    return 0;
}