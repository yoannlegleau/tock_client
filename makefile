CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L ${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I ${SDL_INC_DIR}

game:
	${CC} -o game src/linkedlist.c src/card.c src/menu.c src/gameRule.c src/bord.c src/Player/player.c src/mainSDL.c src/game.c src/main.c ${LIBS} ${INCS}

menu:
		${CC} -o menu src/mainSDL.c src/menu.c ${LIBS} ${INCS}
