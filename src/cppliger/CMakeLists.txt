set(TARGET_NAME cppliger)

file(GLOB_RECURSE headers include/cppliger/*.h include/cppliger/*.hpp)
file(GLOB_RECURSE sources src/*.cpp src/*.h src/*.hpp)

add_library(${TARGET_NAME} ${sources} ${headers})

target_include_directories(${TARGET_NAME} PRIVATE include/)
target_include_directories(${TARGET_NAME} SYSTEM INTERFACE include/)
