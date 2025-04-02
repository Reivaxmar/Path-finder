#ifndef PATHRENDERER_CLASS_H
#define PATHRENDERER_CLASS_H

#include <SFML/Graphics.hpp>
using namespace sf;
#include "PathCalculator.h"
#include <string>

class PathRenderer {
public:
    PathRenderer(Vector2i _siz);
    void Draw(RenderWindow& window);
    void Update(RenderWindow& window);
private:
    PathCalculator m_pathCalc;
    bool m_LeftBefore;
};

#endif