#include "Cell.h"

bool moveParticle(pair<int, int> moveBy, vector<vector<Particle*>>& particleMatrix, Particle* particle)
{
	pair<int, int> particlePos = particle->getPos();
	
	// Now check how much it can move before being blocked by another particle

	// If the particle is falling down
	bool changed = false; int desiredY = particle->getPos().first + moveBy.first;
	if (moveBy.first > 0 && moveBy.second == 0) {
		int x = 1; 
		while (particle->getPos().first + x <= desiredY && x + particle->getPos().first < 300) {
			// If the cell is empty we simply move the particle
			if (!particleMatrix[particlePos.first + x][particlePos.second]) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
				particleMatrix[particlePos.first + x][particlePos.second] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second));
			}
			// If the cell is not empty, but a liquid and the particle is a solid, it will submerge
			else if (particle->getSolid() && !particleMatrix[particlePos.first + x][particlePos.second]->getSolid()) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = particleMatrix[particlePos.first + x][particlePos.second];
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPos(pair<int, int>(particle->getPos().first, particle->getPos().second));
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPixelPos(sf::Vector2f(particle->getPos().second * 3, particle->getPos().first * 3));

				particleMatrix[particlePos.first + x][particlePos.second] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second));
			}
			// Else, the cell cannot move anymore so we stop looking
			else break;
			x++;
		}
	}

	// If the particle is flowing down-left
	desiredY = particle->getPos().first + moveBy.first;
	int desiredX = particle->getPos().second + moveBy.second;
	if (moveBy.first > 0 && moveBy.second < 0) {
		int x = 1, y = -1;
		while (particle->getPos().first + x <= desiredY && particle->getPos().second + y >= desiredX && x + particle->getPos().first < 300 && y + particle->getPos().second > 0) {
			// If the cell is empty we simply move the particle
			if (!particleMatrix[particlePos.first + x][particlePos.second + y]) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			// If the cell is not empty, but a liquid and the particle is a solid, it will submerge
			else if (particle->getSolid() && !particleMatrix[particlePos.first + x][particlePos.second + y]->getSolid()) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = particleMatrix[particlePos.first + x][particlePos.second + y];
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPos(pair<int, int>(particle->getPos().first, particle->getPos().second));
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPixelPos(sf::Vector2f(particle->getPos().second * 3, particle->getPos().first * 3));


				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			// Else, the cell cannot move anymore so we stop looking
			else break;
			
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
		while (particle->getPos().first + x <= desiredY && particle->getPos().second + y <= desiredX && x + particle->getPos().first < 300 && y + particle->getPos().second < 400) {
			// If the cell is empty we simply move the particle
			if (!particleMatrix[particlePos.first + x][particlePos.second + y]) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			// If the cell is not empty, but a liquid and the particle is a solid, it will submerge
			else if (particle->getSolid() && !particleMatrix[particlePos.first + x][particlePos.second + y]->getSolid()) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = particleMatrix[particlePos.first + x][particlePos.second + y];
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPos(pair<int, int>(particle->getPos().first, particle->getPos().second));
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPixelPos(sf::Vector2f(particle->getPos().second * 3, particle->getPos().first * 3));


				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			// Else, the cell cannot move anymore so we stop looking
			else break;

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
		while (particle->getPos().second + x <= desiredX && x + particle->getPos().second < 400 &&
			!particleMatrix[particlePos.first][particlePos.second + x]) {
			changed = true;
			particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
			particleMatrix[particlePos.first][particlePos.second + x] = particle;
			particle->setPos(pair<int, int>(particlePos.first, particlePos.second + x));
			x++;
		}
	}

	// If the particle is floating up-left
	if (moveBy.first < 0 && moveBy.second < 0) {
		desiredY = particle->getPos().first + moveBy.first;
		desiredX = particle->getPos().second + moveBy.second;
		int x = -1, y = -1;
		while (particle->getPos().first + x >= desiredY && particle->getPos().second + y >= desiredX && x + particle->getPos().first > 0 && y + particle->getPos().second > 0) {
			// If the cell is empty we simply move the particle
			if (!particleMatrix[particlePos.first + x][particlePos.second + y]) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			// If the cell is not empty, but a liquid and the particle is a gas, it will float through the water
			else if (!particle->getSolid() && !particleMatrix[particlePos.first + x][particlePos.second + y]->getSolid()) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = particleMatrix[particlePos.first + x][particlePos.second + y];
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPos(pair<int, int>(particle->getPos().first, particle->getPos().second));
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPixelPos(sf::Vector2f(particle->getPos().second * 3, particle->getPos().first * 3));

				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			else break;
			if (particle->getPos().first + x >= desiredY)
				x--;

			if (particle->getPos().second + y >= desiredX)
				y--;
		}
	}

	// If the particle is floating up-right
	if (moveBy.first < 0 && moveBy.second > 0) {
		desiredY = particle->getPos().first + moveBy.first;
		desiredX = particle->getPos().second + moveBy.second;
		int x = -1, y = 1;
		while (particle->getPos().first + x >= desiredY && particle->getPos().second + y <= desiredX && x + particle->getPos().first > 0 && y + particle->getPos().second < 400) {
			// If the cell is empty we simply move the particle
			if (!particleMatrix[particlePos.first + x][particlePos.second + y]) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = nullptr;
				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			// If the cell is not empty, but a liquid and the particle is a gas, it will float through the water
			else if (!particle->getSolid() && !particleMatrix[particlePos.first + x][particlePos.second + y]->getSolid()) {
				changed = true;
				particleMatrix[particle->getPos().first][particle->getPos().second] = particleMatrix[particlePos.first + x][particlePos.second + y];
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPos(pair<int, int>(particle->getPos().first, particle->getPos().second));
				particleMatrix[particle->getPos().first][particle->getPos().second]->setPixelPos(sf::Vector2f(particle->getPos().second * 3, particle->getPos().first * 3));

				particleMatrix[particlePos.first + x][particlePos.second + y] = particle;
				particle->setPos(pair<int, int>(particlePos.first + x, particlePos.second + y));
			}
			else break;
			if (particle->getPos().first + x >= desiredY)
				x--;

			if (particle->getPos().second + y <= desiredX)
				y++;
		}
	}

	// Now, if at least one coordinate of moveBy is different than zero, then it means that the particle can be moved in some direction
	// Hence, we set the coordinates correspondingly and return true
	// Otherwise, we return false

	if (changed) {
		particle->setPixelPos(sf::Vector2f(particle->getPos().second * 3, particle->getPos().first * 3));
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
	for (int x = 299; x >= 0; x--) {
		for (int y = finish; y >= start; y--) {
			if (particleMatrix[x][y] != nullptr) {
				for (int i = 0; i < 3; i++)
					for (int j = 0; j < 3; j++)
						particlesImage.setPixel(y * 3 + i, x * 3 + j, particleMatrix[x][y]->getColor());
				if (particleMatrix[x][y]) {
					particleMatrix[x][y]->applyLaw(particleMatrix);
				}
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
	particlesImage.create(1200, 900, sf::Color(31, 31, 30));
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
	vector<Particle*> columns(400, nullptr);
	particleMatrix.resize(300, columns);

	particlesTexture.create(1200, 900);
	particlesImage.create(1200, 900);
}

ParticleSystem::~ParticleSystem()
{
	for (int i = 0; i < 300; i++)
		for (int j = 0; j < 400; j++)
			delete particleMatrix[i][j];
}

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
	pos.first = newPos.first;
	pos.second = newPos.second;
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

int Particle::getVelocity()
{
	return velocity;
}

void Particle::setVelocity(int velocity)
{
	this->velocity = velocity;
}

bool Particle::getFlammable()
{
	return flammable;
}

void Particle::setFlammable(bool flammable)
{
	this->flammable = flammable;
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
	this->setVelocity(2);
	this->setFlammable(false);
}

void SandParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	if (getVelocity() < 5)
		setVelocity(getVelocity() * ACCELERATION - FRICTION);

	// Try moving the particle down using a constant speed (for now)
	bool moveDown = moveParticle(pair<int, int>(getVelocity(), 0), particleMatrix, this);

	if (!moveDown) {
		// Try moving the particle down-left
		bool moveDownLeft = moveParticle(pair<int, int>(getVelocity(), -getVelocity()), particleMatrix, this);

		if (!moveDownLeft) {
			// Try moving the particle down-right
			bool moveDownRight = moveParticle(pair<int, int>(getVelocity(), getVelocity()), particleMatrix, this);

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

WaterParticle::WaterParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color::Blue);
	this->setSolid(false);
	this->setHasToMove(true);
	this->setVelocity(10);
	this->setFlammable(false);
}

void WaterParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
		// Try moving the particle down using a constant speed (for now)
		bool moveDown = moveParticle(pair<int, int>(getVelocity(), 0), particleMatrix, this);

		if (!moveDown) {
			// Try moving the particle down-left
			bool moveDownLeft = moveParticle(pair<int, int>(getVelocity(), -getVelocity()), particleMatrix, this);

			if (!moveDownLeft) {
				// Try moving the particle down-right
				bool moveDownRight = moveParticle(pair<int, int>(getVelocity(), getVelocity()), particleMatrix, this);

				// Try moving the particle left
				if (!moveDownRight) {
					bool moveLeft = moveParticle(pair<int, int>(0, -getVelocity()), particleMatrix, this);

					// Try moving the particle right
					if (!moveLeft) {
						bool moveRight = moveParticle(pair<int, int>(0, getVelocity()), particleMatrix, this);

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
	int randBrown = rand() % 8 + 1;
	switch (randBrown)
	{
	case 8: {
		this->setColor(sf::Color(51, 34, 22));
		break;
	}
	default:
		this->setColor(sf::Color(82, 48, 24));
		break;
	}
	this->setSolid(true);
	this->setHasToMove(false);
	this->setFlammable(true);
}

void WoodParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
}

WoodParticle::~WoodParticle()
{
}

FireParticle::FireParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color(150, 0, 0));
	this->setSolid(true);
	this->setHasToMove(false);
	this->setFlammable(false);
	this->setVelocity(8);

	// Start lifetime
	this->lifetime.restart();
}

void FireParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	// For a more realistic perspective we change the colors of fire based on a 'fire' color palette
;	int randFire = rand() % 5 + 1;

	switch (randFire)
	{
	case 1:
	{
		this->setColor(sf::Color(255, 0, 0));
		break;
	}

	case 2:
	{
		this->setColor(sf::Color(255, 90, 0));
		break;
	}

	case 3:
	{
		this->setColor(sf::Color(255, 154, 0));
		break;
	}

	case 4:
	{
		this->setColor(sf::Color(255, 206, 0));
		break;
	}
	
	case 5:
	{
		this->setColor(sf::Color(255, 232, 8));
		break;
	}

	default:
		break;
	}

	// If the fire particle is not solid ( for example oil which is on fire ) it will move just like a liquid
	if (!this->getSolid()) {
		// Try moving the particle down using a constant speed
		bool moveDown = moveParticle(pair<int, int>(getVelocity(), 0), particleMatrix, this);

		if (!moveDown) {
			// Try moving the particle down-left
			bool moveDownLeft = moveParticle(pair<int, int>(getVelocity(), -getVelocity()), particleMatrix, this);

			if (!moveDownLeft) {
				// Try moving the particle down-right
				bool moveDownRight = moveParticle(pair<int, int>(getVelocity(), getVelocity()), particleMatrix, this);

				// Try moving the particle left
				if (!moveDownRight) {
					bool moveLeft = moveParticle(pair<int, int>(0, -getVelocity()), particleMatrix, this);

					// Try moving the particle right
					if (!moveLeft) {
						bool moveRight = moveParticle(pair<int, int>(0, getVelocity()), particleMatrix, this);

						// The particle can't move in any direction for now, so it stays
						if (!moveRight) {
							this->setHasToMove(false);
						}
					}
				}
			}
		}
		this->setHasToMove(true);
	}

	// Once a particle 'catches' on fire, it will be switched with a fire particle and purged, once the lifetime
	// of the fire particle reaches its limit, it will be purged as well

	// If the fire particle lifetime has passed its limit, then we purge it, and fire will stop spreading from that particle
	// After fire is purged, it will produce smoke (could produce smoke at a constant rate but for now I'll keep it simple)
	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 2);
	if (lifetime.getElapsedTime().asSeconds() > FIRE_LIFETIME - r) {
		particleMatrix[getPos().first][getPos().second] = new SmokeParticle(pair<int, int>(getPos().first, getPos().second));
		delete this;
	}

	else {
		// Look in every direction to spread the fire, if the particle can catch fire, also spread in random directions
		int randDir = rand() % 8 + 1;

		pair<int, int> pos = getPos();
		bool up = (pos.first - 1 > 0 && particleMatrix[pos.first - 1][pos.second] && particleMatrix[pos.first - 1][pos.second]->getFlammable());
		bool down = (pos.first + 1 < 300 && particleMatrix[pos.first + 1][pos.second] && particleMatrix[pos.first + 1][pos.second]->getFlammable());
		bool left = (pos.second - 1 > 0 && particleMatrix[pos.first][pos.second - 1] && particleMatrix[pos.first][pos.second - 1]->getFlammable());
		bool right = (pos.second + 1 < 400 && particleMatrix[pos.first][pos.second + 1] && particleMatrix[pos.first][pos.second + 1]->getFlammable());
		bool up_left = (pos.first - 1 > 0 && pos.second - 1 > 0 && particleMatrix[pos.first - 1][pos.second - 1] && particleMatrix[pos.first - 1][pos.second - 1]->getFlammable());
		bool up_right = (pos.first - 1 > 0 && pos.second + 1 < 400 && particleMatrix[pos.first - 1][pos.second + 1] && particleMatrix[pos.first - 1][pos.second + 1]->getFlammable());
		bool down_left = (pos.first + 1 < 300 && pos.second - 1 > 0 && particleMatrix[pos.first + 1][pos.second - 1] && particleMatrix[pos.first + 1][pos.second - 1]->getFlammable());
		bool down_right = (pos.first + 1 < 300 && pos.second + 1 < 400 && particleMatrix[pos.first + 1][pos.second + 1] && particleMatrix[pos.first + 1][pos.second + 1]->getFlammable());

		// Set each particle that is flammable on fire (will have to deal with water afterwards, which will produce steam)

		if (up && randDir == 1)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first - 1, pos.second));

			if (particleMatrix[pos.first - 1][pos.second]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first - 1][pos.second];
			particleMatrix[pos.first - 1][pos.second] = fireParticle;
		}

		if (down && randDir == 2)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first + 1, pos.second));

			if (particleMatrix[pos.first + 1][pos.second]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first + 1][pos.second];
			particleMatrix[pos.first + 1][pos.second] = fireParticle;
		}

		if (left && randDir == 3)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first, pos.second - 1));

			if (particleMatrix[pos.first][pos.second - 1]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first][pos.second - 1];
			particleMatrix[pos.first][pos.second - 1] = fireParticle;
		}

		if (right && randDir == 4)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first, pos.second + 1));

			if (particleMatrix[pos.first][pos.second + 1]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first][pos.second + 1];
			particleMatrix[pos.first][pos.second + 1] = fireParticle;
		}

		if (up_left && randDir == 5)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first - 1, pos.second - 1));

			if (particleMatrix[pos.first - 1][pos.second - 1]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first - 1][pos.second - 1];
			particleMatrix[pos.first - 1][pos.second - 1] = fireParticle;
		}

		if (up_right && randDir == 6)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first - 1, pos.second + 1));

			if (particleMatrix[pos.first - 1][pos.second + 1]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first - 1][pos.second + 1];
			particleMatrix[pos.first - 1][pos.second + 1] = fireParticle;
		}

		if (down_left && randDir == 7)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first + 1, pos.second - 1));

			if (particleMatrix[pos.first + 1][pos.second - 1]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first + 1][pos.second - 1];
			particleMatrix[pos.first + 1][pos.second - 1] = fireParticle;
		}

		if (down_right && randDir == 8)
		{
			Particle* fireParticle = new FireParticle(pair<int, int>(pos.first + 1, pos.second + 1));

			if (particleMatrix[pos.first + 1][pos.second + 1]->getSolid())
				fireParticle->setSolid(true);
			else
				fireParticle->setSolid(false);

			delete particleMatrix[pos.first + 1][pos.second + 1];
			particleMatrix[pos.first + 1][pos.second + 1] = fireParticle;
		}
	}
}

