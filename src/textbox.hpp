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
            text.setFont(font);
            text.setFillColor(sf::Color::Black);
            text.setString("");
            text.setCharacterSize(24);
            text.setPosition(x,y);
            chars = text.getString();
            this->init = init;
            selected = false;
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
                        selected = false;
                        done = true;
                    }


                }
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

            if(selected){
                sf::String s = (init+chars+"_").c_str();
                text.setString(s);
                if(chars!=""){
                    std::string s = text.getString();
                }
                
            }
            else{
                text.setString(init+chars);
            }
            window.draw(text);
        }
        void select() {
            done = false;
            selected = true;
        }
        bool isselected(){
            return selected;
        }
    private:
        sf::Text text;      
        std::string chars;
        std::string init;
        bool done = false;
        bool selected = false;

};