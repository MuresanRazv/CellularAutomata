#include "Cell.h"


WaterCell::WaterCell()
{
    this->pix.setPosition(sf::Vector2f(0, 0));
    this->pix.setFillColor(sf::Color::Yellow);
    this->pix.setSize(sf::Vector2f(1, 1));
    this->pos = (pair<int, int>(0, 0));
}

WaterCell::WaterCell(std::pair<int, int> pos)
{
    this->pix.setPosition(sf::Vector2f(pos.second, pos.first));
    this->pix.setFillColor(sf::Color::Blue);
    this->pix.setSize(sf::Vector2f(1, 1));
    this->pos = pos;
}

pair<int, int> WaterCell::getPos()
{
    return pos;
}


void WaterCell::applyLaw(vector<vector<Cell*>> &cellMatrix)
{
    if (move) {
        // Check under
        if (pos.first + 1 < 500 && cellMatrix[pos.first + 1][pos.second] == nullptr) {
            cellMatrix[pos.first + 1][pos.second] = this;
            cellMatrix[pos.first][pos.second] = nullptr;
            pos.first += 1;
            pix.move(sf::Vector2f(0, 1));
            // If the sand has falled all the way down it doesn't have to move anymore
        }
        // Check left
        else if (pos.first + 1 < 500 && cellMatrix[pos.first + 1][pos.second - 1] == nullptr) {
            cellMatrix[pos.first + 1][pos.second - 1] = this;
            cellMatrix[pos.first][pos.second] = nullptr;
            pix.move(sf::Vector2f(-1, 1));
            pos.second -= 1;
            pos.first += 1;
        }
        // Check right
        else if (pos.first + 1 < 500 && cellMatrix[pos.first + 1][pos.second + 1] == nullptr) {
            cellMatrix[pos.first + 1][pos.second + 1] = this;
            cellMatrix[pos.first][pos.second] = nullptr;
            pix.move(sf::Vector2f(1, 1));
            pos.second += 1;
            pos.first += 1;
        }
        else
            move = false;
    }
}

WaterCell::~WaterCell()
{

}

Cell::~Cell()
{
}

void Universe::universeLaws()
{
    for (int i = 499; i >= 0; i--)
        for (int j = 799; j >= 0; j--)
            if (cellMatrix[i][j]) {
                cellMatrix[i][j]->applyLaw(cellMatrix);
            }
}

Universe::Universe()
{
    cellMatrix.resize(500, vector<Cell*>(800));
    for (int i = 499; i >= 0; i--)
        for (int j = 799; j >= 0; j--)
            cellMatrix[i][j] = nullptr;
}

void Universe::addCell(Cell* newCell)
{
    cellMatrix[newCell->getPos().first][newCell->getPos().second] = newCell;
}

Universe::~Universe()
{
}

void Universe::drawCells(sf::RenderWindow& window)
{
    this->universeLaws();
    for (int i = 499; i >= 0; i--)
        for (int j = 799; j >= 0; j--)
            if (cellMatrix[i][j]) {
                window.draw(cellMatrix[i][j]->pix);             
            }
}

SandCell::SandCell()
{
    this->pix.setPosition(sf::Vector2f(0, 0));
    this->pix.setFillColor(sf::Color::Yellow);
    this->pix.setSize(sf::Vector2f(1, 1));
    this->pos = (pair<int, int>(0, 0));
}

SandCell::SandCell(pair<int, int> pos)
{
    this->pix.setPosition(sf::Vector2f(pos.second, pos.first));
    this->pix.setFillColor(sf::Color::Yellow);
    this->pix.setSize(sf::Vector2f(1, 1));
    this->pos = pos;
}

pair<int, int> SandCell::getPos()
{
    return pos;
}

void SandCell::applyLaw(vector<vector<Cell*>> &cellMatrix)
{

    if (move) {
        // Check under
        if (pos.first + 1 < 500 && cellMatrix[pos.first + 1][pos.second] == nullptr) {
            cellMatrix[pos.first + 1][pos.second] = this;
            cellMatrix[pos.first][pos.second] = nullptr;
            pos.first += 1;
            pix.move(sf::Vector2f(0, 1));
            // If the sand has falled all the way down it doesn't have to move anymore
        }
        // Check left
        else if (pos.first + 1 < 500 && cellMatrix[pos.first + 1][pos.second - 1] == nullptr) {
            cellMatrix[pos.first + 1][pos.second - 1] = this;
            cellMatrix[pos.first][pos.second] = nullptr;
            pix.move(sf::Vector2f(-1, 1));
            pos.second -= 1;
            pos.first += 1;
        }
        // Check right
        else if (pos.first + 1 < 500 && cellMatrix[pos.first + 1][pos.second + 1] == nullptr) {
            cellMatrix[pos.first + 1][pos.second + 1] = this;
            cellMatrix[pos.first][pos.second] = nullptr;
            pix.move(sf::Vector2f(1, 1));
            pos.second += 1;
            pos.first += 1;
        }
        else
            move = false;
    }
}

SandCell::~SandCell()
{
}