FireParticle::~FireParticle()
{
}

SmokeParticle::SmokeParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color(180, 180, 180));
	this->setSolid(false);
	this->setHasToMove(true);
	this->setFlammable(false);

	// Start lifetime
	this->lifetime.restart();
}

void SmokeParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	// If the lifetime of the smoke has passed it's limit, purge it
	if (lifetime.getElapsedTime().asSeconds() > SMOKE_LIFETIME) {
		particleMatrix[getPos().first][getPos().second] = nullptr;
		return;
	}

	// I will give the particle a 50% chance to float up-left first time and same for up-right
	// I can't make it float straight up because of the way cells are processed: bottom-top

	int randUp = rand() % 2 + 1;
	int randX = rand() % 5 + 1;
	int randY = rand() % 5 + 1;
	if (randUp % 2 == 0) {
		randUp = -1;
		randX *= -1;
	}
	else {
		randUp = 1;
		randY *= -1;
	}

	int randSpeed = rand() % 5 + 1;

	// Try moving the particle up
	bool moveUp = moveParticle(pair<int, int>(-1 * randSpeed + randX, randUp * randSpeed + randY), particleMatrix, this);

	if (!moveUp) {
		// Try moving the particle left
		bool moveLeft = moveParticle(pair<int, int>(0, -1), particleMatrix, this);

		// Try moving the particle right
		if (!moveLeft) {
			bool moveRight = moveParticle(pair<int, int>(0, 1), particleMatrix, this);

			// The particle can't move in any direction for now, so it stays
			if (!moveRight) {
				this->setHasToMove(false);
				return;
			}
		}
	}
	this->setHasToMove(true);
}

