#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "drawing.h"
#include "point_charge.h"
#include <vector>

void debug() {
    double a = -999.0, b = -999.0;
    //std::cin >> a >> b;
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
    int i = 0;
    while (win.isOpen()) {
        win.clear(sf::Color::White);
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        PointCharge c1(340.3, 234.1, 0.0, 0.00003);
        PointCharge c2(707.0, 400.0, 0.0, -0.00003);
        std::vector<PointCharge> charges = {c1, c2};
        if(i == 0) {
            draw::drawefield(win, charges, 1);
        } else {
            draw::drawefield(win, charges, 0);
        }
        win.display();
        i++;
    }
}

void pointcharges() {
    std::cout << "Enter num charges (must be > 0)" << std::endl;
    int numc = -1;
    while(numc <= 0) {
        std::cin >> numc;
    }
    std::vector<PointCharge> charges;
    for(int i = 0; i < numc; i++) {
        double x = 0.0, y = 0.0, c = 0.0;
        std::cout << "Enter x y charge (space separated) for charge #" << i + 1 << std::endl;
        std::cin >> x >> y >> c;
        charges.push_back(PointCharge(x, y, 0.0, c));
    }
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
    int i = 0;
    std::cout << "Units used are meters, coulombs, and newtons" << i + 1 << std::endl;
    while (win.isOpen()) {
        win.clear(sf::Color::White);
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        if(i == 0) {
            draw::drawefield(win, charges, 1);
        } else {
            draw::drawefield(win, charges, 0);
        }
        win.display();
        i++;
    }
}

int main() {
    std::cout << "Pick one: " << std::endl << "(1) Debug" << std::endl << "(2) Point charges" << std::endl; 
    int choice = -1;
    std::cin >> choice;
    if(choice == 1) {
        debug();
    } else if(choice == 2) {
        pointcharges();
    }
}