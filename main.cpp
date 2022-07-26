#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <SFML/OpenGL.hpp>
#include "Cell.h"
#include <iostream>
#include <thread>

using std::thread;

int main()
{
    sf::Mutex mutex;

    // Elements
    bool sand = true, water = false, wood = false;

    // Create Particle System
    ParticleSystem particleSystem;

    // Render Window for drawing
    sf::RenderWindow window(sf::VideoMode(1200, 900), "SFML works!");
    window.setFramerateLimit(144);
    window.setPosition(sf::Vector2i(300, 50));

    // Check if user is clicking
    bool clicking = false;

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
        
        if (clicking && 0 < sf::Mouse::getPosition(window).x < 1200 && 0 < sf::Mouse::getPosition(window).y < 900) {
            if (sand) {
                for (int i = -10; i < 10; i++)
                    for (int j = -10; j < 10; j++) {
                        Particle* newParticle = new SandParticle(pair<int, int>((sf::Mouse::getPosition(window).y / 3) + i, (sf::Mouse::getPosition(window).x / 3) + j));
                        particleSystem.addParticle(newParticle);
                    }
            }
            if (water) {
                for (int i = -5; i < 5; i++)
                    for (int j = -5; j < 5; j++) {
                            Particle* newParticle = new WaterParticle(pair<int, int>((sf::Mouse::getPosition(window).y / 3) + i, (sf::Mouse::getPosition(window).x / 3) + j));
                            particleSystem.addParticle(newParticle);
                    }
            }
            if (wood) {
                for (int i = 0; i < 15; i++)
                    for (int j = 0; j < 15; j++) {
                        Particle* newParticle = new WoodParticle(pair<int, int>((sf::Mouse::getPosition(window).y / 3) + i, (sf::Mouse::getPosition(window).x / 3) + j));
                        particleSystem.addParticle(newParticle);
                    }
            }
        }
        window.clear(sf::Color(118, 118, 118));

        particleSystem.updateParticles();

        // Update Particles
        std::vector<thread> threads;
        int randomOffset = rand() % 20 + 1;

        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 0, 49 + randomOffset));
        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 100 + randomOffset, 149 + randomOffset));
        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 200 + randomOffset, 249 + randomOffset));
        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 300 + randomOffset, 349 + randomOffset));
        
        for (auto it = threads.begin(); it != threads.end(); ++it)
            it->join();

        threads.clear();

        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 50 + randomOffset, 99 + randomOffset));
        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 150 + randomOffset, 199 + randomOffset));
        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 250 + randomOffset, 299 + randomOffset));
        threads.push_back(thread(&ParticleSystem::update, &particleSystem, 350 + randomOffset, 399));

        for (auto it = threads.begin(); it != threads.end(); ++it)
            it->join();

        window.draw(particleSystem);
        window.display();
        
        currentTime = clock.getElapsedTime();
        fps = 1.0f / (currentTime.asSeconds() - previousTime.asSeconds());
        std::cout << fps << '\n';
        previousTime = currentTime;
    }

    return 0;
}
