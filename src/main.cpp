#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"

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

        vectorR3 vec1 (200, 200, 0);
        vectorR3 vec2 (100, 135, 0);
        draw::drawvector(win, vec1, vec2);
        win.display();
    }
}