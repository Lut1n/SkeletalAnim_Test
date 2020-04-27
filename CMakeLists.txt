cmake_minimum_required(VERSION 3.5)

project(SkeletalAnim_Proj)

set(SRCS
    main.cpp
    maths/math_vector.cpp
    rendering/JointDrawable.cpp
    rendering/SkinDrawable.cpp
    rendering/WeightDrawable.cpp
    rendering/WindFx.cpp
    rigging/Animator.cpp
    rigging/Graph.cpp
    rigging/Joint.cpp
    )

set(HEADERS
    maths/math_vector.hpp
    rendering/JointDrawable.hpp
    rendering/SkinDrawable.hpp
    rendering/vertex_shader.hpp
    rendering/WeightDrawable.hpp
    rendering/WindFx.hpp
    rendering/WindFx_Glsl.hpp
    rigging/Animator.hpp
    rigging/Graph.hpp
    rigging/Joint.hpp
    )

add_definitions("-Wall -Werror -g")

add_executable(SkeletalAnim ${SRCS} ${HEADERS})

## If you want to link SFML statically
# set(SFML_STATIC_LIBRARIES TRUE)

## In most cases better set in the CMake cache
# set(SFML_DIR "<sfml root prefix>/lib/cmake/SFML")
set(SFML_DIR "C:/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.4 COMPONENTS graphics REQUIRED)

target_link_libraries(SkeletalAnim sfml-graphics)
# target_link_libraries(SkeletalTest sfml-window)
# target_link_libraries(SkeletalTest sfml-system)
