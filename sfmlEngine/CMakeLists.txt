
set(CMAKE_CXX_STANDARD 23)

add_library(sfmlEngine
        window.cpp
)

target_link_libraries(sfmlEngine
        PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
)

target_include_directories(sfmlEngine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)