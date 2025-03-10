#ifndef PATHCALCULATOR_CLASS_H
#define PATHCALCULATOR_CLASS_H

#include <iostream>
#include <vector>
#include <queue>
#include <thread>
using namespace std;

#include <SFML/Graphics.hpp>
using namespace sf;

#include "Utils.h"

struct Room {
    Vector2i pos;
    bool up, down, left, right;
    Room(Vector2i _pos = Vector2i(0, 0)) {
        pos = _pos;
        up = false;
        down = false;
        left = false;
        right = false;
    }

    bool isOpen(Vector2i _next) {
        // cout << "Room: (" << pos.x << ", " << pos.y << "), open (dlur): " << down << left << up << right << endl;
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
    void Update();
    // vector<int> CalculatePaths();
    Vector2i getSize();
    Room& getRoom(Vector2i pos);
    vector<vector<pair<Vector2i, Vector2i>>> m_prev;
    // vector<vector<int>> dp;
    int num_paths;
    // Thread calc_thread;
private:
    int backtrack(vector<vector<bool>>& visited, Vector2i pos, Vector2i prev);
    Vector2i m_roomSize;
    vector<vector<Room>> m_grid;
};

#endif