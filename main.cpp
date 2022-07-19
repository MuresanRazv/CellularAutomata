#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/OpenGL.hpp>
#include "Cell.h"
#include <iostream>

int main()
{
    // Elements
    bool sand = true, water = false, wood = false;

    // Render Texture for static cells
    sf::RenderTexture staticCells;
    staticCells.create(800, 500);
    staticCells.clear(sf::Color::Black);

    // Render Window for drawing
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    window.setFramerateLimit(60);
    Universe universe;

    bool clicking = false;

    window.setActive(true);
    bool running = true;

    while (running)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                running = false;

            if (event.type == sf::Event::Resized)
                glViewport(0, 0, event.size.width, event.size.height);
            
            if (event.type == sf::Event::MouseButtonPressed) {
                clicking = true;   
            }
            if (event.type == sf::Event::MouseButtonReleased) {
                clicking = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                water = true;
                sand = false;
                wood = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                water = false;
                sand = true;
                wood = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::B)) {
                water = false;
                sand = false;
                wood = true;
            }

        }
        
        if (clicking) {
            if (sand) {
                for (int i = 0; i < 20; i++)
                    for (int j = 0; j < 20; j++) {
                        Cell* newWCell = new SandCell(pair<int, int>(sf::Mouse::getPosition(window).y + i, sf::Mouse::getPosition(window).x + j));
                        universe.addCell(newWCell);
                    }
            }
            if (water) {
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++) {
                        Cell* newWCell = new WaterCell(pair<int, int>(sf::Mouse::getPosition(window).y + i, sf::Mouse::getPosition(window).x + j));
                        universe.addCell(newWCell);
                    }
            }
            if (wood) {
                for (int i = 0; i < 5; i++)
                    for (int j = 0; j < 5; j++) {
                        Cell* newWCell = new WoodCell(pair<int, int>(sf::Mouse::getPosition(window).y + i, sf::Mouse::getPosition(window).x + j));
                        universe.addCell(newWCell);
                    }
            }
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw cells
        universe.drawCells(window, staticCells);
        
        // End frame
        window.display();
    }

    return 0;
}