SmokeParticle::~SmokeParticle()
{
}

AcidParticle::AcidParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color(145, 200, 47));
	this->setSolid(false);
	this->setHasToMove(true);
	this->setFlammable(false);
	this->setVelocity(6);
	this->limit = rand() % 2 + 1;
}

void AcidParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	if (current > limit) {
		particleMatrix[getPos().first][getPos().second] = nullptr;
		return;
	}

	// Try moving the particle down using a constant speed (for now)
	bool moveDown = moveParticle(pair<int, int>(getVelocity(), 0), particleMatrix, this);

	if (!moveDown) {

		if (getPos().first + 1 < 300 && !dynamic_cast<AcidParticle*>(particleMatrix[getPos().first + 1][getPos().second])) {
			particleMatrix[getPos().first + 1][getPos().second] = this;
			particleMatrix[getPos().first][getPos().second] = nullptr;
			setPos(pair<int, int>(getPos().first + 1, getPos().second));
			current++;
		}

		// Try moving the particle down-left
		bool moveDownLeft = moveParticle(pair<int, int>(getVelocity() - 4, -getVelocity() + 4), particleMatrix, this);

		if (!moveDownLeft) {
			// Try moving the particle down-right
			bool moveDownRight = moveParticle(pair<int, int>(getVelocity() - 4, getVelocity() - 4), particleMatrix, this);

			// Try moving the particle left
			if (!moveDownRight) {
				bool moveLeft = moveParticle(pair<int, int>(0, -getVelocity() + 4), particleMatrix, this);

				// Try moving the particle right
				if (!moveLeft) {
					bool moveRight = moveParticle(pair<int, int>(0, getVelocity() - 4), particleMatrix, this);

					// The particle can't move in any direction for now, so it stays
					if (!moveRight) {
						if (getPos().first - 1 > 0 && !dynamic_cast<AcidParticle*>(particleMatrix[getPos().first - 1][getPos().second]) &&
							particleMatrix[getPos().first - 1][getPos().second]) {
							particleMatrix[getPos().first - 1][getPos().second] = nullptr;
							current++;
						}
						else {
							this->setHasToMove(false);
							return;
						}
					}
				}
			}
		}
	}
	this->setHasToMove(true);
}

