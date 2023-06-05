cmake_minimum_required(VERSION 3.23)
project(sender)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME sender)

set(SOURCES
        main.cpp
)

set(HEADERS

)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} PRIVATE mylib)

importQt5(${PROJECT_NAME})
