#include "PathCalculator.h"

PathCalculator::PathCalculator(Vector2i _siz)
    : m_grid(_siz.x, vector<Room>(_siz.y)), m_roomSize(_siz), m_prev(_siz.x, vector<pair<Vector2i, Vector2i>>(_siz.y, {{-1, -1}, {-1, -1}})) {
    for(int x = 0; x < _siz.x; x++)
        for(int y = 0; y < _siz.y; y++)
            m_grid[x][y].pos = Vector2i(x, y);
}

void PathCalculator::Update(RenderWindow& window) {
    vector<Vector2i> shortestPathVec = shortest_path(Vector2i(0, 0), m_roomSize - Vector2i(1, 1));
    cout << "Shortest path: ";
    for (auto& p : shortestPathVec) {
        cout << "(" << p.x << ", " << p.y << ") -> ";
    }
    cout << "END" << endl;

    vector<vector<bool>> visited(m_roomSize.x, vector<bool>(m_roomSize.y, false));
    vector<Vector2i> path, longestPathVec;
    longest_path(Vector2i(0, 0), m_roomSize - Vector2i(1, 1), visited, path, longestPathVec);

    cout << "Longest path: ";
    for (auto& p : longestPathVec) {
        cout << "(" << p.x << ", " << p.y << ") -> ";
    }
    cout << "END" << endl;
}

// Calculate the shortest path in the grid
vector<Vector2i> PathCalculator::shortest_path(Vector2i from, Vector2i to) {
    vector<vector<int>> dp(m_roomSize.x, vector<int>(m_roomSize.y, -1)); // Distance matrix
    vector<vector<Vector2i>> parent(m_roomSize.x, vector<Vector2i>(m_roomSize.y, {-1, -1})); // Stores path
    vector<vector<bool>> visited(m_roomSize.x, vector<bool>(m_roomSize.y, false));
    queue<Vector2i> q;

    q.push(from);
    visited[from.x][from.y] = true;
    dp[from.x][from.y] = 0;

    vector<Vector2i> directions = {Vector2i(-1, 0), Vector2i(0, -1), Vector2i(1, 0), Vector2i(0, 1)};

    while (!q.empty()) {
        Vector2i pos = q.front();
        q.pop();

        if (pos == to) break; // Stop when we reach the destination

        for (auto& dir : directions) {
            Vector2i newPos = pos + dir;
            if (0 <= newPos.x && newPos.x < m_roomSize.x && 0 <= newPos.y && newPos.y < m_roomSize.y &&
                !visited[newPos.x][newPos.y] && m_grid[pos.x][pos.y].isOpen(dir)) {
                
                visited[newPos.x][newPos.y] = true;
                dp[newPos.x][newPos.y] = dp[pos.x][pos.y] + 1;
                parent[newPos.x][newPos.y] = pos; // Store the previous node
                q.push(newPos);
            }
        }
    }

    // If there's no path
    if (dp[to.x][to.y] == -1) return {};

    // **Reconstructing the shortest path**
    vector<Vector2i> path;
    for (Vector2i at = to; at != from; at = parent[at.x][at.y]) {
        path.push_back(at);
    }
    path.push_back(from);
    reverse(path.begin(), path.end()); // Reverse the path to start from 'from'

    return path;
}


// Calculate the longest path in the grid
vector<Vector2i> PathCalculator::longest_path(Vector2i from, Vector2i to, vector<vector<bool>>& visited, vector<Vector2i>& path, vector<Vector2i>& longestPathVec) {
    visited[from.x][from.y] = true;
    path.push_back(from);

    if (from == to) {
        if (path.size() > longestPathVec.size()) {
            longestPathVec = path;
        }
    } else {
        vector<Vector2i> toAdd = {Vector2i(-1, 0), Vector2i(0, -1), Vector2i(1, 0), Vector2i(0, 1)};

        for (auto& dir : toAdd) {
            Vector2i newPos = from + dir;
            if (0 <= newPos.x && newPos.x < m_roomSize.x && 0 <= newPos.y && newPos.y < m_roomSize.y &&
                !visited[newPos.x][newPos.y] && m_grid[from.x][from.y].isOpen(dir)) {
                longest_path(newPos, to, visited, path, longestPathVec);
            }
        }
    }

    visited[from.x][from.y] = false; // Backtrack
    path.pop_back();

    return longestPathVec;
}

Vector2i PathCalculator::getSize() {
    return m_roomSize;
}

Room& PathCalculator::getRoom(Vector2i pos) {
    if(pos.x >= 0 && pos.y >= 0 && pos.x < m_roomSize.x && pos.y < m_roomSize.y)
        return m_grid[pos.x][pos.y];
}