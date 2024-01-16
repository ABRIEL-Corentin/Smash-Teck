////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  types.inl
//
////////////////////////

#include "ecs/types.hpp"

namespace engine::ecs
{
    template<typename T>
    std::string typeName()
    {
        int status;
        std::string tname = typeid(T).name();
        char *demangled_name = abi::__cxa_demangle(tname.c_str(), nullptr, nullptr, &status);

        if(!status) {
            tname = demangled_name;
            std::free(demangled_name);
        }
        return tname;
    }
}
