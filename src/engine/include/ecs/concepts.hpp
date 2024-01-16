////////////////////////
//
//  Created on Wed Sep 27 2023
//
//  concepts.hpp
//
////////////////////////

#pragma once

#include "ecs/types.hpp"
#include <sstream>
#include <json/json.h>

namespace engine::ecs
{
    template<typename T>
    concept HasOnDestroy = requires(T &t)
    {
        t.onDestroy();
    };

    template<typename T>
    concept HasExtractData = requires(T &t, Json::Value &value)
    {
        t.extractData(value);
    };

    template<typename T>
    concept CanLoadWithJson = requires(const Entity &entity, Json::Value &value)
    {
        T(entity, value);
    };
}
