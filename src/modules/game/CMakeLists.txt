add_library(
    game
    SHARED

    src/components/player.cpp
    src/components/display_memory.cpp
    src/systems/player_movement.cpp
    src/systems/display_memory.cpp
)

target_include_directories(
    game
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../render/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../engine/include/
)
