add_library(gameobject STATIC gameobject.cpp)
target_include_directories(gameobject PUBLIC include)
target_link_libraries(gameobject PUBLIC SDL2-static texturemanager)
