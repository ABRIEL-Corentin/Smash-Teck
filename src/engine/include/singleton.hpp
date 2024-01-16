////////////////////////
//
//  Created on Wed Sep 20 2023
//
//  singleton.hpp
//
////////////////////////

#pragma once

namespace engine
{
    template<typename T>
    class Singleton
    {
        public:
            static inline T &getInstance();
    };
}

#include "inl/singleton.inl"
