#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"
#include <cmath>
#include <iostream>

void draw::transformpt(vectorR3& vec, int windowy) {
    vec.y_component = (windowy - vec.y_component);
}

void draw::transformvec(vectorR3& vec, int windowy) {
    vec.y_component *= -1;
}

void draw::drawvector(sf::RenderWindow &win, vectorR3 start, vectorR3 vec) {
    /*if (start.z_component != 0 || vec.z_component != 0) {
        //Error handling
    }*/

    int triangleSize = 4;
    draw::transformpt(start, win.getSize().y);
    draw::transformvec(vec, win.getSize().y);

    //Draws the line
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x_component, start.y_component), sf::Color::Black),
        sf::Vertex(sf::Vector2f(start.x_component + vec.x_component, start.y_component + vec.y_component), sf::Color::Black)
    };

    // Triangle stuff
    int angle = atan(vec.y_component/vec.x_component) * (180/PI);
    sf::CircleShape triangle(triangleSize, 3);
    triangle.setFillColor(sf::Color::Black);
    triangle.setPosition(start.x_component + vec.x_component, start.y_component + vec.y_component);
    triangle.rotate(angle+90);

    // Drawing the shapes into the screen
    win.draw(line,2 , sf::Lines);
    win.draw(triangle);
}

/*void drawcharge(sf::RenderWindow& win, const PointCharge& pc) {
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
} */