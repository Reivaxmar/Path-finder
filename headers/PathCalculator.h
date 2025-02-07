#ifndef PATHCALCULATOR_CLASS_H
#define PATHCALCULATOR_CLASS_H

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Utils.h"

struct Room {
    Vector2i pos;
    bool up, down, left, right;
    Room(Vector2i _pos = Vector2i(0, 0)) {
        pos = _pos;
        up = true;
        down = true;
        left = true;
        right = true;
    }

    bool isOpen(Vector2i _next) {
        if(_next == Vector2i(1, 0)) return right;
        if(_next == Vector2i(-1, 0)) return left;
        if(_next == Vector2i(0, -1)) return up;
        if(_next == Vector2i(0, 1)) return down;
        return false;

    }
};

class PathCalculator {
public:
    PathCalculator(Vector2i _siz);
    void Update(RenderWindow& window);
    void Draw(RenderWindow& window);
    vector<int> CalculatePaths();
    Vector2i getSize();
    Room& getRoom(Vector2i pos);
private:
    Vector2i m_roomSize;
    vector<vector<Room>> m_grid;
};

#endif