#include "Cell.h"

sf::Vertex& Particle::getPixel()
{
	return pixel;
}

void Particle::setPixelPos(sf::Vector2f pos)
{
	pixel.position = pos;
}

pair<int, int> Particle::getPos()
{
	return pos;
}

void Particle::setPos(pair<int, int> newPos)
{
	pos = newPos;
}

bool Particle::getHasToMove()
{
	return hasToMove;
}

void Particle::setHasToMove(bool newMove)
{
	hasToMove = newMove;
}

bool Particle::getSolid()
{
	return solid;
}

void Particle::setSolid(bool solid)
{
	this->solid = solid;
}

sf::Color Particle::getColor()
{
	if (this)
		return color;
}

void Particle::setColor(sf::Color color)
{
	this->color = color;
	this->pixel.color = color;
}

Particle::~Particle()
{
}

SandParticle::SandParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	int randomYellow = rand() % 10 + 1;
	if (randomYellow % 2 == 0)
		this->setColor(sf::Color::Yellow);
	else
		this->setColor(sf::Color(224, 206, 0));
	this->setSolid(true);
	this->setHasToMove(true);
}

void SandParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	// Try moving the particle down using a constant speed (for now)
	bool moveDown = moveParticle(pair<int, int>(5, 0), particleMatrix, this);

	if (!moveDown) {
		// Try moving the particle down-left
		bool moveDownLeft = moveParticle(pair<int, int>(5, -5), particleMatrix, this);

		if (!moveDownLeft) {
			// Try moving the particle down-right
			bool moveDownRight = moveParticle(pair<int, int>(5, 5), particleMatrix, this);

			// The particle can't move in any direction for now, so it stays
			if (!moveDownRight) {
				setHasToMove(false);
				return;
			}
		}
	}
	setHasToMove(true);
}

SandParticle::~SandParticle()
{
}

bool moveParticle(pair<int, int> moveBy, vector<vector<Particle*>>& particleMatrix, Particle* particle)
{
	pair<int, int> particlePos = particle->getPos();

	// Now check how much it can move before being blocked by another particle

	// If the particle is falling down
	bool changed = false; int desiredY = particle->getPos().first + moveBy.first;
	if (moveBy.first > 0 && moveBy.second == 0) {
		int x = 1; 
		while (particle->getPos().first + x <= desiredY && x + particle->getPos().first < 500 && !particleMatrix[particlePos.first + x][particlePos.second]) {
			changed = true;
			particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
			particleMatrix[particlePos.first + x][particlePos.second] = particle;
			particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second));
			x++;
		}
	}

	// If the particle is flowing down-left
	desiredY = particle->getPos().first + moveBy.first;
	int desiredX = particle->getPos().second + moveBy.second;
	if (moveBy.first > 0 && moveBy.second < 0) {
		int x = 1, y = -1;
		while (particle->getPos().first + x <= desiredY && particle->getPos().second + y >= desiredX && x + particle->getPos().first < 500 && y + particle->getPos().second > 0 &&
			!particleMatrix[particlePos.first + x][particlePos.second + y]) {
			changed = true;
			particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
			particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
			particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			
			if (particle->getPos().first + x <= desiredY)
				x++;

			if (particle->getPos().second + y >= desiredX)
				y--;
		}
	}

	// If the particle is flowing down-right
	desiredY = particle->getPos().first + moveBy.first;
	desiredX = particle->getPos().second + moveBy.second;
	if (moveBy.first > 0 && moveBy.second > 0) {
		int x = 1, y = 1;
		while (particle->getPos().first + x <= desiredY && particle->getPos().second + y <= desiredX && x + particle->getPos().first < 500 && y + particle->getPos().second < 800 &&
			!particleMatrix[particlePos.first + x][particlePos.second + y]) {
			changed = true;
			particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
			particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
			particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			
			if (particle->getPos().first + x <= desiredY)
				x++;

			if (particle->getPos().second + y <= desiredX)
				y++;
		}
	}

	// If the particle is flowing left
	desiredX = particle->getPos().second + moveBy.second;
	if (moveBy.first == 0 && moveBy.second < 0) {
		int x = -1;
		while (particle->getPos().second + x >= desiredX && x + particle->getPos().second > 0 &&
			!particleMatrix[particlePos.first][particlePos.second + x]) {
			changed = true;
			particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
			particleMatrix[particlePos.first][particlePos.second + x] = particle;
			particle->setPos(pair<int, int>(particlePos.first, particlePos.second + x));
			x--;
		}
	}

	// If the particle is flowing right
	desiredY = particle->getPos().second + moveBy.second;
	if (moveBy.first == 0 && moveBy.second > 0) {
		int x = 1;
		while (particle->getPos().second + x <= desiredX && x + particle->getPos().second < 800 &&
			!particleMatrix[particlePos.first][particlePos.second + x]) {
			changed = true;
			particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
			particleMatrix[particlePos.first][particlePos.second + x] = particle;
			particle->setPos(pair<int, int>(particlePos.first, particlePos.second + x));
			x++;
		}
	}

	// Now, if at least one coordinate of moveBy is different than zero, then it means that the particle can be moved in some direction
	// Hence, we set the coordinates correspondingly and return true
	// Otherwise, we return false

	if (changed) {
		particle->setPixelPos(sf::Vector2f(particle->getPos().second, particle->getPos().first));
		return true;
	}
	else
		return false;
}

