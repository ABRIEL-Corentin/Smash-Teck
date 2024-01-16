////////////////////////
//
//  Created on Tue Jan 16 2024
//
//  world.inl
//
////////////////////////

#include "ecs/world.hpp"

namespace engine::ecs
{
    template<typename T>
    Component<T> &World::getComponent(const Entity &entity)
    {
        static Component<T> null_component = std::nullopt;
        Components<T> &components = getComponents<T>();

        if (components.size() <= entity)
            return null_component;
        return components.at(entity);
    }

    template<typename T>
    Json::Value World::extractComponentData(const Entity &entity)
    {
        Components<T> &components = getComponents<T>();
        Json::Value value = Json::Value();

        if (components.size() <= entity || components.at(entity) == std::nullopt)
            return Json::nullValue;

        if constexpr (HasExtractData<T>) {
            value["name"] = typeName<T>();
            components.at(entity).value().extractData(value);
            return value;
        }
        return Json::nullValue;
    }

    template<typename T>
    Components<T> &World::getComponents()
    {
        auto components = m_components.find(std::type_index(typeid(T)));

        if (components == m_components.end()) {
            registerComponent<T>();
            return getComponents<T>();
        }
        return std::any_cast<Components<T> &>(components->second);
    }

    template<typename T, typename ... ARGS>
    Component<T> &World::addComponent(const Entity &entity, ARGS &&... args)
    {
        Components<T> &components = getComponents<T>();

        if (components.size() <= entity)
            components.resize(entity + 1);
        components.at(entity).emplace(entity, std::forward<ARGS>(args)...);
        return components.at(entity);
    }

    template<typename T>
    bool World::hasComponent(const Entity &entity)
    {
        Components<T> &components = getComponents<T>();

        return components.size() > entity && components.at(entity) != std::nullopt;
    }

    template<typename T>
    inline void World::requestRemoveComponent(const Entity &entity)
    {
        m_request_remove_components.push_back({entity, typeName<T>()});
    }

    template<typename T>
    void World::registerComponent()
    {
        if (m_components.find(std::type_index(typeid(T))) != m_components.end())
            return;

        m_components.insert({std::type_index(typeid(T)), Components<T>()});
    }

    template<typename T>
    bool World::removeComponent(const Entity &entity)
    {
        Components<T> &components = getComponents<T>();

        #if DEBUG_DISPLAY_DESTROY_ENTITY
            std::cout << "Entity " << entity << ": Remove component: " << typeName<T>() << std::endl;
        #endif

        if (components.size() <= entity || components.at(entity) == std::nullopt)
            return false;

        if constexpr (HasOnDestroy<T>)
            components.at(entity).value().onDestroy();
        components.at(entity).reset();
        return true;
    }
}
