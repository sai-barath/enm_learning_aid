#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vectorR3.hpp"
#include "drawing.hpp"
#include "pointCharge.hpp"
#include "bField.hpp"
#include "vertexWire.hpp"
#include <cmath>
#include <iostream>
#include <vector>
#include <ctime>

namespace draw {
    /**
     * Draw a 2D vector on the screen
     *
     * @param win The window to draw on
     * @param begin start point
     * @param vect actual vector
     */
    void drawVector(sf::RenderWindow &win, const vectorR3& begin, const vectorR3& vect) {
        int triangleSize = 10;
        vectorR3 start(begin.xComponent, win.getSize().y - begin.yComponent, 0);
        vectorR3 vec(vect.xComponent, -vect.yComponent, 0);

        if(vec.magSquared() > 6400) {
            vec *= (80 / vec.magnitude());
        } else if(vec.magSquared() < 100) {
            vec *= (10 / vec.magnitude());
        }
        triangleSize = vec.magnitude()/5;
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
    /**
     * Draw a small circle representing a charge on the screen
     *
     * @param win The window to draw on
     * @param pc The point charge
     */
    void drawCharge(sf::RenderWindow& win, pointCharge& pc) {
        sf::CircleShape charge(8);
        pc.pos.xComponent = std::floor(pc.pos.xComponent / 100) * 100;
        pc.pos.yComponent = std::floor(pc.pos.yComponent / 100) * 100;
        charge.setOrigin(8, 8);
        charge.setPosition(pc.pos.xComponent, win.getSize().y - pc.pos.yComponent);
        if(pc.charge <= 0.0) {
            charge.setFillColor(sf::Color::Blue); 
            win.draw(charge);
        } else {
            charge.setFillColor(sf::Color::Green);
            win.draw(charge);
        } 
    
    }

    /**
     * Draw a vector with only a z-component
     *
     * @param win The window to draw on
     * @param where start point
     * @param vec actual vector
     */
    void intoOut(sf::RenderWindow& win, const vectorR3& where, const vectorR3& vec) {
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

    /**
     * Draw a set of charges and their associated electric fields
     *
     * @param win The window to draw on
     * @param charges  an std::vector consisting of the charges
     */
    void drawElecField(sf::RenderWindow& win, std::vector<pointCharge>& charges) {
        int numc = charges.size();
        for(int i = 0; i < numc; i++) {
            draw::drawCharge(win, charges[i]);
        }
        int numx = (win.getSize().x / 100) + 1;
        int numy = (win.getSize().y / 100) + 1;
        std::vector<std::vector<vectorR3> > board(numx);
        std::vector<std::vector<bool> > isChargePresent(numx);
        for(int i = 0; i < numx; i++) {
            board[i].reserve(numy);
            isChargePresent[i].reserve(numy);
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
    }

    /**
     * Draw a set of charges and their associated electric field magnitudes (heat map)
     *
     * @param charges  an std::vector consisting of the charges
     */
    void eFieldHeatMap(std::vector<pointCharge>& charges) {
        sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid", sf::Style::Default, sf::ContextSettings(0, 0, 2));
        std::clock_t start = clock();
        const int winX = win.getSize().x;
        const int winY = win.getSize().y;
        const int winSize = winX * winY;
        // Texture for heat values
        sf::Texture heatTexture;
        heatTexture.create(winX, winY);
        // Create a RGBA pixel array (4 components) for the texture, use just the red channel for heat values
        std::vector<sf::Uint8> pixels(winSize * 4);
        for (int y = 0; y < winY; y++) {
            for (int x = 0; x < winX; x++) {
                int index = (y * winX  + x) * 4;
                vectorR3 pos(x, win.getSize().y - y, 0);
                vectorR3 E = charges[0].efield(pos);
                for(size_t i = 1; i < charges.size(); i++) {
                    E += charges[i].efield(pos);
                }
                double mag = E.magnitude() / 10;
                if(mag > 255) mag = 255;
                pixels[index] = static_cast<sf::Uint8>(mag); // set red channel
                std::cout << "Inserting " << mag << std::endl;
                pixels[index + 1] = 0;       
                pixels[index + 2] = static_cast<sf::Uint8>(255 - mag);   
                pixels[index + 3] = 100;
            }
        }
        std::clock_t end = clock();
        double time = ((double) (end - start)) / CLOCKS_PER_SEC;
        std::cout << "time: " << time << std::endl;
        heatTexture.update(pixels.data());
        sf::Shader shader;
        /*const std::string SHADE = R"(
            #version 330 core

            in vec2 fragTexCoord;
            out vec4 FragColor;

            uniform sampler2D heatTexture;

            void main() {
                float heatValue = texture(heatTexture, fragTexCoord).r;
                FragColor = vec4(heatValue, 0, 255.0 - heatValue, 0.5);
            }
        )";
        if (!shader.loadFromMemory(SHADE, sf::Shader::Fragment)) {
            std::cerr << "Can't load shader" << std::endl;
        }
        shader.setUniform("heatTexture", heatTexture);*/
        sf::RectangleShape fullScreenRect(sf::Vector2f(1280, 720));
        fullScreenRect.setFillColor(sf::Color::White);
        fullScreenRect.setTexture(&heatTexture);
        while (win.isOpen()) {
            sf::Event event;
            while (win.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    win.close();
            }
            win.clear(sf::Color::White);
            win.draw(fullScreenRect);
            for(int i = 0; i < charges.size(); i++) {
                draw::drawCharge(win, charges[i]);
            }
            win.display();
        }
    }

    /**
     * Draw an arbitrarily long wire and its magnetic field
     *
     * @param win The window to draw on
     * @param wir The wire
     */
    void drawBField(sf::RenderWindow& win, const longThinWire& wir) {
        double windowSlopeFactor = win.getSize().y / win.getSize().x;
        double slope = wir.direction.yComponent / wir.direction.xComponent;
        double maxX = -1.0;
        double maxY = -1.0;
        //If our wire is steeper than the window, we have to truncate it to avoid drawing out of bounds
        if (slope > windowSlopeFactor) {
            maxX = win.getSize().y / slope;
            maxY = 0;
        } else {
            //Otheriwse just draw until it hits the right edge of the window
            maxX = win.getSize().x;
            maxY = slope * win.getSize().x;
        }
        sf::Vertex wire[] = {
            sf::Vertex(sf::Vector2f(0, win.getSize().y), sf::Color::Black),
            sf::Vertex(sf::Vector2f(maxX, maxY), sf::Color::Black)
        };
        //Calculate angle *after* we know the final wire vector
        double angle = atan2(wire[1].position.y - wire[0].position.y, wire[1].position.x - wire[0].position.x) * (180 / PI);

        double triangleSize = 10.0;
        for(double xPos = 0.0; xPos < maxX; xPos += (maxX / 5)) {

            //Temporary fix for #33; calculate "center of mass" or average position, then rotate
            //Let's move this into a helper/utility class later.
            //We also aren't drawing enough triangles when slope < 1, is this intended?
            //---
            sf::CircleShape triangle(triangleSize, 3);
            sf::Vector2f newTriangleOrigin;
            for (int i = 0; i < 3; i++) {
                sf::Vector2f trianglePoint = triangle.getPoint(i);
                newTriangleOrigin.x += trianglePoint.x;
                newTriangleOrigin.y += trianglePoint.y;
            }
            triangle.setOrigin(newTriangleOrigin.x / 3, newTriangleOrigin.y / 3);
            //---
            
            triangle.setFillColor(sf::Color::Red);
            triangle.rotate(angle + 90);
            triangle.setPosition(xPos, win.getSize().y - (slope * xPos));
            win.draw(triangle);
        }
        // Don't need to use SFML's coord system here
        for(double i = 0.0; i < win.getSize().x; i += (win.getSize().x / 10.0)) {
            for(double j = 0.0; j < win.getSize().y; j += (win.getSize().y / 10.0)) {
                vectorR3 pos(i, j, 0);
                vectorR3 bField = wir.computeBField(pos);
                //std::cout << "(" << pos.xComponent << ", " << pos.yComponent << "): " << bField << std::endl;   
                draw::intoOut(win, pos, bField);
            }
        } 
        win.draw(wire, 2, sf::Lines);
    }

    void drawVertexWire(sf::RenderWindow& win, wireOfVertices& wir, std::vector<std::vector<double>>& cache) {
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
            sf::Vector2i position = sf::Mouse::getPosition();
            wir.addVertex(position.x, win.getSize().y - position.y);
            std::cout << vectorR3(position.x, win.getSize().y - position.y, 0.0) << std::endl;
            if(wir.vertices.size() >= 3) {
                for(int i = 0; i <= win.getSize().x; i += win.getSize().x / 100) {
                    for(int j = 0; j <= win.getSize().y; j += win.getSize().y / 100) {
                        vectorR3 pos(i * 100, j * 100, 0.0);
                        vectorR3 bField = wir.bField(pos);
                        cache[i][j] = bField.zComponent;
                        draw::intoOut(win, pos, bField);
                    }
                }
            }
        }
        if(wir.vertices.size() >= 3) {
            sf::Vertex wire[wir.vertices.size() + 1];
            for(int i = 0; i < wir.vertices.size(); i++) {
                wire[i] = sf::Vertex(sf::Vector2f(wir.vertices[i].xComponent, win.getSize().y - wir.vertices[i].yComponent), sf::Color::Black);
            }
            wire[wir.vertices.size()] = wire[0];
            win.draw(wire, wir.vertices.size() + 1, sf::Lines);
        }
    }
};
