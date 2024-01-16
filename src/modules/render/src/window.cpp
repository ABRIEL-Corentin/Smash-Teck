////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  window.cpp
//
////////////////////////

#include "window.hpp"

namespace render
{
    Window::Window()
        : window({800, 600}, "Smash Teck")
    {
        window.setFramerateLimit(60);
    }
}
