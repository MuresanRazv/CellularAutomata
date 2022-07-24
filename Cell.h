#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <utility>
#include <vector>
#include <array>
#include <map>
#include <iostream>
#include <string>
#include <SFML/Graphics/Color.hpp>
#include <random>

using std::pair;
using std::vector;
using std::map;
using std::string;

class Particle {
private:
	sf::Vertex pixel;
	sf::Vector2f velocity;
	bool hasToMove;
	bool solid;
	pair<int, int> pos;
	sf::Color color;

public:
	// Apply law of current particle, law depends on the type of particle
	virtual void applyLaw(vector<vector<Particle*>>& particleMatrix) = 0;

	// Pixel Getter/Setter
	sf::Vertex& getPixel();
	void setPixelPos(sf::Vector2f pos);

	// Position Setter/Getter
	pair<int, int> getPos();
	void setPos(pair<int, int> newPos);

	// HasToMove Setter/Getter
	bool getHasToMove();
	void setHasToMove(bool newMove);

	// Solid Setter/Getter
	bool getSolid();
	void setSolid(bool solid);

	// Color Setter/Getter
	sf::Color getColor();
	void setColor(sf::Color color);

	virtual ~Particle();
};

class SandParticle : public Particle {
public:
	SandParticle(pair<int, int> pos);

	void applyLaw(vector<vector<Particle*>>& particleMatrix);

	~SandParticle();
};

class WaterParticle : public Particle {
public:
	WaterParticle(pair<int, int> pos);

	void applyLaw(vector<vector<Particle*>>& particleMatrix);

	~WaterParticle();
};

class WoodParticle : public Particle {
public:
	WoodParticle(pair<int, int> pos);

	void applyLaw(vector<vector<Particle*>>& particleMatrix);

	~WoodParticle();
};

class ParticleSystem : public sf::Drawable, public sf::Transformable {
public:
	void addParticle(Particle* particle);
	void update(int start, int finish);

	vector<vector<Particle*>>& getParticleMatrix();


	void updateParticles();

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	vector<vector<Particle*>> particleMatrix;
	
	sf::Texture particlesTexture;
	sf::Image particlesImage;

public:
	ParticleSystem();

	~ParticleSystem();
};



// Try to move the particle in a direction as much as possible
// Returns false if the particle is stuck
bool moveParticle(pair<int, int> moveBy, vector<vector<Particle*>>& particleMatrix, Particle* particle);