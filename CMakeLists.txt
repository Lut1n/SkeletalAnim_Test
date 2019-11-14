cmake_minimum_required(VERSION 3.5)

project(SkeletalAnim_Test)

set(SRCS
    main.cpp
    JoinRenderer.cpp
    SkinRenderer.cpp
    WindRenderer.cpp
    Animator.cpp
    Join.cpp
    Graph.cpp
    math_vector.cpp
    )

set(HEADERS
    JoinRenderer.hpp
    SkinRenderer.hpp
    WindRenderer.hpp
    Animator.hpp
    Join.hpp
    Graph.hpp
    math_vector.hpp
    WindFx_Glsl.hpp
    vertex_shader.hpp
    )

add_definitions("-Wall -Werror -g")

add_executable(SkeletalTest ${SRCS} ${HEADERS})

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")

find_package(SFML 2.4 COMPONENTS graphics REQUIRED)

target_link_libraries(SkeletalTest sfml-graphics)
target_link_libraries(SkeletalTest sfml-window)
target_link_libraries(SkeletalTest sfml-system)
