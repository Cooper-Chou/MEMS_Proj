cmake_minimum_required(VERSION 3.0.0)
project(GAME VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
include(CTest)
enable_testing()

LINK_DIRECTORIES(/usr/inlcude)

file(GLOB GC "./GameComponent/*.*pp")
file(GLOB SM "./StateMachine/*.*pp")
file(GLOB BSP "./BSP/*.*pp")


add_executable(GAME main.cpp
${GC}
${SM}
${BSP}

)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(${PROJECT_NAME} -lwiringPi)
