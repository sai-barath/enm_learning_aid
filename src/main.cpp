#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"


int main() {
    sf::RenderWindow win(sf::VideoMode(800, 600), "E&M Learning Aid");
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        win.clear(sf::Color::White); 
        PointCharge c1(100.0, 400.0, 0.0, 0.00003);
        PointCharge c2(700.0, 400.0, 0.0, -0.00003);
        PointCharge charges[] = {c1, c2};
        draw::drawefield(win, charges, 2);
        win.display();
    }
}