////////////////////////
//
//  Created on Mon Sep 18 2023
//
//  world.hpp
//
////////////////////////

#pragma once

#include "types.hpp"
#include "singleton.hpp"
#include "config.hpp"
#include "ecs/concepts.hpp"
#include "patterns.hpp"
#include <iostream>
#include <type_traits>
#include <json/json.h>

namespace engine::ecs
{
    class World : public Singleton<World>
    {
        public:
            World() = default;

            Entity createEntity();
            Entity getLastEntity() const;
            std::size_t getEntityCount() const;
            bool isAvailableEntity(const Entity &entity) const;
            void destroyEntity(const Entity &entity, DestroyEntityCallback callback = nullptr);
            void applyRequests();
            void clear();
            void launchSystems();

            void addSystem(const System &system);
            void requestRemoveSystem(const System &system);
            bool hasSystem(const System &system) const;
            void clearSystems();

            template<typename T>
            Component<T> &getComponent(const Entity &entity);

            template<typename T>
            Components<T> &getComponents();

            template<typename T, typename ... ARGS>
            Component<T> &addComponent(const Entity &entity, ARGS &&... args);

            template<typename T>
            bool hasComponent(const Entity &entity);

            template<typename T>
            inline void requestRemoveComponent(const Entity &entity);

            template<typename T>
            void registerComponent();

            friend bool ::engine::removeComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type);
            friend bool ::engine::removeSystemPattern(ecs::World &world, const std::string &system);
            friend void ::engine::destroyEntityPattern(ecs::World &world, ecs::Entity entity);

        private:
            Entities m_available_entities;
            Entity m_current_entity;
            ComponentsContainer m_components;
            Systems m_systems;
            RemoveDataContainer m_request_remove_components;
            Systems m_request_remove_systems;
            RequestDestroyEntities m_request_destroy_entities;
            bool m_clear;

            bool removeSystem(const System &system);

            template<typename T>
            bool removeComponent(const Entity &entity);
    };
}

#include "ecs/inl/world.inl"
