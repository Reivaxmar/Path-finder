#include "PathCalculator.h"

PathCalculator::PathCalculator(Vector2i _siz)
    : m_grid(_siz.x, vector<Room>(_siz.y)), m_roomSize(_siz) {

}

void PathCalculator::Update(RenderWindow& window) {
    queue<pair<Vector2i, int>> q;
    q.push({Vector2i(0, 0), 1});
    
    vector<vector<int>> dp(m_roomSize.x, vector<int>(m_roomSize.y, 0));
    vector<vector<bool>> visited(m_roomSize.x, vector<bool>(m_roomSize.y, false));
    
    dp[0][0] = 1;

    vector<Vector2i> toAdd = {Vector2i(-1, 0), Vector2i(0, -1), Vector2i(1, 0), Vector2i(0, 1)};

    while(!q.empty()) {
        // Get the current one in the queue
        auto cur = q.front();
        q.pop();

        for(auto neigh : toAdd) {
            // If it isn't open, skip it
            if(!m_grid[cur.first.x][cur.first.y].isOpen(neigh)) continue;

            // Else, get the next position
            auto nxt = cur.first + neigh;
            // If it is in the bound
            if(nxt.x >= m_roomSize.x || nxt.y >= m_roomSize.y || nxt.x < 0 || nxt.y < 0) continue;
            // Use DP to calculate the nº of paths
            dp[nxt.x][nxt.y] += dp[cur.first.x][cur.first.y];
            // Add it if it hasn't been visited
            if(!visited[nxt.x][nxt.y]) {
                // Push to queue and mark it as visited
                q.push({nxt, dp[cur.first.x][cur.first.y]});
                visited[nxt.x][nxt.y] = true;
            }
        }
    }
    
    cout << "Num paths: " << dp[m_roomSize.x-1][m_roomSize.y-1] << endl;
}

void PathCalculator::Draw(RenderWindow& window) {

}

Vector2i PathCalculator::getSize() {
    return m_roomSize;
}

vector<int> PathCalculator::CalculatePaths() {

}

Room& PathCalculator::getRoom(Vector2i pos) {
    if(pos.x >= 0 && pos.y >= 0 && pos.x < m_roomSize.x && pos.y < m_roomSize.y)
        return m_grid[pos.x][pos.y];
        
    
}