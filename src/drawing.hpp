#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vectorR3.hpp"
#include "drawing.hpp"
#include "pointCharge.hpp"
#include <cmath>
#include <iostream>
#include <vector>


namespace draw {
    void drawVector(sf::RenderWindow &win, const vectorR3& begin, const vectorR3& vect);
    void drawCharge(sf::RenderWindow& win, pointCharge& pc);
    void intoOut(sf::RenderWindow& win, const vectorR3& where, const vectorR3& vec);
    void drawElecField(sf::RenderWindow& win, std::vector<pointCharge>& charges);
};


void draw::drawVector(sf::RenderWindow &win, const vectorR3& begin, const vectorR3& vect) {
    int triangleSize = 10;
    vectorR3 start(begin.x_component, win.getSize().y - begin.y_component, 0);
    vectorR3 vec(vect.x_component, -vect.y_component, 0);
    if(vec.magSquared() > 6400) {
        vec *= (80 / vec.magnitude());
    } else if(vec.magSquared() < 100) {
        vec *= (10 / vec.magnitude());
    }
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.x_component, start.y_component), sf::Color::Black),
        sf::Vertex(sf::Vector2f(start.x_component + vec.x_component, start.y_component + vec.y_component), sf::Color::Black)
    };

    // Rotating the arrow
    double angle = 0.0;
    if(vec.x_component != 0.0) {
        angle = atan(vec.y_component / vec.x_component) * (180 / PI);
    } else if(vec.x_component == 0 && vec.y_component < 0) {
        angle = 270;
    } else if(vec.x_component == 0 && vec.y_component > 0) {
        angle = 90;
    }
    if(vec.x_component < 0.0) {
        angle += 180.0;
    }
    sf::CircleShape triangle(triangleSize, 3);
    triangle.setFillColor(sf::Color::Black);
    triangle.setOrigin(10, 10);
    triangle.setPosition(start.x_component + vec.x_component, start.y_component + vec.y_component);
    triangle.rotate(angle + 90);
    win.draw(line,2 , sf::Lines);
    win.draw(triangle);
}

void draw::drawCharge(sf::RenderWindow& win, pointCharge& pc) {
    sf::CircleShape charge(8);
    pc.pos.x_component = std::floor(pc.pos.x_component / 100) * 100;
    pc.pos.y_component = std::floor(pc.pos.y_component / 100) * 100;
    charge.setOrigin(8, 8);
    charge.setPosition(pc.pos.x_component, win.getSize().y - pc.pos.y_component);
    if(pc.charge <= 0.0) {
        charge.setFillColor(sf::Color::Blue); 
        win.draw(charge);
    } else {
        charge.setFillColor(sf::Color::Red);
        win.draw(charge);
    } 
   
}

void draw::intoOut(sf::RenderWindow& win, const vectorR3& where, const vectorR3& vec) {
    double zComp = std::abs(vec.z_component);
    if(zComp > 48.0) {
        zComp = 48.0;
    } else if(zComp < 5.0 && zComp != 0) {
        zComp = 5.0;
    }
    sf::CircleShape sym(zComp);
    sym.setOrigin(zComp, zComp);
    sym.setFillColor(sf::Color::White);
    sym.setPosition(where.x_component, win.getSize().y - where.y_component);
    sym.setOutlineThickness(2);
    sym.setOutlineColor(sf::Color::Black);
    win.draw(sym);
    if(vec.z_component < 0.0) {
        double lineLen = zComp / SQRT2;
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(where.x_component - lineLen, win.getSize().y - where.y_component + lineLen), sf::Color::Black),
            sf::Vertex(sf::Vector2f(where.x_component + lineLen, win.getSize().y - where.y_component - lineLen), sf::Color::Black)
        };
        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(where.x_component + lineLen, win.getSize().y - where.y_component + lineLen), sf::Color::Black),
            sf::Vertex(sf::Vector2f(where.x_component - lineLen, win.getSize().y - where.y_component - lineLen), sf::Color::Black)
        };
        win.draw(line1, 2, sf::Lines);
        win.draw(line2, 2, sf::Lines);
    } else {
        sf::CircleShape dot(zComp / 4.0);
        dot.setOrigin(zComp / 4.0, zComp / 4.0);
        dot.setPosition(where.x_component, win.getSize().y - where.y_component);
        dot.setFillColor(sf::Color::Black);
        win.draw(dot);
    }
}

void draw::drawElecField(sf::RenderWindow& win, std::vector<pointCharge>& charges) {
    int numc = charges.size();
    for(int i = 0; i < numc; i++) {
        draw::drawCharge(win, charges[i]);
    }
    int numx = (win.getSize().x / 100) + 1;
    int numy = (win.getSize().y / 100) + 1;
    vectorR3** board = new vectorR3*[numx];
    bool** isChargePresent = new bool*[numx];
    for(int i = 0; i < numx; i++) {
        board[i] = new vectorR3[numy];
        isChargePresent[i] = new bool[numy];
        for(int j = 0; j < numy; j++) {
            board[i][j] = vectorR3(i * 100, j * 100, 0);
            isChargePresent[i][j] = 0;
        }
    }
    for(int k = 0; k < charges.size(); k++) {
        isChargePresent[(int) charges[k].pos.x_component / 100][(int) charges[k].pos.y_component / 100] = 1;
    }
    for(int i = 0; i < numx; i++) {
        for(int j = 0; j < numy; j++) {
            vectorR3 efieldatpos = charges[0].efield(board[i][j]);
            for(int k = 1; k < numc; k++) {
                efieldatpos += charges[k].efield(board[i][j]);
            }
            if(!isChargePresent[i][j]) {
                draw::drawVector(win, board[i][j], efieldatpos);
            }
        }
    }
    for(int i = 0; i < numx; i++) {
        delete[] board[i];
        delete[] isChargePresent[i];
    }
    delete[] board;
    delete[] isChargePresent;
}