#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"

int main() {
    //int x1, x2, y1, y2;
    //std::cout << "enter the cords" << std::endl;
    //std::cin >> x1 >> x2 >> y1 >> y2;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 4;
    sf::RenderWindow win(sf::VideoMode(800, 600), "E&M Learning Aid", sf::Style::Default, settings);
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
        win.display();
    }
}