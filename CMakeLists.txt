cmake_minimum_required(VERSION 4.0)
project(ShapeViewer)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW TRUE
)

set(SFML_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_DOC OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "" FORCE)
set(SFML_BUILD_NETWORK OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(sfml)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/sfmlEngine
                    ${CMAKE_CURRENT_SOURCE_DIR}/shapeEngine)

add_subdirectory(sfmlEngine)
add_subdirectory(shapeEngine)

add_executable(ShapeViewer main.cpp)

target_link_libraries(ShapeViewer
        PUBLIC
        sfml-graphics
        sfml-window
        sfml-system
        PRIVATE
        sfmlEngine
        shapeEngine)

# копируем нужные нам DLL-ки
if(WIN32)
    add_custom_command(TARGET ShapeViewer POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:ShapeViewer>)
endif()