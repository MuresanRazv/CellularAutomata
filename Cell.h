#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Main.hpp>
#include <utility>
#include <vector>
#include <array>
#include <map>
#include <iostream>

using std::pair;
using std::vector;
using std::map;

class Cell {
protected:
    pair<int, int> pos;
    bool move = true;

public:
    sf::RectangleShape pix;
    virtual pair<int, int> getPos() = 0;
    virtual void applyLaw(vector<vector<Cell*>> &cellMatrix) = 0;
    virtual ~Cell();
};

class Universe {

private:
    // Private function which applies the laws of universe on each type of cell
    // Is called called repetitively at each tick
    // Each kind of cell will respect at least one law
    // For example, water and sand will both respect the law of gravity
    void universeLaws();

private:
    vector<vector<Cell*>> cellMatrix;

public:

    Universe();
    void addCell(Cell* newCell);
    void drawCells(sf::RenderWindow& window);
    ~Universe();
};

class SandCell : public Cell, public Universe {
public:
    SandCell();
    SandCell(pair<int, int> pos);
    virtual pair<int, int> getPos();
    virtual void applyLaw(vector<vector<Cell*>> &cellMatrix);

    ~SandCell();
};

class WaterCell : public Cell, public Universe {
private:

public:
    WaterCell();
    WaterCell(pair<int, int> pos);
    virtual pair<int, int> getPos();
    virtual void applyLaw(vector<vector<Cell*>> &cellMatrix);

    ~WaterCell();
};
