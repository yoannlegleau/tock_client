/**
* \file Player.c
* \brief gestion des joueurs
* \author LE GLEAU Yoann
* \date 23/02/2022
* \version 1
*/

#include <stdio.h>
#include <malloc.h>
#include "player.h"
#include "../mainSDL.h"

#ifdef __unix__
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#endif

#define DATA 64

char output[DATA];

bool playCard(Player *p, Bord * bord, enum Card * card, int location );


Player * playerFactory( int id){
  Player * player = malloc(sizeof(Player));
  player->idPlayer = id;
  player->cards = linkedListFactory(sizeof(enum Card));
  player->pt = &play;
  player->socket = 0;
  return player;
}

Player * clientFactory( int id, int clientSocket){
  Player * player = malloc(sizeof(Player));
  player->idPlayer = id;
  player->cards = linkedListFactory(sizeof(enum Card));
  player->pt = &playClient;
  player->socket = clientSocket;
  return player;
}

Player * botFactory( int id){
  Player * player = malloc(sizeof(Player));
  player->idPlayer = id;
  player->cards = linkedListFactory(sizeof(enum Card));
  player->pt = &playBot;
  player->socket = 0;
  return player;
}

Player * clientServerFactory(int id, int socket){
  Player * player = malloc(sizeof(Player));
  player->idPlayer = id;
  player->cards = linkedListFactory(sizeof(enum Card));
  player->pt = &playClientServer;
  player->socket = socket;
  return player;
}

void drawPlayer(const Player *player) {
  printf("player %i:\n Cartes:%i\n",player->idPlayer,length(player->cards));
  foreach(player->cards,drawCard);
}

int play(Player *p, Bord * bord) {
  Linkedlist * pownsLocations = getPlayerPansLocation(bord, p->idPlayer);
  bool played = false;
  for (int i = length(pownsLocations) ; i >= 0 ; i--) {
    int pownLocation = (int) get(pownsLocations, i);
    for (int j = 0; j <= length(p->cards); j++) {
      played = playCard(p, bord, get(p->cards, j), pownLocation);
      if (played) {
        printf("player %i a jouer ", p->idPlayer);
        drawCard(get(p->cards, j));
        removeElem(p->cards, j);
        return true;
      }
    }
  }
  if (!played && !isEmpty(p->cards)){
    printf("player %i a jeter ",p->idPlayer);
    drawCard(getFirst(p->cards));
    pollFirst(p->cards);
  }
  sleep(1);
  return false;
}

int playClient(Player *p, Bord * bord){

  snprintf(output,DATA,"PLAY");
  printf("Clien socket: %i", p->socket);
  send(p->socket,output,DATA,0);

  while(1){
    char data[64];
		int read = recv(p->socket,data,64,0);
		data[read] = '\0';
		printf("%s",data);

    int j = data[read];
    int i = data[read];

    int pownLocation = (int) get(pownsLocations, i);

    played = playCard(p, bord, get(p->cards, j), pownLocation);
    if (played) {
      printf("player %i a jouer ", p->idPlayer);
      drawCard(get(p->cards, j));
      removeElem(p->cards, j);
      return true;
    }
    if (!played && !isEmpty(p->cards)){
      printf("player %i a jeter ",p->idPlayer);
      drawCard(getFirst(p->cards));
      pollFirst(p->cards);
      return false;
    }
  }
  //printf("player %i a jouer comme un bot\n", p->idPlayer);
  //playBot(p,bord);
  //return false;
}

int playBot(Player *p, Bord * bord) {
  Linkedlist * pownsLocations = getPlayerPansLocation(bord, p->idPlayer);
  bool played = false;
  for (int i = length(pownsLocations) ; i >= 0 ; i--) {
    int pownLocation = (int) get(pownsLocations, i);
    for (int j = 0; j <= length(p->cards); j++) {
      played = playCard(p, bord, get(p->cards, j), pownLocation);
      if (played) {

        //Envoyer pownLocation coordonnées du pions
        //Envoyer get(p->cards, j)
        printf("player %i a jouer ", p->idPlayer);
        drawCard(get(p->cards, j));
        removeElem(p->cards, j);
        return true;
      }
    }
  }
  if (!played && !isEmpty(p->cards)){
    printf("player %i a jeter ",p->idPlayer);
    drawCard(getFirst(p->cards));
    pollFirst(p->cards);
  }
  return false;
}

int playClientServer(Player *p, Bord * bord) {
  snprintf(output,DATA,"PLAY");
  send(p->socket,output,DATA,0);
  while(1){
    char data[64];
    int read = recv(p->socket,data,DATA,0);
    data[read] = '\0';
    if(strcmp(data,"PPLAY") == 0){
      //return;
    }
  }
  return false;
}

bool playCard(Player *p, Bord *bord, enum Card *card, int location) {
  switch (*card) {
    case one:
    return forward(bord, location, 1);
    case two:
    return forward(bord, location, 2);
    case three:
    return forward(bord, location, 3);
    case four:
    return forward(bord,location, 4);
    case five:
    return forward(bord,location, 5);
    case six:
    return forward(bord, location, 6);
    case seven:
    return forward(bord, location, 7);
    case eight:
    return forward(bord, location, 8);
    case nine:
    return forward(bord, location, 9);
    case ten:
    return forward(bord, location, 10);
    case eleven:
    return forward(bord, location, 11);
    case twelve:
    return forward(bord, location, 12);
    case thirteen:
    return forward(bord, location, 13);
    case thirteen_out:
    if(outPawn(bord, p->idPlayer))
    return true;
    if(forward(bord, location, 13))
    return true;
    default:
    return false;
  }
}

int getHeuristic(Bord * bord, Player * player, enum Card * card){

}
