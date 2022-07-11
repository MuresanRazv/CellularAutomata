#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include "Cell.h"
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    window.setFramerateLimit(144);
    Universe universe = Universe();

    sf::RectangleShape pix(sf::Vector2f(2, 2));
    pix.setSize(sf::Vector2f(10, 10));

    bool clicking = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            
            if (event.type == sf::Event::MouseButtonPressed) {
                clicking = true;   
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                clicking = false;
            }
            
        }
        
        if (clicking) {
            Cell* newWCell = new SandCell(pair<int, int>(sf::Mouse::getPosition(window).y, sf::Mouse::getPosition(window).x));
            universe.addCell(newWCell);

        }

        window.clear(sf::Color(150, 150, 150, 255));
        universe.drawCells(window);
        
        window.display();
    }

    return 0;
}
