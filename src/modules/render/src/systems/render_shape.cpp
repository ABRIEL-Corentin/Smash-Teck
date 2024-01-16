////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  render_shape.cpp
//
////////////////////////

#include "systems/render_shape.hpp"
#include "render_data.hpp"

namespace render
{
    void renderShape()
    {
        engine::ecs::Components<render::Shape> &shapes = engine::ecs::World::getInstance().getComponents<render::Shape>();

        for (auto shape = shapes.begin(); shape != shapes.end(); ++shape) {
            if (!shape->has_value())
                continue;

            RenderData::getInstance().renderShape(shape->value().id);
        }
    }
}
