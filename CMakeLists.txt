cmake_minimum_required(VERSION 3.16)

project(qt-minesweeper VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(Qt6_DIR /home/gz/Qt/6.7.2/gcc_64/lib/cmake/Qt6)
set(Qt6CoreTools_DIR /home/gz/Qt/6.7.2/gcc_64/lib/cmake/Qt6CoreTools)
set(Qt6GuiTools_DIR /home/gz/Qt/6.7.2/gcc_64/lib/cmake/Qt6GuiTools)
set(Qt6WidgetsTools_DIR /home/gz/Qt/6.7.2/gcc_64/lib/cmake/Qt6WidgetsTools)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

qt_add_executable(qt-minesweeper
    main.cpp
    Game.cpp
    IntroWidget.cpp
    DifficultyDialog.cpp
    PlayDialog.cpp
)

target_include_directories(qt-minesweeper PRIVATE ./include)
target_link_libraries(qt-minesweeper PRIVATE Qt6::Widgets)

set_target_properties(qt-minesweeper PROPERTIES
    WIN32_EXECUTABLE ON
    MACOSX_BUNDLE ON
)
