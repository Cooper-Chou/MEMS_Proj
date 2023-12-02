cmake_minimum_required(VERSION 3.10)

project(button_blink)

set(SRC_LIST button_blink.cpp LED_Controller.cpp LED_StateDefine.cpp bsp.cpp)

add_executable(${PROJECT_NAME} ${SRC_LIST})
