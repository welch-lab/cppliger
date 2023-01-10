# CMakeList.txt : CMake project for cppliger, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (cppliger "cppliger.cpp" "cppliger.h")

set_property(TARGET cppliger PROPERTY CXX_STANDARD 20)

target_link_libraries(cppliger PUBLIC Eigen3::Eigen ${ARMADILLO_LIBRARIES} leidenalg ModularityOptimizer libdeps HighFive HighFive_libdeps HighFive_HighFive)

# TODO: Add tests and install targets if needed.
