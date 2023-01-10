# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)
set(CMAKE_TOOLCHAIN_FILE "vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project ("cppliger")

find_package(Eigen3 CONFIG REQUIRED)
find_package(Armadillo CONFIG REQUIRED)
find_package(igraph CONFIG REQUIRED)
find_package(libleidenalg CONFIG REQUIRED)
find_package(HighFive CONFIG REQUIRED)

# Include sub-projects.

add_subdirectory ("vendor")
add_subdirectory ("cppliger")