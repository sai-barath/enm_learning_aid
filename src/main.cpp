#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"


int main() {
    //int x1, x2, y1, y2;
    //std::cout << "enter the cords" << std::endl;
    //std::cin >> x1 >> x2 >> y1 >> y2;
    sf::RenderWindow win(sf::VideoMode(800, 600), "E&M Learning Aid");
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        /*win.clear(sf::Color::White); 
        vectorR3 vec1 (200, 200, 0);
        vectorR3 vec10(400, 400, 0);
        vectorR3 vec2 (-100, 100, 0);
        vectorR3 vec3(100, 100, 0);
        vectorR3 vec4(-100, -100, 0);
        vectorR3 vec5(100,-100, 0);
        vectorR3 vec6(100, 0, 0);
        vectorR3 vec7(-100, 0, 0);
        vectorR3 vec8(0, 100, 0);
        vectorR3 vec9(0, -100, 0);
        vectorR3 vec11(200, 100, 0);
        PointCharge pc1(vec1, 5.0);
        PointCharge pc2(vec10, -5.0);
        
        draw::drawvector(win, vec1, vec2);
        draw::drawvector(win, vec1, vec3);
        draw::drawvector(win, vec1, vec4);
        draw::drawvector(win, vec1, vec5);
        draw::drawvector(win, vec1, vec6);
        draw::drawvector(win, vec1, vec7);
        draw::drawvector(win, vec1, vec8);
        draw::drawvector(win, vec1, vec9);
        draw::drawvector(win, vec1, vec11);
        draw::drawc(win, pc1);
        draw::drawc(win, pc2);*/

        win.display();
    }
}