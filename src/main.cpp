#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vectorR3.hpp"
#include "drawing.hpp"
#include "pointCharge.hpp"
#include "bField.hpp"
#include <vector>


void pointCharges() {
    std::cout << "Enter num charges (must be > 0)" << std::endl;
    int numc = -1;
    while(numc <= 0) {
        std::cin >> numc;
    }
    std::vector<pointCharge> charges(numc);
    for(int i = 0; i < numc; i++) {
        double x = 0.0, y = 0.0, c = 0.0;
        std::cout << "Enter x y charge (space separated) for charge #" << i + 1 << std::endl;
        std::cin >> x >> y >> c;
        charges.push_back(pointCharge(x, y, 0.0, c));
    }
    int mode = -1;
    std::cout << "(1) Field vectors" << std::endl << "(2) Heat map" << std::endl;
    while(mode != 1 && mode != 2) {
        std::cin >> mode;
    }
    if(mode == 1) {
        sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid", sf::Style::Default, sf::ContextSettings(0, 0, 2));
        int i = 0;
        std::cout << "Units used are meters, coulombs, and newtons, chages around the order of magnitude of 10^-4 work best " << std::endl;
        while (win.isOpen()) {
            win.clear(sf::Color::White);
            sf::Event e;
            while (win.pollEvent(e)) {
                if (e.type == sf::Event::Closed) {
                    win.close();
                }
            }
            if(i == 0) {
                draw::drawElecField(win, charges);
            } else {
                draw::drawElecField(win, charges);
            }
            win.display();
            i++;
        }
    } else {
        draw::eFieldHeatMap(charges);
    }
}

void drawB() {
    double x = 1.0,  y = 1.0, curr = 0.0;
    std::cout << "Enter x-dir, y-dir, current" << std::endl;
    std::cin >> x >> y >> curr;
    std::cout << "(1) Field vectors" << std::endl << "(2) Heat map" << std::endl;
    int mode = 0;
    std::cin >> mode;
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid", sf::Style::Default, sf::ContextSettings(0, 0, 2));
    longThinWire wir(x, y, curr);
    draw::drawBField(win, wir, mode);
    clock_t startTime = clock();
    while (win.isOpen()) {
        win.clear(sf::Color::White);
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        win.display();
        //std::cout << "Drawing frame " + std::to_string(i) << std::endl;
        //std::cout << "FPS: " + std::to_string(i / (float(clock() - startTime) / 1000000)) << std::endl;
        //y = std::fmod(1.0001 * y + 0.00001, 3);
    }
}

void vertexWire() {
    double curr = 0.0;
    std::cout << "Enter current" << std::endl;
    std::cin >> curr;
    std::cout << "Pick one:\n(1) Field Vector\n(2) Heat Map" << std::endl;
    int mode = 0;
    std::cin >> mode;
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
    /**
     * Cache will hold z-Component of magnetic field at each location on screen
     * Will only be recomputed each time a new vertex is added
     */
    int x_size = 0;
    int y_size = 0;
    if (mode == 2){
        x_size = win.getSize().x;
        y_size = win.getSize().y;
    }
    else{
        x_size = (win.getSize().x / 100) + 1;
        y_size = (win.getSize().y / 100) + 1;
    }
    std::vector<std::vector<double>> cache(x_size, std::vector<double>(y_size));
    wireOfVertices wir(curr);
    win.clear(sf::Color::White);
    while (win.isOpen()) {
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
            if (e.mouseButton.button == sf::Mouse::Right){
                draw::drawVertexWire(win, wir, cache, mode);
            }
        }
        win.display();
    }
}

int main() {
    std::cout << "Pick one: " << std::endl << "(1) Point charges" << std::endl << "(2) B-fields" << std::endl << "(3) Wire of vertices" << std::endl; 
    int choice = -1;
    std::cin >> choice;
    if(choice == 1) {
        pointCharges();
    } else if(choice == 2) {
        drawB();
    } else if(choice == 3) {
        vertexWire();
    } else {
        return 1;
    }
}