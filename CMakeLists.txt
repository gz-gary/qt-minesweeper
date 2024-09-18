cmake_minimum_required(VERSION 3.16)

project(qt-minesweeper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_PREFIX_PATH /home/gz/Qt/6.7.2/gcc_64/lib/cmake/Qt6)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(qt-minesweeper
    main.cpp
    IntroWidget.cpp
)

target_link_libraries(qt-minesweeper PRIVATE Qt6::Widgets)

set_target_properties(qt-minesweeper PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
