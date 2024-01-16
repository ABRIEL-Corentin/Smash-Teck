
////////////////////////
//
//  Created on Tue Sep 26 2023
//
//  types.cpp
//
////////////////////////

#include "ecs/types.hpp"
#include <dlfcn.h>

namespace engine::ecs
{
    std::string functionName(void *func)
    {
        Dl_info info;
        int status;
        char *demangled_name;

        dladdr(func, &info);
        std::string name = info.dli_sname;

        demangled_name = abi::__cxa_demangle(name.c_str(), nullptr, nullptr, &status);

        if (!status) {
            name = demangled_name;
            std::free(demangled_name);
        }
        return name.substr(0, name.find('('));
    }
}
