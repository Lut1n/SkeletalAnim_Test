cmake_minimum_required(VERSION 3.5)

project(SkeletalAnim_Test)

set(SRCS
    main.cpp
    rendering/JointDrawable.cpp
    rendering/SkinDrawable.cpp
    rendering/WindFx.cpp
    rigging/Animator.cpp
    rigging/Joint.cpp
    rigging/Graph.cpp
    maths/math_vector.cpp
    )

set(HEADERS
    rendering/JointDrawable.hpp
    rendering/SkinDrawable.hpp
    rendering/WindFx.hpp
    rigging/Animator.hpp
    rigging/Joint.hpp
    rigging/Graph.hpp
    maths/math_vector.hpp
    rendering/WindFx_Glsl.hpp
    rendering/vertex_shader.hpp
    )

add_definitions("-Wall -Werror -g")

add_executable(SkeletalTest ${SRCS} ${HEADERS})

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.4 COMPONENTS graphics REQUIRED)

target_link_libraries(SkeletalTest sfml-graphics)
# target_link_libraries(SkeletalTest sfml-window)
# target_link_libraries(SkeletalTest sfml-system)
