#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vectorR3.hpp"
#include "drawing.hpp"
#include "pointCharge.hpp"
#include "bField.hpp"
#include <cmath>
#include <iostream>
#include <vector>


namespace draw {
    void drawVector(sf::RenderWindow &win, const vectorR3& begin, const vectorR3& vect);
    void drawCharge(sf::RenderWindow& win, pointCharge& pc);
    void intoOut(sf::RenderWindow& win, const vectorR3& where, const vectorR3& vec);
    void drawElecField(sf::RenderWindow& win, std::vector<pointCharge>& charges);
    void drawBField(sf::RenderWindow& win, const longThinWire& wir);
};


void draw::drawVector(sf::RenderWindow &win, const vectorR3& begin, const vectorR3& vect) {
    int triangleSize = 10;
    vectorR3 start(begin.xComponent, win.getSize().y - begin.yComponent, 0);
    vectorR3 vec(vect.xComponent, -vect.yComponent, 0);
    if(vec.magSquared() > 6400) {
        vec *= (80 / vec.magnitude());
    } else if(vec.magSquared() < 100) {
        vec *= (10 / vec.magnitude());
    }
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(start.xComponent, start.yComponent), sf::Color::Black),
        sf::Vertex(sf::Vector2f(start.xComponent + vec.xComponent, start.yComponent + vec.yComponent), sf::Color::Black)
    };

    // Rotating the arrow
    double angle = 0.0;
    if(vec.xComponent != 0.0) {
        angle = atan(vec.yComponent / vec.xComponent) * (180 / PI);
    } else if(vec.xComponent == 0 && vec.yComponent < 0) {
        angle = 270;
    } else if(vec.xComponent == 0 && vec.yComponent > 0) {
        angle = 90;
    }
    if(vec.xComponent < 0.0) {
        angle += 180.0;
    }
    sf::CircleShape triangle(triangleSize, 3);
    triangle.setFillColor(sf::Color::Black);
    triangle.setOrigin(triangleSize, triangleSize);
    triangle.setPosition(start.xComponent + vec.xComponent, start.yComponent + vec.yComponent);
    triangle.rotate(angle + 90);
    win.draw(line,2 , sf::Lines);
    win.draw(triangle);
}

void draw::drawCharge(sf::RenderWindow& win, pointCharge& pc) {
    sf::CircleShape charge(8);
    pc.pos.xComponent = std::floor(pc.pos.xComponent / 100) * 100;
    pc.pos.yComponent = std::floor(pc.pos.yComponent / 100) * 100;
    charge.setOrigin(8, 8);
    charge.setPosition(pc.pos.xComponent, win.getSize().y - pc.pos.yComponent);
    if(pc.charge <= 0.0) {
        charge.setFillColor(sf::Color::Blue); 
        win.draw(charge);
    } else {
        charge.setFillColor(sf::Color::Red);
        win.draw(charge);
    } 
   
}

void draw::intoOut(sf::RenderWindow& win, const vectorR3& where, const vectorR3& vec) {
    double zComp = std::abs(vec.zComponent);
    if(zComp > 48.0) {
        zComp = 48.0;
    } else if(zComp < 5.0 && zComp != 0) {
        zComp = 5.0;
    }
    sf::CircleShape sym(zComp);
    sym.setOrigin(zComp, zComp);
    sym.setFillColor(sf::Color::White);
    sym.setPosition(where.xComponent, win.getSize().y - where.yComponent);
    sym.setOutlineThickness(2);
    sym.setOutlineColor(sf::Color::Black);
    win.draw(sym);
    if(vec.zComponent < 0.0) {
        double lineLen = zComp / SQRT2;
        sf::Vertex line1[] = {
            sf::Vertex(sf::Vector2f(where.xComponent - lineLen, win.getSize().y - where.yComponent + lineLen), sf::Color::Black),
            sf::Vertex(sf::Vector2f(where.xComponent + lineLen, win.getSize().y - where.yComponent - lineLen), sf::Color::Black)
        };
        sf::Vertex line2[] = {
            sf::Vertex(sf::Vector2f(where.xComponent + lineLen, win.getSize().y - where.yComponent + lineLen), sf::Color::Black),
            sf::Vertex(sf::Vector2f(where.xComponent - lineLen, win.getSize().y - where.yComponent - lineLen), sf::Color::Black)
        };
        win.draw(line1, 2, sf::Lines);
        win.draw(line2, 2, sf::Lines);
    } else {
        sf::CircleShape dot(zComp / 4.0);
        dot.setOrigin(zComp / 4.0, zComp / 4.0);
        dot.setPosition(where.xComponent, win.getSize().y - where.yComponent);
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
        isChargePresent[(int) charges[k].pos.xComponent / 100][(int) charges[k].pos.yComponent / 100] = 1;
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

void draw::drawBField(sf::RenderWindow& win, const longThinWire& wir) {
    double slopeFactor = win.getSize().y / win.getSize().x;
    double slope = wir.direction.yComponent / wir.direction.xComponent;
    double angle = atan(slope) * (180 / PI);
    double maxX = -1.0;
    double maxY = -1.0;
    if(slope > slopeFactor) {
        maxX = win.getSize().y / slope;
        maxY = 0;
    } else {
        maxX = win.getSize().x;
        maxY = slope * win.getSize().x;
    }
    sf::Vertex wire[] = {
        sf::Vertex(sf::Vector2f(0, win.getSize().y), sf::Color::Black),
        sf::Vertex(sf::Vector2f(maxX, maxY), sf::Color::Black)
    };
    double triangleSize = 10.0;
    for(double xPos = 0.0; xPos < maxX; xPos += (maxX / 5)) {
        sf::CircleShape triangle(triangleSize, 3);
        triangle.setFillColor(sf::Color::Black);
        triangle.setOrigin(triangleSize, triangleSize);
        triangle.setPosition(xPos, win.getSize().y - (slope * xPos));
        triangle.rotate(angle - 90);
        win.draw(triangle);
    }
    win.draw(wire, 2, sf::Lines);
}