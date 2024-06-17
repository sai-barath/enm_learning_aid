#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"
#include <cmath>
#include <iostream>
#include <vector>


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

    int triangleSize = 10;
    draw::transformpt(start, win.getSize().y);
    draw::transformvec(vec, win.getSize().y);
    if(vec.magsquared() > 6400) {
        vec *= (80 / vec.getMagnitude());
    } else if(vec.magsquared() < 100) {
        vec *= (10 / vec.getMagnitude());
    }
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x_component, start.y_component), sf::Color::Black),
        sf::Vertex(sf::Vector2f(start.x_component + vec.x_component, start.y_component + vec.y_component), sf::Color::Black)
    };

    // Rotating the arrow
    double angle = atan(vec.y_component/vec.x_component) * (180 / PI);
    if(vec.x_component < 0.0) {
        angle += 180.0;
    }
    sf::CircleShape triangle(triangleSize, 3);
    triangle.setFillColor(sf::Color::Black);
    triangle.setOrigin(10, 10);
    triangle.setPosition(start.x_component + vec.x_component, start.y_component + vec.y_component);
    triangle.rotate(angle + 90);

    // Drawing the shapes into the screen
    win.draw(line,2 , sf::Lines);
    win.draw(triangle);
}

void draw::drawc(sf::RenderWindow& win, const PointCharge& pc) {
    // Sets up the circle
    /*sf::CircleShape charge(20);
    charge.setOrigin(20, 20);*/
    sf::CircleShape charge(8);
    charge.setOrigin(8, 8);
    charge.setPosition(pc.pos.x_component, win.getSize().y - pc.pos.y_component);
    // Charge is negative
    if(pc.charge <= 0.0) {
        // Changes charge to be blue
        charge.setFillColor(sf::Color::Blue); 
        // Sets up the white lines
        /*sf::Vertex horizontal[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component - 7, win.getSize().y - pc.pos.y_component), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component + 7, win.getSize().y - pc.pos.y_component), sf::Color::White)
        };
        win.draw(horizontal, 2 ,sf::Lines);*/
        win.draw(charge);
    } else {
        // Changes charge to red
        charge.setFillColor(sf::Color::Red);
        // Sets up the white lines
        /*sf::Vertex horizontal[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component - 7, win.getSize().y - pc.pos.y_component), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component + 7, win.getSize().y - pc.pos.y_component), sf::Color::White)
        };
        sf::Vertex vertical[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component, win.getSize().y - pc.pos.y_component + 7), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component, win.getSize().y - pc.pos.y_component - 7), sf::Color::White)
        };
        win.draw(horizontal, 2 ,sf::Lines);
        win.draw(vertical, 2 ,sf::Lines);*/
        win.draw(charge);
    } 
   
}

void draw::drawefield(sf::RenderWindow& win, std::vector<PointCharge>& charges, bool debug) {
    int numx = win.getSize().x / 100;
    int numy = win.getSize().y / 100;
    int numc = charges.size();
    for(int i = 0; i < numc; i++) {
        draw::drawc(win, charges[i]);
    }
    for(int i = 0; i <= numx; i++) {
        for(int j = 0; j <= numy; j++) {
            vectorR3 pos((i * 100) + 20, (j * 100) + 20, 0);
            vectorR3 efieldatpos = charges[0].efield(pos);
            for(int k = 1; k < numc; k++) {
                efieldatpos += charges[k].efield(pos);
            }
            draw::drawvector(win, pos, efieldatpos);
            if(debug) {
                std::cout << "Pos: (" << pos.x_component << ", " << pos.y_component << ", " << pos.z_component << "), Field: (" << efieldatpos.x_component << ", " << efieldatpos.y_component << ", " << efieldatpos.z_component << ")" << std::endl;
            }
        }
    }
}