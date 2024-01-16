import os
import json
import sys

# output file generated
OUTPUT_FILE = sys.argv[1]

# path that contain all modules to extract components and systems
MODULES_DIR = "../modules"

blacklist = sys.argv[2:]

includes = []
components = []
systems = []
functions = []

# navigate for find all modules
for module in os.listdir(MODULES_DIR):

    # pass if there is not a module
    if os.path.isfile(module) or module in blacklist:
        continue

    # search "module.json" file inside each module
    for file in os.listdir(MODULES_DIR + "/" + module):

        # pass if the current file is not "module.json"
        if file != "module.json":
            continue

        # extract data from module
        with open(MODULES_DIR + "/" + module + "/" + file, "r") as file_content:
            json_content = json.loads(file_content.read())

            # extract components
            if  "components" in json_content:
                for component in json_content["components"]:
                    if "name" in component:
                        components.append(component["name"])

                    if "path" in component:
                        includes.append("../" + MODULES_DIR + "/" + module + "/" + component["path"])

            # extract systems
            if "systems" in json_content:
                for system in json_content["systems"]:
                    if "name" in system:
                        systems.append(system["name"])

                    if "path" in system:
                        includes.append("../" + MODULES_DIR + "/" + module + "/" + system["path"])

            # extract functions
            if "functions" in json_content:
                for function in json_content["functions"]:
                    if "name" in function:
                        functions.append(function["name"])

                    if "path" in function:
                        includes.append("../" + MODULES_DIR + "/" + module + "/" + function["path"])

        break

# Write macros for patterns
def write_macros(file):
    file.write(f"\n#define CHECK_ADD_COMPONENT_STREAM(type_str, input, type, data) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tif (type_str == input) {{ \\\n")
    file.write(f"\t\t\tworld.addComponent<type>(entity, data); \\\n")
    file.write(f"\t\t\treturn true; \\\n")
    file.write(f"\t\t}} \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_ADD_COMPONENT_JSON(type_str, input, type, value) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tif constexpr (engine::ecs::CanLoadWithJson<type>) {{ \\\n")
    file.write(f"\t\t\tif (type_str == input) {{ \\\n")
    file.write(f"\t\t\t\tworld.addComponent<type>(entity, value); \\\n")
    file.write(f"\t\t\t\treturn true; \\\n")
    file.write(f"\t\t\t}} \\\n")
    file.write(f"\t\t}} \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_REMOVE_COMPONENT(type_str, input, type) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tif (type_str == input) {{ \\\n")
    file.write(f"\t\t\treturn world.removeComponent<type>(entity); \\\n")
    file.write(f"\t\t}} \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_ADD_SYSTEM(type_str, input, type) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tif (type_str == input) {{ \\\n")
    file.write(f"\t\t\tworld.addSystem(type); \\\n")
    file.write(f"\t\t\treturn true; \\\n")
    file.write(f"\t\t}} \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_REMOVE_SYSTEM(type_str, input, type) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tif (type_str == input) {{ \\\n")
    file.write(f"\t\t\treturn world.removeSystem(type); \\\n")
    file.write(f"\t\t}} \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_GET_FUNCTION_PTR(name, input, function) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tif (name == input) \\\n")
    file.write(f"\t\t\treturn reinterpret_cast<void *>(function); \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_EXTRACT_COMPONENT(type) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tJson::Value value = ecs::World::getInstance().extractComponentData<type>(entity); \\\n")
    file.write(f"\t\tif (value != Json::nullValue) \\\n")
    file.write(f"\t\t\tcomponents.append(value); \\\n")
    file.write(f"\t}} \\\n")

    file.write(f"\n#define CHECK_EXTRACT_SYSTEM(type) \\\n")
    file.write(f"\t{{ \\\n")
    file.write(f"\t\tJson::Value value = ecs::World::getInstance().extractSystemData(entity, type); \\\n")
    file.write(f"\t\tif (value != Json::nullValue) \\\n")
    file.write(f"\t\t\tsystems.append(value); \\\n")
    file.write(f"\t}} \\\n")

# write add component patterns into file
def write_add_components_stream(file):
    file.write(f"\tbool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, std::istream &data)\n")
    file.write(f"\t{{\n")

    if len(components):
        for component in components:
            file.write(f"\t\tCHECK_ADD_COMPONENT_STREAM(\"{component}\", type, {component}, data);\n")
    else:
        file.write(f"\t\t((void)world);\n")
        file.write(f"\t\t((void)entity);\n")
        file.write(f"\t\t((void)data);\n")

    file.write(f"\t\treturn false;\n")
    file.write(f"\t}}\n")

