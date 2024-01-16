add_executable(
    smash-teck

    src/main.cpp
    src/patterns.cpp
    src/application.cpp
    src/scene.cpp
    src/config.cpp
    src/ecs/world.cpp
    src/ecs/types.cpp
)

target_include_directories(
    smash-teck
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
)

target_link_libraries(
	smash-teck

    jsoncpp
    muparser
    dl
)

add_custom_command(
    OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/src/patterns.cpp

    COMMAND
    python3 scripts/generate_patterns.py "src/patterns.cpp" server drm_server

    DEPENDS
    scripts/generate_patterns.py

    WORKING_DIRECTORY
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_custom_target(
    generate_patterns_target

    DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/patterns.cpp
)

add_dependencies(
    smash-teck
    generate_patterns_target
)
