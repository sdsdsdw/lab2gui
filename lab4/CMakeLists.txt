cmake_minimum_required(VERSION 3.22.1)

project(photoEditor)

list(APPEND CMAKE_PREFIX_PATH "/home/sdf/Qt/6.6.0/gcc_64/")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

add_executable(photoEditor
    src/main.cpp
    src/imageEditor.cpp
)

target_link_libraries(photoEditor
    Qt6::Widgets
)