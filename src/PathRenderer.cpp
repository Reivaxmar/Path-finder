#include "PathRenderer.h"

PathRenderer::PathRenderer(Vector2i _siz)
    : m_pathCalc(_siz)
{

}

void PathRenderer::Draw(RenderWindow& window) {
    Vector2f tileSize(Vector2f(window.getSize().x / m_pathCalc.getSize().x, window.getSize().y / m_pathCalc.getSize().y));
    RectangleShape rect(Vector2f(tileSize.x, 10));
    for(int x = 0; x < m_pathCalc.getSize().x; x++) {
        for(int y = 0; y < m_pathCalc.getSize().y; y++) {
            // cout << "IsAble: " << (Mouse::isButtonPressed(Mouse::Left) && !m_LeftBefore) << endl;
            // Get the tile pos
            Vector2f pos = Vector2f(x * tileSize.x, (y+1) * tileSize.y);
            // Check if the mouse is inside and clicked
            if(rect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) &&
               Mouse::isButtonPressed(Mouse::Left) && !m_LeftBefore) {
                m_pathCalc.getRoom(Vector2i(x, y)).down ^= true;
                if(x+1 != m_pathCalc.getSize().x)
                    m_pathCalc.getRoom(Vector2i(x+1, y)).up ^= true;
            }
            // Then, check if it's open
            if(m_pathCalc.getRoom(Vector2i(x, y)).down) {
                rect.setFillColor(Color::Red);
            } else {
                rect.setFillColor(Color::White);
            }
            // Finally set its position and draw it
            rect.setPosition(pos);
            window.draw(rect);

            // Rotate the rectangle for vertical doors
            rect.setRotation(90);
            // Check if the mouse is inside and clicked
            if(rect.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))) &&
               Mouse::isButtonPressed(Mouse::Left) && !m_LeftBefore) {
                m_pathCalc.getRoom(Vector2i(x, y)).right ^= true;
                if(y+1 != m_pathCalc.getSize().y)
                    m_pathCalc.getRoom(Vector2i(x, y+1)).left ^= true;
            }
            // Then, check if it's open
            if(m_pathCalc.getRoom(Vector2i(x, y)).right) {
                rect.setFillColor(Color::Red);
            } else {
                rect.setFillColor(Color::White);
            }
            // Finally draw it
            window.draw(rect);
            // Reset the rectangle
            rect.setRotation(0);
        }

    }
    // Set if last left pressed
    // cout << Mouse::isButtonPressed(Mouse::Left) << ", " << m_LeftBefore << endl;
    m_LeftBefore = Mouse::isButtonPressed(Mouse::Left);
}