cmake_minimum_required(VERSION 3.14)
project(Minesweeper)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Путь к SFMLConfig.cmake
set(SFML_DIR "${CMAKE_SOURCE_DIR}/external/SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Основной исполняемый файл
add_executable(minesweeper
    WIN32
    main.cpp
    src/Game.cpp
    src/Board.cpp
    src/Menu.cpp
)

target_include_directories(minesweeper PRIVATE
    src
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
    "${CMAKE_SOURCE_DIR}/assets/gameassets"
    $<TARGET_FILE_DIR:minesweeper>/assets
)

# --- Блок для тестов с Doctest ---

# Добавляем опцию для включения сборки тестов
option(BUILD_TESTS "Build tests" ON)

if(BUILD_TESTS)
    enable_testing()

    # Добавляем тестовый исполняемый файл
    add_executable(tests_board
        test/test_board.cpp  # файл с тестами
        src/Board.cpp        # исходники, чтобы тесты могли ссылаться на реализацию
    )

    target_include_directories(tests_board PRIVATE
        src
        test  # если там есть заголовки тестов
    )

    # Добавляем Doctest (предполагаем, что doctest.hpp лежит в external/doctest)
    target_include_directories(tests_board PRIVATE "${CMAKE_SOURCE_DIR}/external/doctest")

    # Линковка SFML, если Board.cpp зависит от SFML
    target_link_libraries(tests_board PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
    )

    # Добавляем тест в ctest
    add_test(NAME BoardTests COMMAND tests_board)

    add_executable(tests_game
        test/test_game.cpp
        src/Game.cpp
        src/Board.cpp
        src/Menu.cpp
    )
    target_include_directories(tests_game PRIVATE
        src
        test
        "${CMAKE_SOURCE_DIR}/external/doctest"
    )
    target_link_libraries(tests_game PRIVATE
        sfml-graphics
        sfml-window
        sfml-system
    )
    add_test(NAME GameTests COMMAND tests_game)

    add_executable(tests_menu
       test/test_menu.cpp
       src/Menu.cpp
    )

    target_include_directories(tests_menu PRIVATE
       src
       test
       ${CMAKE_SOURCE_DIR}/external/doctest
    ) 

    target_link_libraries(tests_menu PRIVATE
       sfml-graphics
       sfml-window
       sfml-system
    )

    add_test(NAME MenuTests COMMAND tests_menu)

endif()
