#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include <iostream>

void Artist::drawvector(sf::RenderWindow& win, const vectorR3& start, const vectorR3& vec) {
    /*if (start.z_component != 9 || vec.z_component != 9) {
        //Do something
    }*/

    //Draws the line
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x_component, start.y_component), sf::Color::Black),
        sf::Vertex(sf::Vector2f(vec.x_component, vec.y_component), sf::Color::Black)
    };

    win.draw(line,2 , sf::Lines);
}