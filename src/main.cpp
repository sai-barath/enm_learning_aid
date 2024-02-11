#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

int main() {
    sf::RenderWindow win(sf::VideoMode(800, 600), "E&M Learning Aid");
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
    }
}