#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "R3Vectors.h"
#include "point_charge.h"
#include <vector>


namespace draw {
    void transformpt(vectorR3& vec, int windowy); // from our coordinates to SFML's
    void transformvec(vectorR3& vec, int windowy);
    void drawvector(sf::RenderWindow &win, vectorR3 start, vectorR3 vec); //Check both vectors have z component 0
    void drawc(sf::RenderWindow& win, const PointCharge& pc);
    void drawefield(sf::RenderWindow& win, std::vector<PointCharge> charges, bool debug);
};