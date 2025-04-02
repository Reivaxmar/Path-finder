#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

#include "PathRenderer.h"

int main(int argc, char* argv[]) {
    
    if(argc < 2) {
        cout << "Missing args!" << endl;
        cout << "Usage: ./pathfinder <size>" << endl;
        return -1;
    }
    int n = argv[1][0] - '0';
    // cout << "Size is: " << n << endl;
    PathRenderer pthRend(Vector2i(n, n));

    RenderWindow window(VideoMode(500, 500), "Pathfinder");
    window.setFramerateLimit(60);
    window.requestFocus();

    while(window.isOpen()) {
        for(Event ev;window.pollEvent(ev);) {
            if(ev.type == Event::Closed)
                window.close();
        }
        window.clear();

        pthRend.Draw(window);

        window.display();
    }

}