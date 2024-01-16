#include "ecs/world.hpp"
#include "ecs/concepts.hpp"

#define CHECK_ADD_COMPONENT_STREAM(type_str, input, type, data) \
	{ \
		if (type_str == input) { \
			world.addComponent<type>(entity, data); \
			return true; \
		} \
	} \

#define CHECK_ADD_COMPONENT_JSON(type_str, input, type, value) \
	{ \
		if constexpr (engine::ecs::CanLoadWithJson<type>) { \
			if (type_str == input) { \
				world.addComponent<type>(entity, value); \
				return true; \
			} \
		} \
	} \

#define CHECK_REMOVE_COMPONENT(type_str, input, type) \
	{ \
		if (type_str == input) { \
			return world.removeComponent<type>(entity); \
		} \
	} \

#define CHECK_ADD_SYSTEM(type_str, input, type) \
	{ \
		if (type_str == input) { \
			return world.addSystem(entity, type); \
		} \
	} \

#define CHECK_REMOVE_SYSTEM(type_str, input, type) \
	{ \
		if (type_str == input) { \
			return world.removeSystem(entity, type); \
		} \
	} \

#define CHECK_GET_FUNCTION_PTR(name, input, function) \
	{ \
		if (name == input) \
			return reinterpret_cast<void *>(function); \
	} \

#define CHECK_EXTRACT_COMPONENT(type) \
	{ \
		Json::Value value = ecs::World::getInstance().extractComponentData<type>(entity); \
		if (value != Json::nullValue) \
			components.append(value); \
	} \

#define CHECK_EXTRACT_SYSTEM(type) \
	{ \
		Json::Value value = ecs::World::getInstance().extractSystemData(entity, type); \
		if (value != Json::nullValue) \
			systems.append(value); \
	} \

namespace engine
{
	bool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, std::istream &data)
	{
		((void)world);
		((void)entity);
		((void)data);
		return false;
	}

	bool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, Json::Value &value)
	{
		((void)world);
		((void)entity);
		return false;
	}

	bool removeComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type)
	{
		((void)world);
		((void)entity);
		return false;
	}

	bool addSystemPattern(ecs::World &world, ecs::Entity entity, const std::string &system)
	{
		((void)world);
		((void)entity);
		((void)system);
		return false;
	}

	bool removeSystemPattern(ecs::World &world, ecs::Entity entity, const std::string &system)
	{
		((void)world);
		((void)entity);
		((void)system);
		return false;
	}

	void destroyEntityPattern(ecs::World &world, ecs::Entity entity)
	{
		((void)world);
		((void)entity);
		world.clearSystems(entity);
	}

	void *getFunctionPattern(const std::string &function_name)
	{
		((void)function_name);
		return nullptr;
	}

	std::string extractEntityData(ecs::Entity entity)
	{
		Json::Value root = Json::Value();
		Json::Value components = Json::Value(Json::arrayValue);
		Json::Value systems = Json::Value(Json::arrayValue);

		Json::FastWriter writer = Json::FastWriter();

		((void)entity);

		root["components"] = components;
		root["systems"] = systems;
		return writer.write(root);
	}
}
