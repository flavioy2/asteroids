cmake_minimum_required(VERSION 3.10)
project(AsteroidsGL CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

add_executable(AsteroidsGL
    src/mainAsteroids.cpp
    src/Asteroid.cpp
    src/Bullet.cpp
    src/Flame.cpp
    src/ObjectsList.cpp
    src/Shape.cpp
    src/Ship.cpp
    src/Ovni.cpp
)

target_include_directories(AsteroidsGL PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${OPENGL_INCLUDE_DIR}
    ${GLUT_INCLUDE_DIR}
)

target_link_libraries(AsteroidsGL PRIVATE
    OpenGL::GL
    GLUT::GLUT
    $<$<BOOL:${OPENGL_glu_LIBRARY}>:OpenGL::GLU>
)

if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    target_link_libraries(AsteroidsGL PRIVATE ${COCOA_LIBRARY})
endif()

if(MSVC)
    target_compile_options(AsteroidsGL PRIVATE /w)
    target_compile_definitions(AsteroidsGL PRIVATE _CRT_SECURE_NO_WARNINGS)
else()
    target_compile_options(AsteroidsGL PRIVATE -w)
endif()
