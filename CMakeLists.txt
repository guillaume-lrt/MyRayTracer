cmake_minimum_required(VERSION 3.9)

project(MyRayTracer LANGUAGES CXX)

find_package(OpenMP REQUIRED)

add_executable (
	MyRayTracer
	Camera.hpp
	Image.hpp
	Main.cpp
	Mesh.hpp
	Ray.hpp
	Ray.cpp
	RayTracer.hpp
	Scene.hpp
	utils.hpp
	Vec3.h
)

set_target_properties(MyRayTracer PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)


INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/stb)
LINK_DIRECTORIES(${CMAKE_SOURCE_DIR}/stb) 

target_link_libraries(MyRayTracer PRIVATE OpenMP::OpenMP_CXX)

