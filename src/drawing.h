#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"


namespace draw {
    void transformpt(vectorR3& vec, int windowy); // from our coordinates to SFML's
    void transformvec(vectorR3& vec, int windowy);
    void drawvector(sf::RenderWindow &win, vectorR3 start, vectorR3 vec); //Check both vectors have z component 0
};