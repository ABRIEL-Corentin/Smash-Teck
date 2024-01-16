////////////////////////
//
//  Created on Wed Sep 27 2023
//
//  utils.hpp
//
////////////////////////

#pragma once

#include <sstream>

namespace engine
{
    template<typename ... ARGS>
    std::string concat(const ARGS &... args);
}

#include "inl/utils.inl"
