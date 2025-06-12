cmake_minimum_required(VERSION 3.14)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories("C:/Program Files/SFML-3.0.0/include")
link_directories("C:/Program Files/SFML-3.0.0/lib")


add_executable(minesweeper
    main.cpp
    src/Game.cpp
    src/Board.cpp
)

target_include_directories(minesweeper PRIVATE src)
target_link_libraries(minesweeper sfml-graphics sfml-window sfml-system)
