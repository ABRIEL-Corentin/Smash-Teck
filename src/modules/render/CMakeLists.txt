add_library(
    render
    SHARED

    src/window.cpp
    src/systems/render_window.cpp
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
