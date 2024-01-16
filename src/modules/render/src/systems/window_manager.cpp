////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  window_manager.cpp
//
////////////////////////

#include "systems/window_manager.hpp"
#include "render_data.hpp"

namespace render
{
    void windowManager()
    {
        RenderData::getInstance().update();
    }
}
