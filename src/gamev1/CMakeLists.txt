
add_executable(gamev1 main.cpp)
target_link_libraries(gamev1 PRIVATE game)

add_library(game STATIC game.cpp)
target_include_directories(game PUBLIC include)
target_link_libraries(game PUBLIC SDL2main SDL2-static SDL2_image texturemanager)

add_library(texturemanager STATIC TextureManager.cpp)
target_include_directories(texturemanager PUBLIC include)
target_link_libraries(texturemanager PUBLIC SDL2main SDL2-static SDL2_image)


# copy assets
set(SRC_DIR "${CMAKE_SOURCE_DIR}/resource/assets")
set(DEST_DIR "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets")
MESSAGE(NOTICE "Source dir: ${SRC_DIR}")
MESSAGE(NOTICE "Dest dir: ${DEST_DIR}")
add_custom_command(
    OUTPUT "${DEST_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${SRC_DIR}" "${DEST_DIR}"
    DEPENDS "${SRC_DIR}"
    COMMENT "copying ${SRC_DIR} to ${DEST_DIR}"
)
add_custom_target(copy_folder ALL DEPENDS "${DEST_DIR}")
