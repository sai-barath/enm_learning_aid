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
        win.clear(sf::Color::White);
        sf::CircleShape circ(10.0f);
        circ.setFillColor(sf::Color::Blue);
        win.draw(circ);
        win.display();
    }
}