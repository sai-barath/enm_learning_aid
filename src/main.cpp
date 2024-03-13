#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"


void drawcharge(sf::RenderWindow& win, const PointCharge& pc) {
    sf::CircleShape charge(20);
    charge.setPosition(pc.pos.x_component, win.getSize().y - pc.pos.y_component);
    if(pc.charge <= 0.0) {
        charge.setFillColor(sf::Color::Blue);
        sf::Vertex line[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component - 15, win.getSize().y - pc.pos.y_component), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component + 15, win.getSize().y - pc.pos.y_component), sf::Color::White)
        };
        win.draw(line, 2 ,sf::Lines);
    } else {
        charge.setFillColor(sf::Color::Red);
        sf::Vertex line1[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component - 15, win.getSize().y - pc.pos.y_component), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component + 15, win.getSize().y - pc.pos.y_component), sf::Color::White)
        };
        sf::Vertex line2[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component, win.getSize().y - pc.pos.y_component  + 15), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component, win.getSize().y - pc.pos.y_component - 15), sf::Color::White)
        };
        win.draw(line1, 2 ,sf::Lines);
        win.draw(line2, 2 ,sf::Lines);
    }
    win.draw(charge);
}
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
        PointCharge pc(vec1, 5.0);
        /*draw::*/drawcharge(win, pc);
    }
}