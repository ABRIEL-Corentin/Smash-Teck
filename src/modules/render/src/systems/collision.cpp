////////////////////////
//
//  Created on Mon Sep 25 2023
//
//  collision.cpp
//
////////////////////////

#include "systems/collision.hpp"

namespace render
{
    void collisionProcess()
    {
        engine::ecs::Components<CollisionBox> &boxes = engine::ecs::World::getInstance().getComponents<CollisionBox>();
        engine::ecs::Components<Shape> &shapes = engine::ecs::World::getInstance().getComponents<Shape>();

        for (std::size_t i = 0; i < boxes.size(); ++i) {
            if (!boxes.at(i).has_value())
                continue;

            if (shapes.size() <= i || !shapes.at(i).has_value())
                continue;

            CollisionBox &box = boxes.at(i).value();
            Shape &shape = shapes.at(i).value();

            for (auto collide = box.collides.begin(); collide != box.collides.end(); ++collide)
                collide->collide = false;

            for (std::size_t j = 0; j < boxes.size(); ++j) {
                if (i == j)
                    continue;

                if (!boxes.at(j).has_value())
                    continue;

                if (shapes.size() <= j || !shapes.at(j).has_value())
                    continue;

                CollisionBox &other_box = boxes.at(j).value();
                Shape &other_shape = shapes.at(j).value();

                if (shape.getRect().intersects(other_shape.getRect())) {
                    auto collide_entity = std::find(box.collides.begin(), box.collides.end(), j);

                    if (collide_entity == box.collides.end()) {
                        box.collides.push_back(CollisionEntityStatus(j));

                        if (box.on_collision_enter)
                            box.on_collision_enter(box, other_box);

                        continue;
                    }

                    if (box.on_collision_stay)
                        box.on_collision_stay(box, other_box);

                    collide_entity->collide = true;
                }
            }

            for (std::size_t j = 0; j < box.collides.size(); ++j) {
                if (box.collides.at(j).collide)
                    continue;

                engine::ecs::Component<CollisionBox> &other_box = engine::ecs::World::getInstance().getComponent<CollisionBox>(box.collides.at(j).entity);

                if (box.on_collision_exit && other_box.has_value())
                    box.on_collision_exit(box, other_box.value());

                box.collides.erase(box.collides.begin() + j);
            }
        }

        // static engine::ecs::World &world = engine::ecs::World::getInstance();
        // engine::ecs::Component<render::CollisionBox> &box = engine::ecs::World::getInstance().getComponent<render::CollisionBox>(entity);
        // engine::ecs::Component<render::Shape> &shape = engine::ecs::World::getInstance().getComponent<render::Shape>(entity);
        // engine::ecs::Component<CollisionBox> &other_box = world.getComponent<CollisionBox>(0);
        // engine::ecs::Component<Shape> &other_shape = world.getComponent<Shape>(0);

        // if (!box.has_value() || !shape.has_value())
        //     return;

        // for (auto collide = box->collides.begin(); collide != box->collides.end(); ++collide)
        //     collide->collide = false;

        // for (engine::ecs::Entity entity_it = 0; entity_it <= world.getLastEntity(); ++entity_it) {
        //     other_box = world.getComponent<CollisionBox>(entity_it);
        //     other_shape = world.getComponent<Shape>(entity_it);

        //     if (!other_box.has_value() || !other_shape.has_value() || entity_it == entity)
        //         continue;

        //     if (shape->getRect().intersects(other_shape->getRect())) {
        //         auto collide_entity = std::find(box->collides.begin(), box->collides.end(), entity_it);

        //         if (collide_entity == box->collides.end()) {
        //             box->collides.push_back(CollisionEntityStatus(entity_it));

        //             if (box->on_collision_enter)
        //                 box->on_collision_enter(box.value(), other_box.value());

        //             continue;
        //         }

        //         if (box->on_collision_stay)
        //             box->on_collision_stay(box.value(), other_box.value());

        //         collide_entity->collide = true;
        //     }
        // }

        // for (std::size_t i = 0; i < box->collides.size(); ++i) {
        //     if (!box->collides.at(i).collide) {
        //         engine::ecs::Component<CollisionBox> &other_box = world.getComponent<CollisionBox>(box->collides.at(i).entity);

        //         if (box->on_collision_exit && other_box.has_value())
        //             box->on_collision_exit(box.value(), other_box.value());

        //         box->collides.erase(box->collides.begin() + i);
        //     }
        // }
    }
}
