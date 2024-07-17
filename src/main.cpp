#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vectorR3.hpp"
#include "drawing.hpp"
#include "pointCharge.hpp"
#include <vector>


void pointCharges() {
    std::cout << "Enter num charges (must be > 0)" << std::endl;
    int numc = -1;
    while(numc <= 0) {
        std::cin >> numc;
    }
    std::vector<pointCharge> charges;
    for(int i = 0; i < numc; i++) {
        double x = 0.0, y = 0.0, c = 0.0;
        std::cout << "Enter x y charge (space separated) for charge #" << i + 1 << std::endl;
        std::cin >> x >> y >> c;
        charges.push_back(pointCharge(x, y, 0.0, c));
    }
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
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
}

void debug() {
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
    while (win.isOpen()) {
        win.clear(sf::Color::White);
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        vectorR3 where(500, 500, 0);
        vectorR3 where2(500, 600, 0);
        vectorR3 into(0, 0, 2);
        vectorR3 out(0, 0, -2);
        draw::intoOut(win, where, into);
        draw::intoOut(win, where2, out);
        win.display();
    }
}

int main() {
    std::cout << "Pick one: " << std::endl << "(1) Point charges" << std::endl << "(2) Debug" << std::endl; 
    int choice = -1;
    std::cin >> choice;
    if(choice == 1) {
        pointCharges();
    } else if(choice == 2) {
        debug();
    } else {
        return 1;
    }
}