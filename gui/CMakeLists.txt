cmake_minimum_required(VERSION 3.23)
project(gui)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME gui)

set(SOURCES
        src/mainwindow.cpp
        src/mainwindow.ui
        main.cpp
)

set(HEADERS
        inc/mainwindow.h
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
importQt5(${PROJECT_NAME})