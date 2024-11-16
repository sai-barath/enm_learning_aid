#pragma once
#include <cmath>
#include <string>
#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class textbox{
    public:
        textbox(int x, int y, sf::Font &font, std::string init){
            valid = true;
            start.setFont(font);
            start.setFillColor(sf::Color::Black);
            start.setString(init);
            start.setCharacterSize(24);
            start.setPosition(x,y);
            text.setFont(font);
            text.setFillColor(sf::Color::Black);
            text.setString("");
            text.setCharacterSize(24);
            text.setPosition(x+start.getLocalBounds().width,y);
            chars = text.getString();
            this->init = init;
            selected = false;
            coords.x = x+start.getLocalBounds().width;
            coords.y = y;
            sf::Vector2<float> size(500,37);
            box = sf::RectangleShape(size);
            box.setFillColor(sf::Color::White);
            box.setPosition(coords);
        }
        textbox(){
        }
        void input(sf::Event input) {
           
            if(input.type == sf::Event::TextEntered && selected) {
                int charnum = input.text.unicode;
                if(charnum<128) {
                    if(charnum!= DELETE_KEY && charnum!= ENTER_KEY && charnum!= ESCAPE_KEY){
                        sf::String s = input.text.unicode;
                        chars+=s.toAnsiString();
                        
                    }
                    if(charnum == DELETE_KEY&& chars!=""){
                        chars = chars.substr(0,chars.size()-1);
                    }
                    if(charnum == ENTER_KEY) {
                        std::cout<<"suss"<<std::endl;
                        selected = false;
                        done = true;
                    }


                }
            }
            if(input.type == sf::Event::MouseButtonPressed && input.mouseButton.button == sf::Mouse::Left && input.mouseButton.x>=coords.x && input.mouseButton.x<=coords.x+box.getSize().x && input.mouseButton.y>=coords.y && input.mouseButton.y<=coords.y+box.getSize().y && !done) {
                selected = true;
            }
            else if(input.type == sf::Event::MouseButtonPressed){
                selected = false;
            }
        }

        bool isdone() {
            return done;
        }
        void setText(std::string s){
            init = s;
        }
        std::string getInput() {
            return chars;
        }
        void draw(sf::RenderWindow &window){
            if(valid){
                if(selected){
                    sf::String s = (chars+"_").c_str();
                    text.setString(s);
                    if(chars!=""){
                        std::string s = text.getString();
                    }
                    
                }
                else{
                    text.setString(chars);
                }
                window.draw(start);
                window.draw(box);
                window.draw(text);
            }  
        }
        void select() {
            done = false;
            selected = true;
        }
        bool isselected(){
            return selected;
        }
    private:
        sf::Text start;  
        sf::Text text;      
        std::string chars;
        std::string init;
        bool done = false;
        bool selected = false;
        bool valid = false;
        sf::Vector2<float> coords;
        sf::RectangleShape box;


};