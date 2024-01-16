////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  fps_display.cpp
//
////////////////////////

#include "systems/fps_display.hpp"
#include "events/time.hpp"
#include <iostream>

namespace render
{
    void fpsDisplay()
    {
        std::cout << "\rFPS: " << (1.0f / Time::getInstance().getDeltaTime()) << std::flush;
    }
}
