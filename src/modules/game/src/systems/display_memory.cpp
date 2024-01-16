////////////////////////
//
//  Created on Tue Oct 03 2023
//
//  display_memory.cpp
//
////////////////////////

#include "systems/display_memory.hpp"
#include "components/display_memory.hpp"
#include "events/time.hpp"

namespace game
{
    void DisplayEntitiesMemory()
    {
        engine::ecs::Components<DisplayEntitiesMemoryContainer> &containers = engine::ecs::World::getInstance().getComponents<DisplayEntitiesMemoryContainer>();
        engine::ecs::Entity last_entity = engine::ecs::World::getInstance().getLastEntity();
        std::size_t used_entities = 0;
        std::size_t nb_line = last_entity;

        for (auto container = containers.begin(); container != containers.end(); ++container) {
            if (!container->has_value())
                continue;

            container->value().timer += render::Time::getInstance().getDeltaTime();

            if (container->value().timer <= 0.05f)
                return;

            container->value().timer = 0;
            nb_line = nb_line / container->value().width + (last_entity % container->value().width != 0);

            for (std::size_t i = 0; i < container->value().last_nb_line; ++i)
                std::cout << container->value().line_up << container->value().line_clear;
            std::cout << std::flush;

            for (std::size_t y = 0; y < nb_line; ++y) {
                for (std::size_t x = 0; x < container->value().width; ++x) {
                    if (y * container->value().width + x < last_entity) {
                        if (engine::ecs::World::getInstance().isAvailableEntity(y * container->value().width + x)) {
                            std::cout << container->value().red_color;
                            ++used_entities;
                        } else
                            std::cout << container->value().green_color;
                        std::cout << "#";
                    } else
                        break;
                }
                std::cout << std::endl;
            }

            std::cout << container->value().reset_color;

            std::cout << "Entities: " << used_entities << "/" << last_entity << std::endl;
            container->value().last_nb_line = nb_line + 1;
        }

        // if (!container.has_value())
        //     return;

        // container->timer += render::Time::getInstance().getDeltaTime();

        // if (container->timer <= 0.05f)
        //     return;

        // container->timer = 0;
        // nb_line = nb_line / container->width + (last_entity % container->width != 0);

        // for (std::size_t i = 0; i < container->last_nb_line; ++i)
        //     std::cout << container->line_up << container->line_clear;
        // std::cout << std::flush;

        // for (std::size_t y = 0; y < nb_line; ++y) {
        //     for (std::size_t x = 0; x < container->width; ++x) {
        //         if (y * container->width + x < last_entity) {
        //             if (engine::ecs::World::getInstance().isAvailableEntity(y * container->width + x)) {
        //                 std::cout << container->red_color;
        //                 ++used_entities;
        //             } else
        //                 std::cout << container->green_color;
        //             std::cout << "#";
        //         } else
        //             break;
        //     }
        //     std::cout << std::endl;
        // }

        // std::cout << container->reset_color;

        // std::cout << "Entities: " << used_entities << "/" << last_entity << std::endl;
        // container->last_nb_line = nb_line + 1;
    }
}
