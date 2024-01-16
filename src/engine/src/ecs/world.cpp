////////////////////////
//
//  Created on Mon Sep 18 2023
//
//  world.cpp
//
////////////////////////

#include "ecs/world.hpp"
#include "patterns.hpp"
#include "config.hpp"
#include <sstream>

namespace engine::ecs
{
    Entity World::createEntity()
    {
        if (m_available_entities.size()) {
            Entity entity = m_available_entities.front();
            m_available_entities.erase(m_available_entities.begin());
            return entity;
        }

        return m_current_entity++;
    }

    Entity World::getLastEntity() const
    {
        return m_current_entity;
    }

    std::size_t World::getEntityCount() const
    {
        return m_current_entity - m_available_entities.size();
    }

    bool World::isAvailableEntity(const Entity &entity) const
    {
        return std::find(m_available_entities.begin(), m_available_entities.end(), entity) == m_available_entities.end();
    }

    void World::destroyEntity(const Entity &entity, DestroyEntityCallback callback)
    {
        #if DEBUG_DISPLAY_DESTROY_ENTITY
            std::cout << "Destroy entity: " << entity << std::endl;
        #endif

        m_request_destroy_entities.push_back({entity, callback});
    }

    void World::applyRequests()
    {
        if (m_clear) {
            m_available_entities.clear();
            m_current_entity = 0;
            m_components.clear();
            m_systems.clear();
            m_request_remove_components.clear();
            m_request_remove_systems.clear();
            m_request_destroy_entities.clear();
            m_clear = false;
        }
        for (auto component = m_request_remove_components.begin(); component != m_request_remove_components.end(); ++component)
            removeComponentPattern(*this, component->first, component->second);

        for (auto system = m_request_remove_systems.begin(); system != m_request_remove_systems.end(); ++system)
            removeSystem(*system);

        for (auto entity = m_request_destroy_entities.begin(); entity != m_request_destroy_entities.end(); ++entity) {
            if (std::find(m_available_entities.begin(), m_available_entities.end(), entity->first) == m_available_entities.end()) {
                if (entity->second)
                    entity->second(entity->first);
                destroyEntityPattern(*this, entity->first);
                m_available_entities.push_back(entity->first);
            }
        }

        m_request_remove_components.clear();
        m_request_remove_systems.clear();
        m_request_destroy_entities.clear();
    }

    void World::clear()
    {
        m_clear = true;
    }

    void World::launchSystems()
    {
        for (auto system = m_systems.begin(); system != m_systems.end(); ++system)
            (*system)();
    }

    void World::addSystem(const System &system)
    {
        if (!hasSystem(system))
            m_systems.push_back(system);
    }

    bool World::removeSystem(const System &system)
    {
        if (!system)
            return false;

        for (auto it = m_systems.begin(); it != m_systems.end(); ++it) {
            if (*it == system) {
                m_systems.erase(it);
                return true;
            }
        }
        return false;
    }

    void World::requestRemoveSystem(const System &system)
    {
        m_request_remove_systems.push_back(system);
    }

    bool World::hasSystem(const System &system) const
    {
        if (!system)
            return false;

        for (auto it = m_systems.begin(); it != m_systems.end(); ++it)
            if (*it == system)
                return true;
        return false;
    }

    void World::clearSystems()
    {
        m_systems.clear();
    }
}
