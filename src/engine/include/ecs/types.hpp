////////////////////////
//
//  Created on Mon Sep 18 2023
//
//  types.hpp
//
////////////////////////

#pragma once

#include <vector>
#include <map>
#include <unordered_map>
#include <optional>
#include <any>
#include <typeindex>
#include <memory>
#include <functional>
#include <cxxabi.h>

namespace engine::ecs
{
    using Entity = std::size_t;
    using Entities = std::vector<Entity>;
    using ComponentsContainer = std::unordered_map<std::type_index, std::any>;
    using RemoveDataContainer = std::vector<std::pair<Entity, std::string>>;
    using System = void (*)(const Entity &);
    using Systems = std::vector<System>;
    using SystemsContainer = std::vector<Systems>;
    using DestroyEntityCallback = void (*)(const Entity &);
    using RestoreEntityCallback = void (*)(const Entity &);
    using RequestRestoreEntities = std::vector<std::pair<std::string, RestoreEntityCallback>>;
    using RequestDestroyEntities = std::vector<std::pair<Entity, DestroyEntityCallback>>;

    template<typename T>
    using Component = std::optional<T>;

    template<typename T>
    using Components = std::vector<Component<T>>;

    template<typename T>
    std::string typeName();

    std::string functionName(void *func);
}

#include "ecs/inl/types.inl"
