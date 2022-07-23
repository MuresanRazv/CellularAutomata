#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/OpenGL.hpp>
#include "Cell.h"
#include <iostream>

int main()
{
    sf::Mutex mutex;

    // Elements
    bool sand = true, water = false, wood = false;

    // Create Particle System
    ParticleSystem particleSystem;

    // Render Window for drawing
    sf::RenderWindow window(sf::VideoMode(800, 500), "SFML works!");
    window.setFramerateLimit(144);

    // Check if user is clicking
    bool clicking = false;

    int x = 340, y = 230;
    moveToNextChunk(x, y);
    std::cout << x << " " << y;

    // Clock
    float fps;
    sf::Clock clock = sf::Clock();
    sf::Time previousTime = clock.getElapsedTime();
    sf::Time currentTime;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

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
                for (int i = 0; i < 11; i++)
                    for (int j = 0; j < 11; j++) {
                            Particle* newParticle = new SandParticle(pair<int, int>(sf::Mouse::getPosition(window).y + i, sf::Mouse::getPosition(window).x + j));
                            particleSystem.addParticle(newParticle);
                    }
            }
            if (water) {
                for (int i = 0; i < 11; i++)
                    for (int j = 0; j < 11; j++) {
                            Particle* newParticle = new WaterParticle(pair<int, int>(sf::Mouse::getPosition(window).y + i, sf::Mouse::getPosition(window).x + j));
                            particleSystem.addParticle(newParticle);
                    }
            }
        }
        window.clear(sf::Color(118, 118, 118));

        // Update Particles
        sf::Thread thread1(&ParticleSystem::updateFirstHalf, &particleSystem);
        sf::Thread thread2(&ParticleSystem::updateSecondHalf, &particleSystem);
        
        thread1.launch();
        thread2.launch();

        window.draw(particleSystem);
        window.display();
        
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        std::cout << fps << '\n';
        previousTime = currentTime;
    }

    return 0;
}
