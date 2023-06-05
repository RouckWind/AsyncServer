cmake_minimum_required(VERSION 3.23)
project(asyncserver)

set(CMAKE_MODULE_PATH "${CMAKE_BINARY_DIR};${CMAKE_MODULE_PATH}")

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME asyncserver)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

macro(importQt5 TARGET_NAME)
    if(Qt5_FOUND)
        target_link_libraries(${TARGET_NAME}  PRIVATE Qt5::Core Qt5::Widgets)
        set_target_properties(${TARGET_NAME} PROPERTIES AUTOMOC ON AUTORCC ON)
    endif ()
endmacro()

add_subdirectory(gui)
add_subdirectory(lib)
add_subdirectory(sender)

