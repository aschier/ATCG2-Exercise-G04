cmake_minimum_required(VERSION 2.8.10)
project(ATCG2-Mesh-Exercise)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_subdirectory(OpenMesh)

add_executable(mesh_exercise
	mesh_exercise.cpp
)

target_compile_definitions(mesh_exercise PUBLIC -D_USE_MATH_DEFINES)
target_compile_definitions(mesh_exercise  PUBLIC -DOM_STATIC_BUILD)

target_link_libraries(mesh_exercise PUBLIC
	OpenMeshCore
)

add_executable(center_exercise
	center_exercise.cpp
)
target_include_directories(center_exercise PUBLIC
	eigen3
)
