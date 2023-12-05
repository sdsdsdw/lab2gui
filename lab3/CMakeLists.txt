cmake_minimum_required(VERSION 3.22.1)

project(notepad)

list(APPEND CMAKE_PREFIX_PATH "/home/sdf/Qt/6.6.0/gcc_64/")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_executable(notepad
    src/main.cpp
    src/notepad.cpp
)

target_link_libraries(notepad
    Qt6::Widgets
)
