#include "PathCalculator.h"

PathCalculator::PathCalculator(Vector2i _siz)
    : m_grid(_siz.x, vector<Room>(_siz.y)), m_roomSize(_siz), m_prev(_siz.x, vector<pair<Vector2i, Vector2i>>(_siz.y, {{-1, -1}, {-1, -1}})) {
    for(int x = 0; x < _siz.x; x++)
        for(int y = 0; y < _siz.y; y++)
            m_grid[x][y].pos = Vector2i(x, y);
}

void PathCalculator::Update() {
    vector<vector<bool>> visited(m_roomSize.x, vector<bool>(m_roomSize.y, false));
    
    visited[0][0] = true;

    m_prev.clear();
    m_prev.resize(m_roomSize.x, vector<pair<Vector2i, Vector2i>>(m_roomSize.y, {{-1, -1}, {-1, -1}}));
    
    num_paths = backtrack(visited, Vector2i(0, 0), Vector2i(-2, -2));

    cout << "Num paths: " << num_paths << endl;

    vector<Vector2i> p;
    Vector2i cur = m_roomSize - Vector2i(1, 1);
    while(cur != Vector2i(-2, -2)) {
        p.push_back(cur);
        cur = m_prev[cur.x][cur.y].second;
    }
    reverse(p.begin(), p.end());
    cout << "Shortest path: ";
    for(auto& i : p) cout << "(" << i.x << ", " << i.y << "), ";
    cout << endl;

    p.clear();
    cur = m_roomSize - Vector2i(1, 1);
    while(cur != Vector2i(-2, -2)) {
        p.push_back(cur);
        cur = m_prev[cur.x][cur.y].first;
    }
    reverse(p.begin(), p.end());
    cout << "Longest path: ";
    for(auto& i : p) cout << "(" << i.x << ", " << i.y << "), ";
    cout << endl;
}

int PathCalculator::backtrack(vector<vector<bool>> &visited, Vector2i pos, Vector2i prev = Vector2i(0, 0)) {
    if(m_prev[pos.x][pos.y].first == Vector2i(-1, -1)) m_prev[pos.x][pos.y].first = prev;
    m_prev[pos.x][pos.y].second = prev;
    if(pos == m_roomSize - Vector2i(1, 1)) {
        return 1;
    }
    // cout << "Entered room: (" << pos.x << ", " << pos.y << ")" << endl;
    visited[pos.x][pos.y] = true;
    int paths = 0;

    vector<Vector2i> toAdd = {Vector2i(-1, 0), Vector2i(0, -1), Vector2i(1, 0), Vector2i(0, 1)};

    for(Vector2i neigh : toAdd) {
        Vector2i newPos = pos + neigh;
        if(0 <= newPos.x && newPos.x < m_roomSize.x && 0 <= newPos.y && newPos.y < m_roomSize.y &&
           !visited[newPos.x][newPos.y] && m_grid[pos.x][pos.y].isOpen(neigh)) {
            paths += backtrack(visited, newPos, pos);
        }
    }
    visited[pos.x][pos.y] = false;
    return paths;
}

Vector2i PathCalculator::getSize() {
    return m_roomSize;
}

Room& PathCalculator::getRoom(Vector2i pos) {
    if(pos.x >= 0 && pos.y >= 0 && pos.x < m_roomSize.x && pos.y < m_roomSize.y)
        return m_grid[pos.x][pos.y];
}