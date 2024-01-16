////////////////////////
//
//  Created on Wed Sep 27 2023
//
//  text.cpp
//
////////////////////////

#include "systems/render_text.hpp"
#include "render_data.hpp"

namespace render
{
    void renderText()
    {
        engine::ecs::Components<render::Text> &texts = engine::ecs::World::getInstance().getComponents<render::Text>();

        for (auto text = texts.begin(); text != texts.end(); ++text) {
            if (!text->has_value())
                continue;

            RenderData::getInstance().renderText(text->value().id);
        }
    }
}
