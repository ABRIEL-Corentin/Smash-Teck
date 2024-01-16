////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  singleton.inl
//
////////////////////////

#include "singleton.hpp"

namespace engine
{
    template<typename T>
    inline T &Singleton<T>::getInstance()
    {
        static T instance = T();

        return instance;
    }
}
