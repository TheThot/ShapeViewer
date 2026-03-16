
set(CMAKE_CXX_STANDARD 23)

add_library(shapeEngine
        BaseShape.cpp
)

target_link_libraries(shapeEngine)

target_include_directories(shapeEngine
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)