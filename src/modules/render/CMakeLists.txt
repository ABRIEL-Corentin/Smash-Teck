add_library(
    render
    SHARED

    src/render_data.cpp
    src/systems/window_manager.cpp
    src/systems/fps_display.cpp
    src/systems/render_shape.cpp
    src/systems/animation.cpp
    src/systems/render_text.cpp
    src/components/shape.cpp
    src/components/animation.cpp
    src/components/text.cpp
    src/components/sound.cpp
    src/events/keyboard.cpp
    src/events/time.cpp
    src/math/color.cpp
)

target_include_directories(
    render
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../math/include/
    ${CMAKE_CURRENT_SOURCE_DIR}/../../engine/include/
)

target_link_libraries(
	render

    sfml-graphics
    sfml-audio
    sfml-window
    sfml-system
)
