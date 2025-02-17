#include "PathRenderer.h"

PathRenderer::PathRenderer(Vector2i _siz)
    : m_pathCalc(_siz)
{

}

void PathRenderer::Draw(RenderWindow& window) {

    Vector2f tileSize(Vector2f(window.getSize().x / m_pathCalc.getSize().x, window.getSize().y / m_pathCalc.getSize().y));
    // Vector2f tileSize(Vector2f(100, 100));
    RectangleShape rect(Vector2f(tileSize.x, 10));

    bool update = false;

    Font font;
    font.loadFromFile("assets/CascadiaCode.ttf");
    Text text("", font);
    text.setFillColor(Color::White);
    
    for(int x = 0; x < m_pathCalc.getSize().x; x++) {
        for(int y = 0; y < m_pathCalc.getSize().y; y++) {
            text.setPosition(Vector2f(x * tileSize.x, y * tileSize.y));
            text.setString(to_string(m_pathCalc.dp[x][y]));
            window.draw(text);
            // Get the tile pos
            Vector2f pos = Vector2f(x * tileSize.x, (y+1) * tileSize.y);
            rect.setPosition(pos);
            
            // Check if the mouse is inside and clicked
            if(rect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) &&
               Mouse::isButtonPressed(Mouse::Left) && !m_LeftBefore) {
                m_pathCalc.getRoom(Vector2i(x, y)).down ^= true;
                update = true;
                if(x+1 < m_pathCalc.getSize().x)
                    m_pathCalc.getRoom(Vector2i(x+1, y)).up ^= true;
            }
            // Then, check if it's open
            if(m_pathCalc.getRoom(Vector2i(x, y)).down) {
                rect.setFillColor(Color::Red);
            } else {
                rect.setFillColor(Color::White);
            }

            // Finally set its position and draw it
            if(y != m_pathCalc.getSize().y - 1)
                window.draw(rect);

            // Rotate the rectangle for vertical doors
            pos = Vector2f((x+1) * tileSize.x, y * tileSize.y);
            rect.setPosition(pos);
            rect.setRotation(90);
            // Check if the mouse is inside and clicked
            if(rect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) &&
               Mouse::isButtonPressed(Mouse::Left) && !m_LeftBefore) {
                m_pathCalc.getRoom(Vector2i(x, y)).right ^= true;
                update = true;
                if(y+1 < m_pathCalc.getSize().y)
                    m_pathCalc.getRoom(Vector2i(x, y+1)).left ^= true;
            }
            // Then, check if it's open
            if(m_pathCalc.getRoom(Vector2i(x, y)).right) {
                rect.setFillColor(Color::Red);
            } else {
                rect.setFillColor(Color::White);
            }
            // Finally draw it
            if(x != m_pathCalc.getSize().x - 1)
                window.draw(rect);
            // Reset the rectangle
            rect.setRotation(0);
            
        }
    }

    if(update) Update();

    // Set if last left pressed
    m_LeftBefore = Mouse::isButtonPressed(Mouse::Left);
}

void PathRenderer::Update() {
    m_pathCalc.Update();
}