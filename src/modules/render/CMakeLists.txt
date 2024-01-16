add_library(
    render
    SHARED

    src/empty.cpp
    src/systems/test_system.cpp
)

target_include_directories(
    render
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../engine/include/
)

target_link_libraries(
	render

    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
)
