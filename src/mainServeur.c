#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include "game.h"

#define DATA 64

/*
gcc client.c -o client -lpthread
*/
int start = 1;
int clientCount = 0;
char output[DATA];


static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

struct client{

	int index;
	int sockID;
	struct sockaddr_in clientAddr;
	int len;
};

struct client Client[DATA];
pthread_t thread[DATA];

void * doNetworking(void * ClientDetail){

	struct client* clientDetail = (struct client*) ClientDetail;
	int index = clientDetail -> index;
	int clientSocket = clientDetail -> sockID;

	printf("Client %d connected.\n",index + 1);

	while(1){

		char data[DATA];
		int read = recv(clientSocket,data,DATA,0);
		data[read] = '\0';

		if(strcmp(data,"TEST") == 0){
			//read = recv(clientSocket,data,DATA,0);
			snprintf(output,DATA,"Ceci est un test\n");
			send(clientSocket,output,DATA,0);
		}

    if(strcmp(data,"START") == 0){
      start = 1;
    }

    if(strcmp(data,"PLAY") == 0){

    }

	}

	return NULL;

}

int main(){

	int serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	struct sockaddr_in serverAddr;

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(8080);
	serverAddr.sin_addr.s_addr = htons(INADDR_ANY);


	if(bind(serverSocket,(struct sockaddr *) &serverAddr , sizeof(serverAddr)) == -1) return 0;

	if(listen(serverSocket,DATA) == -1) return 0;


	printf("Server started listenting on port 8080 ...........\n");

	while(1){
		if(clientCount < 4){
			Client[clientCount].sockID = accept(serverSocket, (struct sockaddr*) &Client[clientCount].clientAddr, &Client[clientCount].len);
			Client[clientCount].index = clientCount;

			pthread_create(&thread[clientCount], NULL, doNetworking, (void *) &Client[clientCount]);

			clientCount ++;
		}
		if(start == 1){
      Game *game = gameCreate(4);
      addPlayer(game, clientCount);
      gameStart(game);
		}
	}

	for(int i = 0 ; i < clientCount ; i ++)
	pthread_join(thread[i],NULL);
}
