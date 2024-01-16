////////////////////////
//
//  Created on Tue Oct 03 2023
//
//  display_memory.hpp
//
////////////////////////

#pragma once

#include "ecs/world.hpp"
#include <sstream>

namespace game
{
    using DisplayEntitiesMemoryContainer = struct DisplayEntitiesMemoryContainer
    {
        std::string line_up;
        std::string line_clear;
        std::string green_color;
        std::string red_color;
        std::string reset_color;
        std::size_t width;
        std::size_t last_nb_line;
        float timer;

        DisplayEntitiesMemoryContainer(const engine::ecs::Entity &entity, std::istream &data);
        DisplayEntitiesMemoryContainer(const engine::ecs::Entity &entity, Json::Value &data);
        void extractData(Json::Value &data) const;
    };
}
