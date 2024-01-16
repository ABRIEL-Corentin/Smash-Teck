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

        m_systems.push_back(Systems());
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
            removeSystemPattern(*this, system->first, system->second);

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
        Entity entity = 0;

        for (auto systems = m_systems.begin(); systems != m_systems.end(); ++systems) {
            for (auto system = systems->begin(); system != systems->end(); ++system)
                (*system)(entity);
            ++entity;
        }
    }

    bool World::addSystem(const Entity &entity, const System &system)
    {
        if (m_systems.size() <= entity || !system)
            return false;

        m_systems.at(entity).push_back(system);
        return true;
    }

    bool World::removeSystem(const Entity &entity, const System &system)
    {
        if (m_systems.size() <= entity || !system)
            return false;

        for (auto it = m_systems.at(entity).begin(); it != m_systems.at(entity).end(); ++it) {
            if (*it == system) {
                m_systems.at(entity).erase(it);
                return true;
            }
        }
        return false;
    }

    void World::requestRemoveSystem(const Entity &entity, const System &system)
    {
        m_request_remove_systems.push_back({entity, functionName(reinterpret_cast<void *>(system))});
    }

    bool World::hasSystem(const Entity &entity, const System &system) const
    {
        if (m_systems.size() <= entity || !system)
            return false;

        for (auto it = m_systems.at(entity).begin(); it != m_systems.at(entity).end(); ++it)
            if (*it == system)
                return true;
        return false;
    }

    void World::clearSystems(const Entity &entity)
    {
        if (m_systems.size() <= entity)
            return;

        m_systems.at(entity).clear();
    }

    Json::Value World::extractSystemData(const Entity &entity, System system)
    {
        if (hasSystem(entity, system))
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
            addSystemPattern(*this, entity, system->asString());
        if (callback)
            callback(entity);
    }
}
