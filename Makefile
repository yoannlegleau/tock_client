CC=gcc
FLAGS=-Wall -g
SDL_DIR=${HOME}/SDL2
SDL_LIB_DIR=${SDL_DIR}/lib
SDL_INC_DIR=${SDL_DIR}/include
LIBS=-L ${SDL_LIB_DIR} -lSDL2 -lSDL2_image -lSDL2_ttf
INCS=-I ${SDL_INC_DIR}

BIN= game

game:
	${CC} -o game src/Draw/Drawable.c src/parser.c src/Color.c src/linkedlist.c src/card.c src/mainClient.c src/gameRule.c src/board.c src/Player/player.c src/Draw/mainSDL.c src/game.c -lpthread ${LIBS} ${INCS}

menu:
	${CC} -o menu src/mainSDL.c src/menu.c ${LIBS} ${INCS}

server:
	${CC} -o server src/linkedlist.c src/card.c src/mainServeur.c src/gameRule.c src/bord.c src/Player/player.c src/mainSDL.c src/game.c -lpthread ${LIBS} ${INCS}

clean:
	- rm game
	- rm menu
	- rm server

all: game