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
		bool moveDown = tryToMove(pair<int, int>(pos.first + moveValue, pos.second), cellMatrix);
		if (!moveDown) {

			// Check down-left
			bool moveDownLeft = tryToMove(pair<int, int>(pos.first + 1, pos.second - 1), cellMatrix);
			if (!moveDownLeft) {

				// Check down-right
				bool moveDownRight = tryToMove(pair<int, int>(pos.first + 1, pos.second + 1), cellMatrix);
				if (!moveDownRight)

					// Cannot move in any direction, it is blocked
					move = false;
			}
		}	
	}
}

SandCell::~SandCell()
{
}

bool Cell::tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix)
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

	//// Check how much it can move vertically
	//if (moveValue.first > 0)
	//	while (cellMatrix[moveValue.first][pos.second] && moveValue.first != pos.first) {
	//		moveValue.first--;
	//	}

	//// Check how much it can move horizontally
	//if (moveValue.second > 0)
	//	while (cellMatrix[pos.first][moveValue.second] && moveValue.second != pos.second) {
	//		moveValue.second--;
	//	}

	// Return final position
}

Cell::~Cell()
{
}