AcidParticle::~AcidParticle()
{
}

LavaParticle::LavaParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);

	int randLava = rand() % 4 + 1;
	switch (randLava)
	{
	case 1:
	{
		this->setColor(sf::Color(255, 37, 0));
		break;
	}
	case 2:
	{
		this->setColor(sf::Color(255, 102, 0));
		break;
	}
	case 3:
	{
		this->setColor(sf::Color(242, 242, 23));
		break;
	}
	case 4:
	{
		this->setColor(sf::Color(234, 92, 15));
		break;
	}
	default:
		break;
	}
	this->setSolid(false);
	this->setHasToMove(true);
	this->setFlammable(false);
	this->setVelocity(4);
}

void LavaParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	// Since lava is really hot, we will also set on fire any particle that is flammable and next to it
	int up = getPos().first - 1, down = getPos().first + 1;
	int left = getPos().second - 1, right = getPos().second + 1;

	// Up
	if (up > 0 && particleMatrix[up][getPos().second] && particleMatrix[up][getPos().second]->getFlammable()) {
		Particle* fireParticle = new FireParticle(pair<int, int>(up, getPos().second));

		if (particleMatrix[up][getPos().second]->getSolid())
			fireParticle->setSolid(true);

		delete particleMatrix[up][getPos().second];
		particleMatrix[up][getPos().second] = fireParticle;
	}
	// Down
	if (down < 300 && particleMatrix[down][getPos().second] && particleMatrix[down][getPos().second]->getFlammable()) {
		Particle* fireParticle = new FireParticle(pair<int, int>(down, getPos().second));

		if (particleMatrix[down][getPos().second]->getSolid())
			fireParticle->setSolid(true);

		delete particleMatrix[down][getPos().second];
		particleMatrix[down][getPos().second] = fireParticle;
	}
	// Down-Left
	if (down < 300 && left > 0 && particleMatrix[down][left] && particleMatrix[down][left]->getFlammable()) {
		Particle* fireParticle = new FireParticle(pair<int, int>(down, left));

		if (particleMatrix[down][left]->getSolid())
			fireParticle->setSolid(true);

		delete particleMatrix[down][left];
		particleMatrix[down][left] = fireParticle;
	}
	// Down-Right
	if (down < 300 && right < 400 && particleMatrix[down][right] && particleMatrix[down][right]->getFlammable()) {
		Particle* fireParticle = new FireParticle(pair<int, int>(down, right));

		if (particleMatrix[down][right]->getSolid())
			fireParticle->setSolid(true);

		delete particleMatrix[down][right];
		particleMatrix[down][right] = fireParticle;
	}
	// Left
	if (left > 0 && particleMatrix[getPos().first][left] && particleMatrix[getPos().first][left]->getFlammable()) {
		Particle* fireParticle = new FireParticle(pair<int, int>(getPos().first, left));

		if (particleMatrix[getPos().first][left]->getSolid())
			fireParticle->setSolid(true);

		delete particleMatrix[getPos().first][left];
		particleMatrix[getPos().first][left] = fireParticle;
	}
	// Right
	if (right < 400 && particleMatrix[getPos().first][right] && particleMatrix[getPos().first][right]->getFlammable()) {
		Particle* fireParticle = new FireParticle(pair<int, int>(getPos().first, right));

		if (particleMatrix[getPos().first][right]->getSolid())
			fireParticle->setSolid(true);

		delete particleMatrix[getPos().first][right];
		particleMatrix[getPos().first][right] = fireParticle;
	}

	// Try moving the particle down using a constant speed
	bool moveDown = moveParticle(pair<int, int>(getVelocity(), 0), particleMatrix, this);

	if (!moveDown) {
		// Try moving the particle down-left
		bool moveDownLeft = moveParticle(pair<int, int>(getVelocity(), -getVelocity()), particleMatrix, this);

		if (!moveDownLeft) {
			// Try moving the particle down-right
			bool moveDownRight = moveParticle(pair<int, int>(getVelocity(), getVelocity()), particleMatrix, this);

			// Try moving the particle left
			if (!moveDownRight) {
				bool moveLeft = moveParticle(pair<int, int>(0, -getVelocity()), particleMatrix, this);

				// Try moving the particle right
				if (!moveLeft) {
					bool moveRight = moveParticle(pair<int, int>(0, getVelocity()), particleMatrix, this);

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

LavaParticle::~LavaParticle()
{
}

OilParticle::OilParticle(pair<int, int> pos)
{
	this->setPixelPos(sf::Vector2f(pos.second, pos.first));
	this->setPos(pos);
	this->setColor(sf::Color(90, 74, 24));
	this->setSolid(false);
	this->setHasToMove(true);
	this->setFlammable(true);
	this->setVelocity(10);
}

void OilParticle::applyLaw(vector<vector<Particle*>>& particleMatrix)
{
	// Try moving the particle down using a constant speed
	bool moveDown = moveParticle(pair<int, int>(getVelocity(), 0), particleMatrix, this);

	if (!moveDown) {
		// Try moving the particle down-left
		bool moveDownLeft = moveParticle(pair<int, int>(getVelocity(), -getVelocity()), particleMatrix, this);

		if (!moveDownLeft) {
			// Try moving the particle down-right
			bool moveDownRight = moveParticle(pair<int, int>(getVelocity(), getVelocity()), particleMatrix, this);

			// Try moving the particle left
			if (!moveDownRight) {
				bool moveLeft = moveParticle(pair<int, int>(0, -getVelocity()), particleMatrix, this);

				// Try moving the particle right
				if (!moveLeft) {
					bool moveRight = moveParticle(pair<int, int>(0, getVelocity()), particleMatrix, this);

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

OilParticle::~OilParticle()
{
}
