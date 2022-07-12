#include "Cell.h"

Universe::Universe()
{
	vector<Cell*> columns(800, nullptr);
	cellMatrix.resize(500, columns);
}

Universe::~Universe()
{
	for (int i = 499; i >= 0; i--)
		for (int j = 799; j >= 0; j--)
			delete cellMatrix[i][j];
}

void Universe::universeLaws()
{
	for (int i = 499; i >= 0; i--)
		for (int j = 799; j >= 0; j--)
			if (cellMatrix[i][j])
				cellMatrix[i][j]->applyLaw(cellMatrix);
}

void Universe::drawCells(sf::RenderWindow &window)
{
	universeLaws();
	for (int i = 499; i >= 0; i--)
		for (int j = 799; j >= 0; j--)
			if (cellMatrix[i][j])
				window.draw(cellMatrix[i][j]->pix);
			
}

void Universe::addCell(Cell* cell)
{
	cellMatrix[cell->getPos().first][cell->getPos().second] = cell;
}

SandCell::SandCell(pair<int, int> pos)
{
	this->pos = pos;
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
		pair<int, int> moveDown = tryToMove(pair<int, int>(pos.first + moveValue, pos.second), cellMatrix);
		if (moveDown.first != pos.first || moveDown.second != pos.second) {
			// Update position
			cellMatrix[pos.first][pos.second] = nullptr;
			cellMatrix[moveDown.first][pos.second] = this;
			pos.first = moveDown.first;

			// Change coordinates of pixel
			pix.move(sf::Vector2f(0, moveValue));
			return;
		}

		// Check down-left
		pair<int, int> moveDownLeft = tryToMove(pair<int, int>(pos.first + 1, pos.second - 1), cellMatrix);
		if (moveDownLeft.first != pos.first && moveDownLeft.second != pos.second) {
			// Update position
			cellMatrix[pos.first][pos.second] = nullptr;
			cellMatrix[moveDownLeft.first][moveDownLeft.second] = this;
			pos.first = moveDownLeft.first;
			pos.second = moveDownLeft.second;

			// Change coordinates of pixel
			pix.move(sf::Vector2f(-moveValue, moveValue));
			return;
		}

		// Check down-right
		pair<int, int> moveDownRight = tryToMove(pair<int, int>(pos.first + 1, pos.second + 1), cellMatrix);
		if (moveDownRight.first != pos.first && moveDownRight.second != pos.second) {
			// Update position
			cellMatrix[pos.first][pos.second] = nullptr;
			cellMatrix[moveDownRight.first][moveDownRight.second] = this;
			pos.first = moveDownRight.first;
			pos.second = moveDownRight.second;

			// Change coordinates of pixel
			pix.move(sf::Vector2f(moveValue, moveValue));
			return;
		}

		// Sand has fallen to a point where it doesn't have to move anymore
		else
			move = false;
	}
}

SandCell::~SandCell()
{
}

pair<int, int> Cell::tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix)
{
	// Check horizontal bound
	bool inBoundsX = (moveValue.second > 0 && moveValue.second < 800);
	while (!inBoundsX) {
		moveValue.second--;
		inBoundsX = (moveValue.second > 0 && moveValue.second < 800);
	}

	// Check vertical bound
	bool inBoundsY = (moveValue.first > 0 && moveValue.first < 500);
	while (!inBoundsY) {
		moveValue.first--;
		inBoundsY = (moveValue.first > 0 && moveValue.first < 500);
	}

	// Check how much it can move vertically
	if (moveValue.first > 0)
		while (cellMatrix[moveValue.first][pos.second] && moveValue.first != pos.first) {
			moveValue.first--;
		}

	// Check how much it can move horizontally
	if (moveValue.second > 0)
		while (cellMatrix[pos.first][moveValue.second] && moveValue.second != pos.second) {
			moveValue.second--;
		}

	// Return final position
	return moveValue;
}

Cell::~Cell()
{
}
