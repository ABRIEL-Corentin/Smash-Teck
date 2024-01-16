////////////////////////
//
//  Created on Tue Oct 03 2023
//
//  display_memory.cpp
//
////////////////////////

#include "components/display_memory.hpp"

namespace game
{
    DisplayEntitiesMemoryContainer::DisplayEntitiesMemoryContainer(const engine::ecs::Entity &, std::istream &data)
        : line_up("\033[1A"),
          line_clear("\x1b[2K"),
          green_color("\033[0;32m"),
          red_color("\033[0;31m"),
          reset_color("\033[0m"),
          width(40),
          last_nb_line(0),
          timer(0)
    {
        data >> width;
    }

    DisplayEntitiesMemoryContainer::DisplayEntitiesMemoryContainer(const engine::ecs::Entity &, Json::Value &data)
    {
        line_up = ("\033[1A");
        line_clear = ("\x1b[2K");
        green_color = ("\033[0;32m");
        red_color = ("\033[0;31m");
        reset_color = ("\033[0m");
        width = (40);
        last_nb_line = (0);
        timer = (0);
        width = data["width"].asUInt64();
    }

    void DisplayEntitiesMemoryContainer::extractData(Json::Value &data) const
    {
        data["width"] = width;
    }
}
