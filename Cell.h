#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <utility>
#include <vector>
#include <array>
#include <map>
#include <iostream>
#include <string>

using std::pair;
using std::vector;
using std::map;
using std::string;

class Cell {
protected:
    pair<int, int> pos;
    bool move = true;

    bool tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix);

public:
    sf::RectangleShape pix;
    virtual pair<int, int> getPos() = 0;
    virtual void applyLaw(vector<vector<Cell*>> &cellMatrix) = 0;
    virtual ~Cell();
};

class SandCell : public Cell {
private:
    float velocity = 4;
    sf::Clock clock;

public:
    SandCell(pair<int, int> pos);

    pair<int, int> getPos();
    void applyLaw(vector<vector<Cell*>>& cellMatrix);

    ~SandCell();
};

class Universe {
private:
    vector<vector<Cell*>> cellMatrix;

public:
    Universe();
    ~Universe();

    void universeLaws();
    void drawCells(sf::RenderWindow &window);
    void addCell(Cell* cell);
};