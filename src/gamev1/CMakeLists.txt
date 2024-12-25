
add_executable(gamev1 main.cpp)
target_link_libraries(gamev1 PRIVATE game)

add_library(game STATIC game.cpp)
target_include_directories(game PUBLIC include)
target_link_libraries(game PUBLIC SDL2main SDL2-static)
