////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  window.hpp
//
////////////////////////

#pragma once

#include "singleton.hpp"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace render
{
    using Window = struct Window : public engine::Singleton<Window>
    {
        sf::RenderWindow window;
        double delta_time;

        Window();
    };
}
