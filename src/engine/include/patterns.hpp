////////////////////////
//
//  Created on Tue Sep 19 2023
//
//  patterns.hpp
//
////////////////////////

#pragma once

#include "ecs/types.hpp"
#include <json/json.h>

namespace engine
{
    namespace ecs
    {
        class World;
    }

	bool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, std::istream &data);
	bool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, Json::Value &value);
	bool removeComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type);
	bool addSystemPattern(ecs::World &world, ecs::Entity entity, const std::string &system);
	bool removeSystemPattern(ecs::World &world, ecs::Entity entity, const std::string &system);
	void destroyEntityPattern(ecs::World &world, ecs::Entity entity);
    void *getFunctionPattern(const std::string &function_name);
    std::string extractEntityData(ecs::Entity entity);
}
