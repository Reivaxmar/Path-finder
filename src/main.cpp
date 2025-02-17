#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#include "PathRenderer.h"

int main() {
    // cout << "Enter width and height: ";
    int n;
    cin >> n;
    // int n = 7;

    PathCalculator pthCalc(Vector2i(n, n));
    PathRenderer pthRend(Vector2i(n, n));

    RenderWindow window(VideoMode(500, 500), "Pathfinder");
    window.setFramerateLimit(60);

    while(window.isOpen()) {
        for(Event ev;window.pollEvent(ev);) {
            if(ev.type == Event::Closed)
                window.close();
        }
        window.clear();

        pthRend.Draw(window);

        window.display();
    }
    
    // pthCalc.Update(window);

    


    // RenderWindow window(VideoMode(800, 800), "Pathfinder");

}