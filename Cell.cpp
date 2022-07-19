#include "Cell.h"

Universe::Universe()
{
	vector<Cell*> columns(800, nullptr);
	cellMatrix.resize(500, columns);
	
	movingCells.create(800, 500);
	staticCells.create(800, 500);

	movingCells.clear(sf::Color::Black);
	staticCells.clear(sf::Color::Black);
}

Universe::~Universe()
{
	for (int i = 499; i >= 0; i--)
		for (int j = 799; j >= 0; j--)
			delete cellMatrix[i][j];
}

void Universe::universeLaws(sf::RenderTexture& texture)
{
	// Clear moving cells texture
	movingCells.clear(sf::Color(0, 0, 0, 0));

	for (int i = 499; i >= 0; i--)
		for (int j = 799; j >= 0; j--)
			if (cellMatrix[i][j] != nullptr)
			{
				// Draw to moving cells texture
				if (cellMatrix[i][j]->getMove()) {
					movingCells.draw(cellMatrix[i][j]->pix);
					cellMatrix[i][j]->applyLaw(cellMatrix);
				}

				// Draw to static cells texture, because the cell is not moving
				else {
					if (!cellMatrix[i][j]->drewStatic) {
						staticCells.draw(cellMatrix[i][j]->pix);
						cellMatrix[i][j]->drewStatic = true;
					}
				}
			}

	// End frame for moving cells
	movingCells.display();

	// End frame for static cells
	staticCells.display();

	// Draw moving and static cells
	const sf::Texture& movingTexture = movingCells.getTexture();
	const sf::Texture& staticTexture = staticCells.getTexture();
	sf::Sprite movingSprite(movingTexture), staticSprite(staticTexture);
	texture.draw(staticSprite);
	texture.draw(movingSprite);
	

}

void Universe::drawCells(sf::RenderWindow &window, sf::RenderTexture& texture)
{
	// Draw static Cells
	texture.clear();
	universeLaws(texture);
	texture.display();
	const sf::Texture& staticCells = texture.getTexture();
	sf::Sprite sprite(staticCells);
	window.draw(sprite);			
}

void Universe::addCell(Cell* cell)
{
	cellMatrix[cell->getPos().first][cell->getPos().second] = cell;
}

