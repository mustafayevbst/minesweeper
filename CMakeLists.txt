cmake_minimum_required(VERSION 3.14)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Укажи папку, где лежит SFMLConfig.cmake (обычно в lib/cmake/SFML)
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")

find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

add_executable(minesweeper
    main.cpp
    src/Game.cpp
    src/Board.cpp
)

target_include_directories(minesweeper PRIVATE
    "src"
)

target_link_libraries(minesweeper PRIVATE
    sfml-graphics
    sfml-window
    sfml-system
)
add_custom_command(TARGET minesweeper POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/bin"
    $<TARGET_FILE_DIR:minesweeper>
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets"
    $<TARGET_FILE_DIR:minesweeper>/assets
)
