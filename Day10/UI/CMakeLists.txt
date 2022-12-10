# Almost all CMake files should start with this
# You should always specify a range with the newest
# and oldest tested versions of CMake. This will ensure
# you pick up the best policies.
cmake_minimum_required(VERSION 3.22.2)
project(SimpleUI)

set(raylib_INCLUDE_DIR "C:/Program Files (x86)/raylib/include")
find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(SOURCES main.cpp)
add_executable(${PROJECT_NAME} ${SOURCES})

set_target_properties(SimpleUI PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(SimpleUI PROPERTIES CXX_STANDARD 17)

add_subdirectory(libraries)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib raygui)
