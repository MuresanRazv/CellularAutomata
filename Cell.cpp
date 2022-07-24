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
	this->setColor(sf::Color::Yellow);
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

int determineChunk(int x, int y)
{
	int nr = 0;
	while (x > 0 || y > 0) {
		x -= 100;
		y -= 100;
		nr++;
	}

	return nr - 1;
}

void moveToNextChunk(int& x, int& y)
{
	while (y % 100 != 0)
		y--;
	while (x % 100 != 0)
		x--;
}

void resetChunks(const vector<vector<Particle*>>& particleMatrix, vector<Chunk>& chunks)
{
	for (int i = 0; i < chunks.size(); i++)
	{
		// Set bounds correctly
		int beginX = chunks[i].getX() + 100, beginY = chunks[i].getY() + 100;
		if (beginX == 500)
			beginX--;
		if (beginY == 800)
			beginY--;

		// Check current chunk
		bool checked = false;
		for (int x = beginX; x >= chunks[i].getX() && !checked; x--)
			for (int y = beginY; y >= chunks[i].getY() && !checked; y--) {
				if (particleMatrix[x][y] && particleMatrix[x][y]->getHasToMove())
				{
					chunks[i].setHasToUpdate(true);
					checked = true;
				}
			}
		if (!checked)
			chunks[i].setHasToUpdate(false);
	}
}

void ParticleSystem::addParticle(Particle* particle)
{
	pair<int, int> particlePos = particle->getPos();
	particleMatrix[particlePos.first][particlePos.second] = particle;
}

void ParticleSystem::update(int start, int finish)
{
			for (int x = 499; x >= 0; x--)
				for (int y = finish; y >= start; y--) {
					if (particleMatrix[x][y]) {
						particlesImage.setPixel(y, x, particleMatrix[x][y]->getPixel().color);
						particleMatrix[x][y]->applyLaw(particleMatrix);
					}
				}
}

vector<vector<Particle*>>& ParticleSystem::getParticleMatrix()
{
	return particleMatrix;
}

vector<Chunk>& ParticleSystem::getChunks()
{
	return chunks;
}

void ParticleSystem::updateParticles()
{
	particlesTexture.update(particlesImage);
	particlesImage.create(800, 500);
	/*mergedParticles.clear();
	for (int i = 499; i >= 0; i--)
		for (int j = 799; j >= 0; j--)
			if (particleMatrix[i][j] != nullptr) {
				if (particleMatrix[i][j]->getHasToMove())
					particleMatrix[i][j]->setColor(sf::Color::Red);
				else
					particleMatrix[i][j]->setColor(sf::Color::Blue);

					mergedParticles.append(particleMatrix[i][j]->getPixel());
			}*/
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

	for (int i = 0; i < 500; i += 100)
		for (int j = 0; j < 800; j += 100)
			chunks.push_back(Chunk(i, j));

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
	if (getHasToMove()) {

		// Try moving the particle down using a constant speed (for now)
		bool moveDown = moveParticle(pair<int, int>(5, 0), particleMatrix, this);

		if (!moveDown) {
			// Try moving the particle down-left
			bool moveDownLeft = moveParticle(pair<int, int>(5, -5), particleMatrix, this);

			if (!moveDownLeft) {
				// Try moving the particle down-right
				bool moveDownRight = moveParticle(pair<int, int>(5, 5), particleMatrix, this);

				// Try moving the particle left
				if (!moveDownRight) {
					bool moveLeft = moveParticle(pair<int, int>(0, -5), particleMatrix, this);

					// Try moving the particle right
					if (!moveLeft) {
						bool moveRight = moveParticle(pair<int, int>(0, 5), particleMatrix, this);

						// The particle can't move in any direction for now, so it stays
						if (!moveRight) {
							this->setHasToMove(false);
							return;
						}
					}
				}

			}
		}
	}
}

WaterParticle::~WaterParticle()
{
}

Chunk::Chunk(int x, int y)
{
	this->x = x;
	this->y = y;
}

bool Chunk::getHasToUpdate()
{
	return hasToUpdate;
}

void Chunk::setHasToUpdate(bool hasToUpdate)
{
	this->hasToUpdate = hasToUpdate;
}

int Chunk::getX()
{
	return x;
}

int Chunk::getY()
{
	return y;
}
