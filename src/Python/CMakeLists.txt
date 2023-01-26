set(TARGET_NAME pyliger)
find_package(pybind11 CONFIG REQUIRED)

file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp)
file(GLOB_RECURSE pyfiles pyliger/*.py)

CONFIGURE_FILE(setup.py.in
        ${CMAKE_CURRENT_BINARY_DIR}/setup.py @ONLY
        )

PYBIND11_ADD_MODULE("${TARGET_NAME}" MODULE src/conversions.hpp src/myclass_bindings.cpp)

target_compile_definitions("${TARGET_NAME}"
                           PRIVATE VERSION_INFO=${PYLIGER_VERSION_INFO})