bool SandCell::tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix)
{
	// Check horizontal bound
	bool inBoundsX = (moveValue.second > 0 && moveValue.second < 800);
	while (!inBoundsX) {
		if (moveValue.second > pos.second)
			moveValue.second--;
		else
			moveValue.second++;
		inBoundsX = (moveValue.second > 0 && moveValue.second < 800);
	}

	// Check vertical bound
	bool inBoundsY = (moveValue.first > 0 && moveValue.first < 500);
	while (!inBoundsY) {
		moveValue.first--;
		inBoundsY = (moveValue.first > 0 && moveValue.first < 500);
	}

	// Down
	if (moveValue.first > pos.first && moveValue.second == pos.second)
	{
		int i = 1;
		bool changed = false;
		while (pos.first != moveValue.first && pos.first + i < 500 && (!cellMatrix[pos.first + i][pos.second] || !cellMatrix[pos.first + i][pos.second]->solid)) {
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.first += 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed) {
			return false;
		}
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

	// Down left
	else if (moveValue.first > pos.first && moveValue.second < pos.second) {
		int i = 1, j = 1;
		bool changed = false;
		while (moveValue.first != pos.first && moveValue.second != pos.second && (!cellMatrix[pos.first + i][pos.second - j] || !cellMatrix[pos.first + i][pos.second - j]->solid))
		{
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.first += 1;
			pos.second -= 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed) {
			return false;
		}

		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

	// Down right
	else if (moveValue.first > pos.first && moveValue.second > pos.second) {
		int i = 1, j = 1;
		bool changed = false;
		while (moveValue.first != pos.first && moveValue.second != pos.second && (!cellMatrix[pos.first + i][pos.second + j] || !cellMatrix[pos.first + i][pos.second + j]->solid))
		{
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.first += 1;
			pos.second += 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed) {
			return false;
		}
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

}

SandCell::SandCell(pair<int, int> pos)
{
	this->pos = pos;
	this->solid = true;
	this->pix.setPosition(pos.second, pos.first);
	this->pix.setFillColor(sf::Color::Yellow);
	this->pix.setSize(sf::Vector2f(1, 1));
}

pair<int, int> SandCell::getPos()
{
	return pos;
}

void SandCell::applyLaw(vector<vector<Cell*>>& cellMatrix)
{

	int moveValue = velocity;

	if (move) {

		// Check down
		bool moveDown = this->tryToMove(pair<int, int>(pos.first + moveValue, pos.second), cellMatrix);
		if (!moveDown) {

			// Check down-left
			bool moveDownLeft = this->tryToMove(pair<int, int>(pos.first + moveValue, pos.second - moveValue), cellMatrix);
			if (!moveDownLeft) {

				// Check down-right
				bool moveDownRight = this->tryToMove(pair<int, int>(pos.first + moveValue, pos.second + moveValue), cellMatrix);
				if (!moveDownRight) {

					// Cannot move in any direction, it is blocked
					move = false;
				}
			}
		}
	}
}

SandCell::~SandCell()
{
}

bool WaterCell::tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix)
{
	// Check horizontal bound
	bool inBoundsX = (moveValue.second > 0 && moveValue.second < 800);
	while (!inBoundsX) {
		if (moveValue.second > pos.second)
			moveValue.second--;
		else
			moveValue.second++;
		inBoundsX = (moveValue.second > 0 && moveValue.second < 800);
	}

	// Check vertical bound
	bool inBoundsY = (moveValue.first > 0 && moveValue.first < 500);
	while (!inBoundsY) {
		moveValue.first--;
		inBoundsY = (moveValue.first > 0 && moveValue.first < 500);
	}

	// Down
	if (moveValue.first > pos.first && moveValue.second == pos.second)
	{
		int i = 1;
		bool changed = false;
		while (pos.first != moveValue.first && pos.first + i < 500 && !cellMatrix[pos.first + i][pos.second]) {
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.first += 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed) {
			return false;
		}
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

	// Down left
	else if (moveValue.first > pos.first && moveValue.second < pos.second) {
		int i = 1, j = 1;
		bool changed = false;
		while (moveValue.first != pos.first && moveValue.second != pos.second && !cellMatrix[pos.first + i][pos.second - j])
		{
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.first += 1;
			pos.second -= 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed) {
			return false;
		}
			
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

	// Down right
	else if (moveValue.first > pos.first && moveValue.second > pos.second) {
		int i = 1, j = 1;
		bool changed = false;
		while (moveValue.first != pos.first && moveValue.second != pos.second && !cellMatrix[pos.first + i][pos.second + j])
		{
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.first += 1;
			pos.second += 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed) {
			return false;
		}
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

	// Left
	else if (moveValue.first == pos.first && moveValue.second < pos.second) {
		int i = 1;
		bool changed = false;
		while (moveValue.second != pos.second && !cellMatrix[pos.first][pos.second - i])
		{
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.second -= 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed)
			return false;
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}

	// Right
	else if (moveValue.first == pos.first && moveValue.second > pos.second) {
		int i = 1;
		bool changed = false;
		while (moveValue.second != pos.second && !cellMatrix[pos.first][pos.second + i])
		{
			cellMatrix[pos.first][pos.second] = nullptr;
			pos.second += 1;
			cellMatrix[pos.first][pos.second] = this;
			changed = true;
		}
		if (!changed)
			return false;
		else {
			pix.setPosition(pos.second, pos.first);
			return true;
		}
	}
}

bool Cell::getMove()
{
	return move;
}

Cell::~Cell()
{
}

WaterCell::WaterCell(pair<int, int> pos)
{
	this->pos = pos;
	this->pix.setPosition(pos.second, pos.first);
	this->pix.setFillColor(sf::Color::Blue);
	this->pix.setSize(sf::Vector2f(1, 1));
}

pair<int, int> WaterCell::getPos()
{
	return pos;
}

void WaterCell::applyLaw(vector<vector<Cell*>>& cellMatrix)
{
	int moveValue = velocity;

	if (move) {

		// Check down
		bool moveDown = tryToMove(pair<int, int>(pos.first + moveValue, pos.second), cellMatrix);
		if (!moveDown) {

			// Check down-left
			bool moveDownLeft = tryToMove(pair<int, int>(pos.first + moveValue, pos.second - moveValue), cellMatrix);
			if (!moveDownLeft) {

				// Check down-right
				bool moveDownRight = tryToMove(pair<int, int>(pos.first + moveValue, pos.second + moveValue), cellMatrix);
				if (!moveDownRight) {

					// Check left
					bool moveLeft = tryToMove(pair<int, int>(pos.first, pos.second - moveValue), cellMatrix);
					if (!moveLeft) {

						//Check right
						bool moveRight = tryToMove(pair<int, int>(pos.first, pos.second + moveValue), cellMatrix);
						
						// It is blocked
						if (!moveRight)
							move = false;
					}
				}
			}
		}
	}
}

WaterCell::~WaterCell()
{
}

bool WoodCell::tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix)
{
	return false;
}

WoodCell::WoodCell(pair<int, int> pos)
{
	this->pos = pos;
	this->solid = true;
	this->pix.setPosition(pos.second, pos.first);
	this->pix.setFillColor(sf::Color::Black);
	this->pix.setSize(sf::Vector2f(1, 1));
}

pair<int, int> WoodCell::getPos()
{
	return pos;
}

void WoodCell::applyLaw(vector<vector<Cell*>>& cellMatrix)
{
}

WoodCell::~WoodCell()
{
}