void ParticleSystem::addParticle(Particle* particle)
{
	pair<int, int> particlePos = particle->getPos();
	particleMatrix[particlePos.first][particlePos.second] = particle;
}

void ParticleSystem::update(int start, int finish)
{
	for (int x = 499; x >= 0; x--) {
		for (int y = finish; y >= start; y--) {
			if (particleMatrix[x][y] != nullptr) {
				particlesImage.setPixel(y, x, particleMatrix[x][y]->getColor());
				particleMatrix[x][y]->applyLaw(particleMatrix);
			}	
		}
	}
}

vector<vector<Particle*>>& ParticleSystem::getParticleMatrix()
{
	return particleMatrix;
}

void ParticleSystem::updateParticles()
{
	particlesTexture.update(particlesImage);
	particlesImage.create(800, 500, sf::Color(31, 31, 30));
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = NULL;

	// draw the vertex array
	sf::Sprite sprite;
	sprite.setTexture(particlesTexture);
	target.draw(sprite);
}

ParticleSystem::ParticleSystem()
{
	vector<Particle*> columns(800, nullptr);
	particleMatrix.resize(500, columns);

	particlesTexture.create(800, 500);
	particlesImage.create(800, 500);
}

ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < 500; i++)
		for (int j = 0; j < 800; j++)
			delete particleMatrix[i][j];
}

WaterParticle::WaterParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color::Blue);
	this->setSolid(false);
	this->setHasToMove(true);
}

void WaterParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
		// Try moving the particle down using a constant speed (for now)
		bool moveDown = moveParticle(pair<int, int>(5, 0), particleMatrix, this);

		if (!moveDown) {
			// Try moving the particle down-left
			bool moveDownLeft = moveParticle(pair<int, int>(10, -10), particleMatrix, this);

			if (!moveDownLeft) {
				// Try moving the particle down-right
				bool moveDownRight = moveParticle(pair<int, int>(10, 10), particleMatrix, this);

				// Try moving the particle left
				if (!moveDownRight) {
					bool moveLeft = moveParticle(pair<int, int>(0, -20), particleMatrix, this);

					// Try moving the particle right
					if (!moveLeft) {
						bool moveRight = moveParticle(pair<int, int>(0, 20), particleMatrix, this);

						// The particle can't move in any direction for now, so it stays
						if (!moveRight) {
							this->setHasToMove(false);
							return;
						}
					}
				}

			}
		}
		this->setHasToMove(true);
}

WaterParticle::~WaterParticle()
{
}

WoodParticle::WoodParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color(97, 58, 14));
	this->setSolid(true);
	this->setHasToMove(false);
}

void WoodParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
}

WoodParticle::~WoodParticle()
{
}
