#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "vectorR3.hpp"
#include "drawing.hpp"
#include "pointCharge.hpp"
#include "bField.hpp"
#include "textbox.hpp"
#include <vector>
#include <sstream>
sf::Font font;
    
void textSet(sf::Text &text,int x,int y,std::string str,sf::Font font){

    
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("Point Charges       B-fields        Wire of Vertices");
    text.setCharacterSize(24);
    text.setPosition(30,0);
}


void pointCharges() {
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setString("Input for Point Charges");
    title.setCharacterSize(26);
    title.setPosition(500-title.getLocalBounds().width/2,0);
    sf::RenderWindow infowindow(
        sf::VideoMode(1000,200),
        "Input");
    sf::Text instr;
    textbox numcharges(0, 40, font,"Enter num charges: ");
    numcharges.select();
    textbox eachcharge(0,80,font,"Enter x y charge (space seperated) for ");
    int chargenum = 1;

    std::vector<pointCharge> charges;

    while (infowindow.isOpen()) {
        sf::Event event;
        if(numcharges.isdone()&& !eachcharge.isselected()) {
            eachcharge.select();
            eachcharge.setText("Enter x y charge (space seperated) for charge "+ std::to_string(chargenum)+": ");
        }
        while (infowindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                {infowindow.close();}
            if( event.type == sf::Event::TextEntered && !numcharges.isdone()) {
                numcharges.input(event);
            }
            if( event.type == sf::Event::TextEntered && !eachcharge.isdone()) {
                eachcharge.input(event);
            }
        }        
        if(eachcharge.isdone()) {
            chargenum+=1;
            double x = 0.0, y = 0.0, c = 0.0;
            
            std::stringstream ss(eachcharge.getInput());
            ss >> x >> y >> c;

            charges.push_back(pointCharge(x, y, 0.0, c));
            if(chargenum>std::stoi(numcharges.getInput())) {
                
                break;
            }
            eachcharge = textbox(0, 80, font, "Enter x y charge (space seperated) for charge "+ std::to_string(chargenum)+": ");
            eachcharge.select();
        }
        infowindow.clear(sf::Color(255,255,255)); 
        numcharges.draw(infowindow);
        eachcharge.draw(infowindow);
        infowindow.draw(title);
        infowindow.display();

    }

    infowindow.close();
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid", sf::Style::Default, sf::ContextSettings(0, 0, 2));
    int i = 0;
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

void drawB() {
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setString("Input for B-Field");
    title.setCharacterSize(26);
    title.setPosition(500-title.getLocalBounds().width/2,0);
    sf::RenderWindow infowindow(
        sf::VideoMode(1000, 200),
        "Input");
    sf::Text instr;
    textbox input(0,40,font,"Enter x-dir, y-dir, current: ");
    input.select();
    double x = 1.0,  y = 1.0, curr = 0.0;
    std::vector<pointCharge> charges;

    while (infowindow.isOpen()) {
        sf::Event event;
        while (infowindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                {infowindow.close();}
            if( event.type == sf::Event::TextEntered && !input.isdone()) {
                input.input(event);
            }
        }        
        if(input.isdone()) {
            std::stringstream ss(input.getInput());
            ss >> x >> y >> curr;
            break;
        }
        infowindow.clear(sf::Color(255,255,255)); 
        input.draw(infowindow);
        infowindow.draw(title);
        infowindow.display();

    }

    infowindow.close();

    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid", sf::Style::Default, sf::ContextSettings(0, 0, 2));
    while (win.isOpen()) {
        win.clear(sf::Color::White);
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        longThinWire wir(x, y, curr);
        draw::drawBField(win, wir);
        win.display();
    }
}

void vertexWire() {
    sf::Text title;
    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setString("Input for Vertex Wire");
    title.setCharacterSize(26);
    title.setPosition(500-title.getLocalBounds().width/2,0);
    double curr = 0.0;
    sf::RenderWindow infowindow(
        sf::VideoMode(1000, 200),
        "Input");
    sf::Text instr;
    textbox input(0,40,font,"Enter current: ");
    input.select();
    std::vector<pointCharge> charges;

    while (infowindow.isOpen()) {
        sf::Event event;
        while (infowindow.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                {infowindow.close();}
            if( event.type == sf::Event::TextEntered && !input.isdone()) {
                input.input(event);
            }
        }        
        if(input.isdone()) {
            std::stringstream ss(input.getInput());
            ss >> curr;
            break;
        }
        infowindow.clear(sf::Color(255,255,255)); 
        input.draw(infowindow);
        infowindow.draw(title);
        infowindow.display();

    }

    infowindow.close();
    sf::RenderWindow win(sf::VideoMode(1280, 720), "E&M Learning Aid");
    /**
     * Cache will hold z-Component of magnetic field at each location on screen
     * Will only be recomputed each time a new vertex is added
     */
    std::vector<std::vector<double>> cache((win.getSize().x / 100) + 1);
    for(int i = 0; i < cache.size(); i++) {
        cache[i].reserve((win.getSize().y / 100) + 1);
    }
    wireOfVertices wir(curr);
    while (win.isOpen()) {
        win.clear(sf::Color::White);
        sf::Event e;
        while (win.pollEvent(e)) {
            if (e.type == sf::Event::Closed) {
                win.close();
            }
        }
        draw::drawVertexWire(win, wir, cache);
        win.display();
    }
}



int main() {
    sf::Text text;
    sf::Text title;
    if (!font.loadFromFile("/mnt/c/Users/brady/OneDrive/Desktop/e&m/enm_learning_aid/Arial.ttf")){
    return EXIT_FAILURE;
    }

    title.setFont(font);
    title.setFillColor(sf::Color::Black);
    title.setString("Choose function");
    title.setCharacterSize(26);
    title.setPosition(280-title.getLocalBounds().width/2,0);

    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setString("Point Charges         B-fields          Wire of Vertices");
    text.setCharacterSize(20);
    text.setPosition(60,100);
    sf::RectangleShape button1(sf::Vector2f(120, 50));
    button1.setFillColor(sf::Color::Red);
    button1.setPosition(50, 150);
    sf::RectangleShape button2(sf::Vector2f(120, 50));
    button2.setFillColor(sf::Color::Blue);
    button2.setPosition(220, 150);
    sf::RectangleShape button3(sf::Vector2f(120, 50));
    button3.setFillColor(sf::Color::Green);
    button3.setPosition(390, 150);

    sf::RenderWindow window(
        sf::VideoMode(560, 480),
        "E&M Learning Aid");
    window.clear(sf::Color(255,255,255));
    while (window.isOpen()) {

        sf::Event event;

        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                std::cout << "CLOSED" << std::endl;
                window.close();
            }

            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(event.mouseButton.x >= 50 && event.mouseButton.x <= 170 && event.mouseButton.y >= 150 && event.mouseButton.y <=200) {
                        window.close();
                        pointCharges();

                    }
                    if(event.mouseButton.x >= 220 && event.mouseButton.x <= 340 && event.mouseButton.y >= 150 && event.mouseButton.y <=200) {
                        drawB();
                    }
                    if(event.mouseButton.x >= 390 && event.mouseButton.x <= 510 && event.mouseButton.y >= 150 && event.mouseButton.y <=200) {
                        vertexWire();
                    }
                }
            }

        }

        window.clear(sf::Color(255,255,255));

        window.draw(title);
        window.draw(text);
        window.draw(button1);
        window.draw(button2);
        window.draw(button3);

        window.display();
    }

}