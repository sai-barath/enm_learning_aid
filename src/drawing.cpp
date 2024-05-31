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

    int triangleSize = 10;
    draw::transformpt(start, win.getSize().y);
    draw::transformvec(vec, win.getSize().y);

    //Draws the line
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x_component, start.y_component), sf::Color::Black),
        sf::Vertex(sf::Vector2f(start.x_component + vec.x_component, start.y_component + vec.y_component), sf::Color::Black)
    };

    // Triangle stuff
    double angle = atan(vec.y_component/vec.x_component) * (180/PI);
    if(vec.x_component < 0.0) {
        angle += 180.0;
    }
    sf::CircleShape triangle(triangleSize, 3);
    triangle.setFillColor(sf::Color::Black);
    triangle.setOrigin(10,10);
    triangle.setPosition(start.x_component + vec.x_component, start.y_component + vec.y_component);
    triangle.rotate(angle+90);

    // Drawing the shapes into the screen
    win.draw(line,2 , sf::Lines);
    win.draw(triangle);
}

void draw::drawc(sf::RenderWindow& win, const PointCharge& pc) {
    // Sets up the circle
    sf::CircleShape charge(20);
    charge.setOrigin(20, 20);
    charge.setPosition(pc.pos.x_component, win.getSize().y - pc.pos.y_component);
    // Charge is negative
    if(pc.charge <= 0.0) {
        // Changes charge to be blue
        charge.setFillColor(sf::Color::Blue); 
        win.draw(charge);

        // Sets up the white lines
        sf::Vertex horizontal[] =
        {
        sf::Vertex(sf::Vector2f(pc.pos.x_component - 7, win.getSize().y - pc.pos.y_component), sf::Color::White),
        sf::Vertex(sf::Vector2f(pc.pos.x_component + 7, win.getSize().y - pc.pos.y_component), sf::Color::White)
        };
        win.draw(horizontal, 2 ,sf::Lines);
    } 

    // Charge is positive
    else {
        // Changes charge to red
        charge.setFillColor(sf::Color::Red);
        win.draw(charge);

        // Sets up the white lines
        sf::Vertex horizontal[] =
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
        win.draw(vertical, 2 ,sf::Lines);
    } 
}

void draw::drawefield(sf::RenderWindow& win, PointCharge* charges, int numc, bool debug) {
    // Maybe each charge's actual location is its top left: CONFIRMED
    int numx = win.getSize().x / 100;
    int numy = win.getSize().y / 100;
    for(int i = 0; i < numc; i++) {
        draw::drawc(win, charges[i]);
    }
    for(int i = 0; i < numx; i++) {
        for(int j = 0; j < numy; j++) {
            vectorR3 pos(i * 100, j * 100, 0);
            vectorR3 efieldatpos = charges[0].efield(pos);
            /*for(int k = 0; k < numc; k++) {
                efieldatpos += charges[i].efield(pos);
            }*/
            draw::drawvector(win, pos, efieldatpos);
            /*vectorR3 distance = pos - charges[i].pos;
            if(debug) {
                std::cout << "Distance: " << distance.getMagnitude() << ", field: " << efieldatpos.getMagnitude() << std::endl;
                if(efieldatpos.getMagnitude() > )
            }*/
        }
    }
}