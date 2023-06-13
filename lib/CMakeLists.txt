cmake_minimum_required(VERSION 3.23)
project(mylib)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME mylib)

set(SOURCES
        src/server.cpp
        src/threadpool.cpp
        src/client.cpp
        src/threadSafeQueue.cpp
)

set(HEADERS
        inc/server.h
        inc/threadpool.h
        inc/client.h
        inc/threadSafeQueue.h
)

add_library(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)

importQt5(${PROJECT_NAME})
