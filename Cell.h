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
private:
    virtual bool tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix) = 0;

protected:
    pair<int, int> pos;
    bool move = true;

public:
    bool solid = false;
    bool drewStatic = false;
    sf::RectangleShape pix;
    virtual pair<int, int> getPos() = 0;
    bool getMove();
    virtual void applyLaw(vector<vector<Cell*>> &cellMatrix) = 0;
    virtual ~Cell();
};

class SandCell : public Cell {
private:
    float velocity = 6;
    virtual bool tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix);

public:
    SandCell(pair<int, int> pos);

    pair<int, int> getPos();
    void applyLaw(vector<vector<Cell*>>& cellMatrix);

    ~SandCell();
};

class WaterCell : public Cell {
private:
    float velocity = 3;
    virtual bool tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix);

public:
    WaterCell(pair<int, int> pos);

    pair<int, int> getPos();
    void applyLaw(vector<vector<Cell*>>& cellMatrix);

    ~WaterCell();
};

class WoodCell : public Cell {
private:
    virtual bool tryToMove(pair<int, int> moveValue, vector<vector<Cell*>>& cellMatrix);

public:
    WoodCell(pair<int, int> pos);

    pair<int, int> getPos();
    void applyLaw(vector<vector<Cell*>>& cellMatrix);

    ~WoodCell();
};

class Universe {
private:
    vector<vector<Cell*>> cellMatrix;
    sf::RenderTexture staticCells;
    sf::RenderTexture movingCells;

public:
    Universe();
    ~Universe();

    void universeLaws(sf::RenderTexture& texture);
    void drawCells(sf::RenderWindow &window, sf::RenderTexture &texture);
    void addCell(Cell* cell);
};