#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
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

    draw::transformpt(start, win.getSize().y);
    draw::transformvec(vec, win.getSize().y);
    //Draws the line
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x_component, start.y_component), sf::Color::Black),
        sf::Vertex(sf::Vector2f(start.x_component + vec.x_component, start.y_component + vec.y_component), sf::Color::Black)
    };

    int angle = atan(vec.y_component/vec.x_component) * (180/PI);
    sf::CircleShape triangle(10.f, 3);
    triangle.setFillColor(sf::Color::Black);
    //triangle.setOrigin(start.x_component + vec.x_component, start.y_component + vec.y_component);
    triangle.setPosition(start.x_component + vec.x_component, start.y_component + vec.y_component - 15);
    triangle.rotate(angle+90);
    //std::cout << angle << std::endl;

    //win.draw(convex);
    win.draw(line,2 , sf::Lines);
    win.draw(triangle);
}