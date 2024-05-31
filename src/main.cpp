#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"

void debug() {
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
    int i = 0;
    win.clear(sf::Color::White);
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        PointCharge c1(87.0, 360.0, 0.0, 0.00003);
        PointCharge c2(707.0, 400.0, 0.0, -0.00003);
        PointCharge charges[] = {c1};
        if(i == 0) {
            draw::drawefield(win, charges, 1, 1);
        } else {
            draw::drawefield(win, charges, 1, 0);
        }
        win.display();
    }
}

int main() {
    std::cout << "Pick one: " << std::endl << "(1) Debug" << std::endl; 
    int choice = -1;
    std::cin >> choice;
    if(choice == 1) {
        debug();
    }
}