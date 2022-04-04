cmake_minimum_required(VERSION 3.20)
project(tock_client C)

set(CMAKE_C_STANDARD 99)

set(SDL2_INCLUDE_DIR C:/lib/SDL2-2.0.16/include)
set(SDL2_LIB_DIR C:/lib/SDL2-2.0.16/lib/x86)
include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

set(SDL2_TTF_INCLUDE_DIR C:/lib/SDL2_ttf/include)
set(SDL2_TTF_LIB_DIR C:/lib/SDL2_ttf/lib/x86)
include_directories(${SDL2_TTF_INCLUDE_DIR})
link_directories(${SDL2_TTF_LIB_DIR})

set(SDL2_image_INCLUDE_DIR C:/lib/SDL2_image-2.0.5/include)
set(SDL2_image_LIB_DIR C:/lib/SDL2_image-2.0.5/lib/x86)
include_directories(${SDL2_image_INCLUDE_DIR})
link_directories(${SDL2_image_LIB_DIR})

add_executable(tock_client src/mainClient.c src/game.c src/game.h src/Draw/mainSDL.c src/Draw/mainSDL.h src/linkedlist.c src/linkedlist.h src/card.c src/card.h src/gameRule.c src/gameRule.h src/Player/player.c src/Player/player.h src/board.c src/board.h src/Color.h src/parser.c src/parser.h src/Color.c src/Draw/Drawable.c src/Draw/Drawable.h)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)
target_link_libraries(${PROJECT_NAME} SDL2_ttf SDL2_ttf)
target_link_libraries(${PROJECT_NAME} SDL2_image SDL2_image)