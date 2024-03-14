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
        win.clear(sf::Color::White); 
        vectorR3 vec1 (200, 200, 0);
        vectorR3 vec2 (0, 100, 0);
        draw::drawvector(win, vec1, vec2);
        PointCharge pc(vec1, 5.0);
        draw::drawc(win, pc);
        /*sf::CircleShape charge(20);
        charge.setPosition(200, 150);
        charge.setFillColor(sf::Color::Blue);
        win.draw(charge);*/
        win.display();
    }
}