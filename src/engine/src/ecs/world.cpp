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

    void World::requestRestoreEntityData(const std::string &data, RestoreEntityCallback callback)
    {
        m_request_restore_entity_data.push_back({data, callback});
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
            m_request_restore_entity_data.clear();
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

        for (auto request = m_request_restore_entity_data.begin(); request != m_request_restore_entity_data.end(); ++request)
            restoreEntityData(request->first, request->second);

        m_request_remove_components.clear();
        m_request_remove_systems.clear();
        m_request_destroy_entities.clear();
        m_request_restore_entity_data.clear();
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

    Json::Value World::extractSystemData(System system)
    {
        if (hasSystem(system))
            return Json::Value(functionName(reinterpret_cast<void *>(system)));
        return Json::nullValue;
    }

    void World::restoreEntityData(const std::string &data, RestoreEntityCallback callback)
    {
        Json::Reader reader = Json::Reader();
        Json::Value root = Json::Value();
        Json::Value components = Json::Value();
        Json::Value systems = Json::Value();
        ecs::Entity entity;

        if (!reader.parse(data, root)) {
            std::cerr << "Failed to load data for entity " << ":" << std::endl;
            std::cerr << data << std::endl;
            return;
        }

        entity = createEntity();

        components = root["components"];
        systems = root["systems"];

        for (auto component = components.begin(); component != components.end(); ++component)
            if (!addComponentPattern(*this, entity, (*component)["name"].asString(), *component))
                std::cerr << "Failed to add component '" << (*component)["name"].asString() << std::endl;

        for (auto system = systems.begin(); system != systems.end(); ++system)
            addSystemPattern(*this, system->asString());
        if (callback)
            callback(entity);
    }
}
