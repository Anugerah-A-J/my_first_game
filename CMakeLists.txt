cmake_minimum_required(VERSION 3.10)

project(my_first_game)

find_package(Allegro CONFIG REQUIRED)

add_link_options(-static-libstdc++ -static-libgcc)
add_executable(my_first_game Character.cpp Game.cpp main.cpp Object.cpp Shape.cpp Collision.cpp UI.cpp)

if(MSVC)
    target_compile_options(my_first_game PRIVATE /W4 /WX)
else()
    target_compile_options(my_first_game PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

target_link_libraries(my_first_game PRIVATE allegro allegro_primitives allegro_font allegro_ttf)
