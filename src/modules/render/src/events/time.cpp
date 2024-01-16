////////////////////////
//
//  Created on Mon Sep 25 2023
//
//  time.cpp
//
////////////////////////

#include "events/time.hpp"
#include <SFML/System.hpp>

namespace render
{
    void Time::update()
    {
        static sf::Clock clock = sf::Clock();

        _delta_time = clock.restart().asSeconds();
    }
}
