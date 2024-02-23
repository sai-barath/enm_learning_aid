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
        vectorR3 vec1 (100, 100, 9);
        vectorR3 vec2 (500, 500, 9);

        Artist test;
        test.drawvector(win, vec1, vec2);

        win.display();
    }
}