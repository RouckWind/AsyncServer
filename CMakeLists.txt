cmake_minimum_required(VERSION 3.23)
project(asyncserver)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME asyncserver)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt5 REQUIRED COMPONENTS
        Widgets
    )

set(HEADERS

)

set(SOURCES
    main.cpp
)


add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} Qt5::Widgets)
