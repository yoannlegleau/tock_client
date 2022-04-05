/**
 * \file main.c
 * \brief gestion de l'application
 * \author JARRIER Allan
 * \date 20/01/2022
 *
 */
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include "Draw/mainSDL.h"
#include "game.h"
#include "parser.h"
#include "Color.h"

#ifdef __unix__
 #include <unistd.h>
 #include <pthread.h>
 #include <netinet/in.h>
 #include <sys/socket.h>
 #include <arpa/inet.h>
#endif

#define DATA 64

/*
void * doRecieving(void * sockID){

	int clientSocket = *((int *) sockID);

	while(1){

		char data[DATA];
		int read = recv(clientSocket,data,DATA,0);
		data[read] = '\0';
		printf("%s",data);

	}

}
 */

/**
 * \brief lancement du jeu et fermeture
 * \param argc
 * \param args
 * \return
 */
int main(int argc, char* args[]) {
    printf("GAME\n");
    winCreate();
    Game *game;
    game = gameCreate(4);
    addPlayer(game, 1);
    gameStart(game);
    /*
    do {
        printf("Je ")
        game = gameCreate(4);
        addPlayer(game, 1);
    }while(gameStart(game));
    */





    //ferme le jeu
    winDestroy();

    return 0;
}
