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
    void intoOut(sf::RenderWindow& win, const vectorR3& where, const vectorR3& vec, double current) {
        double zComp = std::abs(vec.zComponent * 1e9 / current);
        int scalingFactor;
        sf::Color color;

        if (zComp <= 1) {
            color = sf::Color::Blue;
            scalingFactor = 2;
        } else if (zComp <= 2) {
            color = sf::Color::Green;
            scalingFactor = 2 + (zComp - 1) * 3;
        } else if (zComp <= 4) {
            color = sf::Color::Yellow;
            scalingFactor = 5 + (zComp - 2) * (11 / 2);
        } else {
            color = sf::Color::Red;
            scalingFactor = 16;
        }
        sf::CircleShape sym(zComp);
        sym.setRadius(scalingFactor);
        sym.setOutlineColor(color);
        sym.setOrigin(sym.getRadius(), sym.getRadius());
        sym.setFillColor(sf::Color::White);
        sym.setPosition(where.xComponent, win.getSize().y - where.yComponent);
        sym.setOutlineThickness(2);
        win.draw(sym);
        if(vec.zComponent < 0.0) {
            double lineLen = scalingFactor / SQRT2;
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
            double dotRadius = 1 + scalingFactor / 4;
            sf::CircleShape dot(dotRadius);
            dot.setOrigin(dotRadius, dotRadius);
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

    double computeDistanceFromWire(const vectorR3& pos, const longThinWire& wir) {
    // p1: A point on the wire (you can use the wire's starting point)
    vectorR3 p1(0, 0, 0);  // Assuming the wire starts at (0, 0)

    // p2: The position of the vector (pos in this case)
    vectorR3 p2 = pos;

    // d: The direction vector of the wire
    vectorR3 d = wir.direction;

    // Compute the vector from p1 to p2
    vectorR3 p1_to_p2 = p2 - p1;

    // Compute the cross product of d and (p2 - p1)
    vectorR3 crossProduct = d.cross(p1_to_p2);

    // Calculate the distance using the formula: |d x (p2 - p1)| / |d|
    double distance = crossProduct.magnitude() / d.magnitude();

    return distance;
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
                // std::cout << "Inserting " << mag << std::endl;
                pixels[index + 1] = 0;       
                pixels[index + 2] = static_cast<sf::Uint8>(255 - mag);   
                pixels[index + 3] = 255;
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
        while(win.isOpen()) {
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
    void drawBField(sf::RenderWindow& win, const longThinWire& wir,  int& mode, const float d = 32) {
        double windowSlopeFactor = win.getSize().y / win.getSize().x;
        double slope = wir.direction.yComponent / wir.direction.xComponent;
        double maxX;
        double maxY;
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

        //Draws every node in the grid representing the magnetic field
        if (mode == 1) {
            for (double i = 0.0; i < win.getSize().x; i += (win.getSize().x / (1280 / d))) {
                for (double j = 0.0; j < win.getSize().y; j += (win.getSize().y / (720 / d))) {
                    vectorR3 pos(i, j, 0);
                    vectorR3 bField = wir.computeBField(pos);
                    //std::cout << "(" << pos.xComponent << ", " << pos.yComponent << "): " << bField << std::endl;
                    if (computeDistanceFromWire(pos,wir) > 20){
                        draw::intoOut(win, pos, bField, wir.current);
                    }
                }
            }
        } else {
            // sets each pixel to a color based on the magnitude and direction (blue = into the screen, red = out of the screen)
            std::vector<sf::Uint8> pixels(win.getSize().x * win.getSize().y * 4);
            int pixel_index = 0;
            for (int i = 0; i < win.getSize().y; i++){
                for (int j = 0; j < win.getSize().x; j++){
                    pixel_index = (i * win.getSize().x  + j) * 4;
                    vectorR3 pos(j, win.getSize().y - i, 0);
                    vectorR3 bField = wir.computeBField(pos);
                    if (bField.zComponent < 0){
                        double bMagnitude = bField.magnitude() * 1e9;
                        if (bMagnitude > 255) bMagnitude = 255;
                        pixels[pixel_index] = static_cast<sf::Uint8>(255 - bMagnitude);
                        std::cout << "Inserting " << bMagnitude << std::endl;
                        pixels[pixel_index + 1] = static_cast<sf::Uint8>(255 - bMagnitude);
                        pixels[pixel_index + 2] = static_cast<sf::Uint8>(255);
                        pixels[pixel_index + 3] = 255;
                    } else {
                        double bMagnitude = bField.magnitude() * 1e9;
                        if (bMagnitude > 255) bMagnitude = 255;
                        pixels[pixel_index] = static_cast<sf::Uint8>(255);
                        std::cout << "Inserting " << bMagnitude << std::endl;
                        pixels[pixel_index + 1] = static_cast<sf::Uint8>(255 - bMagnitude);
                        pixels[pixel_index + 2] = static_cast<sf::Uint8>(255 - bMagnitude);
                        pixels[pixel_index + 3] = 255;
                    }
                }
            }
            sf::Texture heatTextureB;
            heatTextureB.create(win.getSize().x, win.getSize().y);
            heatTextureB.update(pixels.data());
            sf::RectangleShape fullScreenRect(sf::Vector2f(win.getSize().x, win.getSize().y));
            fullScreenRect.setFillColor(sf::Color::White);
            fullScreenRect.setTexture(&heatTextureB);
            win.clear(sf::Color::White);
            win.draw(fullScreenRect);

            // draw the legend for blue = into and red = out of, bottom right part of the window

            // outline box for the legend
            sf::RectangleShape legendOutline(sf::Vector2f(50, 50));
            legendOutline.setOrigin(50, 50);
            legendOutline.setFillColor(sf::Color::White);
            legendOutline.setOutlineThickness(1.75);
            legendOutline.setOutlineColor(sf::Color::Black);
            legendOutline.setPosition(sf::Vector2f(win.getSize().x - 25, win.getSize().y - 25));
            win.draw(legendOutline);

            // blue box for into the screen
            sf::RectangleShape blueLegendBox(sf::Vector2f(15, 15));
            blueLegendBox.setFillColor(sf::Color::Blue);
            blueLegendBox.setPosition(win.getSize().x - 70, win.getSize().y - 68);
            win.draw(blueLegendBox);

            // into next to blue
            sf::CircleShape intoOutline;
            intoOutline.setPosition(win.getSize().x - 45, win.getSize().y - 68);
            intoOutline.setFillColor(sf::Color::White);
            intoOutline.setOutlineThickness(2);
            intoOutline.setRadius(7.5);
            intoOutline.setOutlineColor(sf::Color::Black);
            sf::Vertex line1[] = {
                sf::Vertex(sf::Vector2f(win.getSize().x - 30, win.getSize().y - 60.5), sf::Color::Black),
                sf::Vertex(sf::Vector2f(win.getSize().x - 45, win.getSize().y - 60.5), sf::Color::Black)
            };
            sf::Vertex line2[] = {
                sf::Vertex(sf::Vector2f(win.getSize().x - 37.5, win.getSize().y - 68), sf::Color::Black),
                sf::Vertex(sf::Vector2f(win.getSize().x - 37.5, win.getSize().y - 53), sf::Color::Black)
            };
            win.draw(intoOutline);
            win.draw(line1, 10, sf::Lines);
            win.draw(line2, 10, sf::Lines);

            // red box for out of screen
            sf::RectangleShape redLegendBox(sf::Vector2f(15, 15));
            redLegendBox.setFillColor(sf::Color::Red);
            redLegendBox.setPosition(win.getSize().x - 70, win.getSize().y - 48);
            win.draw(redLegendBox);

            //out of next to red
            sf::CircleShape outofOutline;
            outofOutline.setPosition(win.getSize().x - 45, win.getSize().y - 48);
            outofOutline.setFillColor(sf::Color::White);
            outofOutline.setOutlineThickness(2);
            outofOutline.setRadius(7.5);
            outofOutline.setOutlineColor(sf::Color::Black);
            win.draw(outofOutline);
            
            sf::CircleShape dot(3);
            dot.setOrigin(3, 3);
            dot.setPosition(win.getSize().x - 37.5, win.getSize().y - 40.5);
            dot.setFillColor(sf::Color::Black);
            win.draw(dot);
        }
        sf::RectangleShape thickLine;
        float length = sqrt(maxX*maxX + (maxY-win.getSize().y) * (maxY-win.getSize().y));
        thickLine.setOrigin(0, 5 / 2.0f);
        thickLine.setSize(sf::Vector2f(length, 5));
        thickLine.setRotation(angle);
        thickLine.setPosition(0, win.getSize().y);
        thickLine.setFillColor(sf::Color::Black);
        win.draw(thickLine);
        //win.draw(wire , 2, sf::Lines);

        if (wir.current < 0) {
            angle = std::fmod(angle + 180, 360);
        }

        double triangleSize = 10.0;
        for (double xPos = 0.0; xPos < maxX; xPos += (maxX / 5)) {

            //Temporary fix for #33; calculate "center of mass" or average position, then rotate
            //Let's move this into a helper/utility class later.
            //We also aren't drawing enough triangles when slope < 1, is this intended?
            sf::CircleShape triangle(triangleSize, 3);
            sf::Vector2f newTriangleOrigin;
            for (int i = 0; i < 3; i++) {
                sf::Vector2f trianglePoint = triangle.getPoint(i);
                newTriangleOrigin.x += trianglePoint.x;
                newTriangleOrigin.y += trianglePoint.y;
            }
            triangle.setOrigin(newTriangleOrigin.x / 3, newTriangleOrigin.y / 3);
            if (mode == 1){
                triangle.setFillColor(sf::Color::Red);
            }
            else{
                triangle.setFillColor(sf::Color::Green);
            }
            triangle.rotate(angle + 90);
            triangle.setPosition(xPos, win.getSize().y - (slope * xPos));
            win.draw(triangle);
        }
    }

    void drawVertexWire(sf::RenderWindow& win, wireOfVertices& wir, std::vector<std::vector<double> >& cache, int mode) {
        win.clear(sf::Color::White);
        int multiplier = 100;
        if (mode == 2){
            multiplier = 1;
        }
        // Mouse button pressed, may need to add new vertex
        sf::Vector2f position = win.mapPixelToCoords(sf::Mouse::getPosition(win));
        if(wir.vertices.empty()) { 
            // If no vertices exist, we can add one without any other checks, no B-field recompute needed
            std::cout << "inserting " << vectorR3(position.x, position.y, 0.0) << std::endl;
            wir.addVertex(position.x, position.y);
        } else {
            // Some vertices exist
            vectorR3 last = wir.vertices[wir.vertices.size() - 1];
            // Check last vertex added to avoid duplication
            if(last.xComponent != position.x || last.yComponent != position.y) {
                // If new click location is different from last
                std::cout << "inserting " << vectorR3(position.x, position.y, 0.0) << std::endl;
                wir.addVertex(position.x, position.y);
                // Recalculate b field and store in cache
                if(wir.vertices.size() >= 3) {
                    for(int i = 0; i < (win.getSize().x / multiplier); i++) {
                        for(int j = 0; j < (win.getSize().y / multiplier); j++) {
                            vectorR3 pos(i * multiplier, j * multiplier, 0.0);
                            vectorR3 bField = wir.bField(pos);
                            cache[i][j] = bField.zComponent;
                        }
                    }
                }
            }
        }
        if(wir.vertices.size() >= 3) {
            // Draw wire and display b-field if enough vertices
            int numVert = wir.vertices.size();
            for(int i = 0; i < wir.vertices.size(); i++) {
                sf::Vertex wirSeg[] = {sf::Vertex(sf::Vector2f(wir.vertices[i].xComponent, win.getSize().y - wir.vertices[i].yComponent), sf::Color::Black), sf::Vertex(sf::Vector2f(wir.vertices[(i + 1) % numVert].xComponent, win.getSize().y - wir.vertices[(i + 1) % numVert].yComponent), sf::Color::Black)};
                win.draw(wirSeg, 2, sf::Lines);
            }
            if (mode == 1) {
                for(int i = 0; i <= (win.getSize().x / 100); i++) {
                    for(int j = 0; j <= (win.getSize().y / 100); j++) {
                        vectorR3 bField(0, 0, cache[i][j]);
                        vectorR3 pos(i * 100, j * 100, 0.0);
                        draw::intoOut(win, pos, bField, wir.current);
                    }
                }
            } else {
                std::vector<sf::Uint8> pixels(win.getSize().x * win.getSize().y * 4);
                
                for (int i = 0; i < win.getSize().x; i++){
                    for (int j = 0; j < win.getSize().y; j++){
                        int pixel_index = (j * win.getSize().x  + i) * 4;
                        vectorR3 pos(i, win.getSize().y - j, 0);
                        double bField = cache[i][j];
                        if (bField < 0){
                            double bMagnitude = -bField * 1e9;
                            if (bMagnitude > 255) bMagnitude = 255;
                            pixels[pixel_index] = static_cast<sf::Uint8>(255 - bMagnitude);
                            //std::cout << "Inserting " << bMagnitude << std::endl;
                            pixels[pixel_index + 1] = static_cast<sf::Uint8>(255 - bMagnitude);
                            pixels[pixel_index + 2] = static_cast<sf::Uint8>(255);
                            pixels[pixel_index + 3] = static_cast<sf::Uint8>(255);
                        } else {
                            double bMagnitude = bField * 1e9;
                            if (bMagnitude > 255) bMagnitude = 255;
                            pixels[pixel_index] = static_cast<sf::Uint8>(255);
                            //std::cout << "Inserting " << bMagnitude << std::endl;
                            pixels[pixel_index + 1] = static_cast<sf::Uint8>(255 - bMagnitude);
                            pixels[pixel_index + 2] = static_cast<sf::Uint8>(255 - bMagnitude);
                            pixels[pixel_index + 3] = static_cast<sf::Uint8>(255);
                        }
                    }
                }
                win.clear(sf::Color::White);
                sf::Texture heatTextureB;
                heatTextureB.create(win.getSize().x, win.getSize().y);
                heatTextureB.update(pixels.data());
                sf::RectangleShape fullScreenRect(sf::Vector2f(win.getSize().x, win.getSize().y));
                fullScreenRect.setFillColor(sf::Color::White);
                fullScreenRect.setTexture(&heatTextureB);
                win.draw(fullScreenRect);

                // draw the legend for blue = into and red = out of, bottom right part of the window

                // outline box for the legend
                sf::RectangleShape legendOutline(sf::Vector2f(50, 50));
                legendOutline.setOrigin(50, 50);
                legendOutline.setFillColor(sf::Color::White);
                legendOutline.setOutlineThickness(1.75);
                legendOutline.setOutlineColor(sf::Color::Black);
                legendOutline.setPosition(sf::Vector2f(win.getSize().x - 25, win.getSize().y - 25));
                win.draw(legendOutline);

                // blue box for into the screen
                sf::RectangleShape blueLegendBox(sf::Vector2f(15, 15));
                blueLegendBox.setFillColor(sf::Color::Blue);
                blueLegendBox.setPosition(win.getSize().x - 70, win.getSize().y - 68);
                win.draw(blueLegendBox);

                // into next to blue
                sf::CircleShape intoOutline;
                intoOutline.setPosition(win.getSize().x - 45, win.getSize().y - 68);
                intoOutline.setFillColor(sf::Color::White);
                intoOutline.setOutlineThickness(2);
                intoOutline.setRadius(7.5);
                intoOutline.setOutlineColor(sf::Color::Black);
                sf::Vertex line1[] = {
                    sf::Vertex(sf::Vector2f(win.getSize().x - 30, win.getSize().y - 60.5), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(win.getSize().x - 45, win.getSize().y - 60.5), sf::Color::Black)
                };
                sf::Vertex line2[] = {
                    sf::Vertex(sf::Vector2f(win.getSize().x - 37.5, win.getSize().y - 68), sf::Color::Black),
                    sf::Vertex(sf::Vector2f(win.getSize().x - 37.5, win.getSize().y - 53), sf::Color::Black)
                };
                win.draw(intoOutline);
                win.draw(line1, 10, sf::Lines);
                win.draw(line2, 10, sf::Lines);

                // red box for out of screen
                sf::RectangleShape redLegendBox(sf::Vector2f(15, 15));
                redLegendBox.setFillColor(sf::Color::Red);
                redLegendBox.setPosition(win.getSize().x - 70, win.getSize().y - 48);
                win.draw(redLegendBox);

                //out of next to red
                sf::CircleShape outofOutline;
                outofOutline.setPosition(win.getSize().x - 45, win.getSize().y - 48);
                outofOutline.setFillColor(sf::Color::White);
                outofOutline.setOutlineThickness(2);
                outofOutline.setRadius(7.5);
                outofOutline.setOutlineColor(sf::Color::Black);
                win.draw(outofOutline);
                
                sf::CircleShape dot(3);
                dot.setOrigin(3, 3);
                dot.setPosition(win.getSize().x - 37.5, win.getSize().y - 40.5);
                dot.setFillColor(sf::Color::Black);
                win.draw(dot);
            }
            
        }
    }
};
