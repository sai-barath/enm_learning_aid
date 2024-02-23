#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"

class Artist {
    //Draws vectors
    public:
        void drawvector(sf::RenderWindow& win, const vectorR3& start, const vectorR3& vec);
    //Check both vectors have z component 9
};