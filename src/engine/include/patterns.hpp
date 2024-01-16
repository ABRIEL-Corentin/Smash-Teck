////////////////////////
//
//  Created on Tue Sep 19 2023
//
//  patterns.hpp
//
////////////////////////

#pragma once

#include "ecs/types.hpp"

namespace engine
{
    namespace ecs
    {
        class World;
    }

	bool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, std::istream &data);
	bool removeComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type);
	bool addSystemPattern(ecs::World &world, const std::string &system);
	bool removeSystemPattern(ecs::World &world, const std::string &system);
	void destroyEntityPattern(ecs::World &world, ecs::Entity entity);
    void *getFunctionPattern(const std::string &function_name);
}