def write_add_components_json(file):
    file.write(f"\tbool addComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type, Json::Value &value)\n")
    file.write(f"\t{{\n")

    if len(components):
        for component in components:
            file.write(f"\t\tCHECK_ADD_COMPONENT_JSON(\"{component}\", type, {component}, value);\n")
    else:
        file.write(f"\t\t((void)world);\n")
        file.write(f"\t\t((void)entity);\n")

    file.write(f"\t\treturn false;\n")
    file.write(f"\t}}\n")

# write remove component patterns into file
def write_remove_components(file):
    file.write(f"\tbool removeComponentPattern(ecs::World &world, ecs::Entity entity, const std::string &type)\n")
    file.write(f"\t{{\n")

    if len(components):
        for component in components:
            file.write(f"\t\tCHECK_REMOVE_COMPONENT(\"{component}\", type, {component});\n")
    else:
        file.write(f"\t\t((void)world);\n")
        file.write(f"\t\t((void)entity);\n")

    file.write(f"\t\treturn false;\n")
    file.write(f"\t}}\n")

# write systems patterns into file
def write_add_systems(file):
    file.write(f"\tbool addSystemPattern(ecs::World &world, const std::string &system)\n")
    file.write(f"\t{{\n")

    if len(systems):
        for system in systems:
            file.write(f"\t\tCHECK_ADD_SYSTEM(\"{system}\", system, {system})\n")
    else:
        file.write(f"\t\t((void)world);\n")
        file.write(f"\t\t((void)system);\n")

    file.write(f"\t\treturn false;\n")
    file.write(f"\t}}\n")

def write_remove_systems(file):
    file.write(f"\tbool removeSystemPattern(ecs::World &world, const std::string &system)\n")
    file.write(f"\t{{\n")

    if len(systems):
        for system in systems:
            file.write(f"\t\tCHECK_REMOVE_SYSTEM(\"{system}\", system, {system})\n")
    else:
        file.write(f"\t\t((void)world);\n")
        file.write(f"\t\t((void)system);\n")

    file.write(f"\t\treturn false;\n")
    file.write(f"\t}}\n")

# write destroy entity patterns into file
def write_destroy_entity(file):
    file.write(f"\tvoid destroyEntityPattern(ecs::World &world, ecs::Entity entity)\n")
    file.write(f"\t{{\n")

    if len(components):
        for component in components:
            file.write(f"\t\tworld.removeComponent<{component}>(entity);\n")
    else:
        file.write(f"\t\t((void)world);\n")
        file.write(f"\t\t((void)entity);\n")

    file.write(f"\t}}\n")

def write_get_function_ptr(file):
    file.write(f"\tvoid *getFunctionPattern(const std::string &function_name)\n")
    file.write(f"\t{{\n")

    if len(functions):
        for function in functions:
            file.write(f"\t\tCHECK_GET_FUNCTION_PTR(\"{function}\", function_name, {function})\n")
    else:
        file.write(f"\t\t((void)function_name);\n")

    file.write(f"\t\treturn nullptr;\n")
    file.write(f"\t}}\n")

def write_extract_entity_data(file):
    file.write(f"\tstd::string extractEntityData(ecs::Entity entity)\n")
    file.write(f"\t{{\n")

    file.write(f"\t\tJson::Value root = Json::Value();\n")
    file.write(f"\t\tJson::Value components = Json::Value(Json::arrayValue);\n")
    file.write(f"\t\tJson::Value systems = Json::Value(Json::arrayValue);\n\n")
    file.write(f"\t\tJson::FastWriter writer = Json::FastWriter();\n\n")

    if len(components) and len(systems):
        for component in components:
            file.write(f"\t\tCHECK_EXTRACT_COMPONENT({component});\n")

        file.write(f"\n")
        for system in systems:
            file.write(f"\t\tCHECK_EXTRACT_SYSTEM({system});\n")
    else:
        file.write(f"\t\t((void)entity);\n")

    file.write(f"\n\t\troot[\"components\"] = components;\n")
    file.write(f"\t\troot[\"systems\"] = systems;\n")
    file.write(f"\t\treturn writer.write(root);\n")
    file.write(f"\t}}\n")

# generate patterns file
with open(OUTPUT_FILE, "w") as file:

    # write import headers
    file.write(f"#include \"ecs/world.hpp\"\n")
    file.write(f"#include \"ecs/concepts.hpp\"\n")
    for include in set(includes):
        file.write(f"#include \"{include}\"\n")

    write_macros(file)

    file.write(f"\nnamespace engine\n{{\n")

    write_add_components_stream(file)
    file.write("\n")
    write_add_components_json(file)
    file.write("\n")
    write_remove_components(file)
    file.write("\n")
    write_add_systems(file)
    file.write("\n")
    write_remove_systems(file)
    file.write("\n")
    write_destroy_entity(file)
    file.write("\n")
    write_get_function_ptr(file)
    file.write("\n")
    write_extract_entity_data(file)

    file.write(f"}}\n")
