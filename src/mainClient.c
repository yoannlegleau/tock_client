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
#include "mainSDL.h"
#include "game.h"

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
    //lance le jeu dans la fenêtre principal

    int option;
    char *ip_address = NULL;

    //if (ip_address) printf("IP_ADDRESS: %s\n", ip_address);

    /*
    int clientSocket = socket(PF_INET, SOCK_STREAM, 0);

    struct sockaddr_in serverAddr;

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8080);
    //serverAddr.sin_addr.s_addr = inet_addr("172.18.41.223");
    //serverAddr.sin_addr.s_addr = inet_addr(ip_address);
    serverAddr.sin_addr.s_addr = htons(INADDR_ANY);

    if(connect(clientSocket, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) == -1) return 0;

    printf("Connection established ............\n");

    pthread_t thread;
    pthread_create(&thread, NULL, doRecieving, (void *) &clientSocket );

    while(1){

      char input[DATA];
      scanf("%s",input);

      if(strcmp(input,"TEST") == 0){
        send(clientSocket,input,DATA,0);
      }
      if(strcmp(input,"START") == 0){
        send(clientSocket,input,DATA,0);
      }
      if(strcmp(input,"PLAY") == 0){
        send(clientSocket,input,DATA,0);
        scanf("%[^\n]s",input);
        send(clientSocket,input,DATA,0);
      }
    }
    */

    winCreate();
    Game *game = gameCreate(4);
    addPlayer(game, 4);
    gameStart(game);

    // ferme le jeu
    winDestroy();

    return 0;
}
