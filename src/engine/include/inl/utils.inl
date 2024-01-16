////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  utils.inl
//
////////////////////////

#include "utils.hpp"

namespace engine
{
    template<typename ... ARGS>
    std::string concat(const ARGS &... args)
    {
        std::stringstream ss = std::stringstream();

        ((ss << args), ...);
        return ss.str();
    }
}
