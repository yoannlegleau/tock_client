/**
 * \file card.c
 * \brief gestion des cartes
 * \author JARRIER allan
 * \date 28/01/2022
 * \version 1
 */

#include "card.h"
#include "Player/player.h"
#include <stdlib.h>

bool isComposed(const enum Card * card){
    return (*card == ThirteenOut ||
            *card == oneOut);
}

Linkedlist * getCardCompose(const enum Card * card){
    if (!isComposed(card))
        return NULL;
    Linkedlist *compose = linkedListFactory(destroyCard);
    enum Card * composeCard ;
    switch (*card) {
        case ThirteenOut:
            composeCard = malloc(sizeof(enum Card));
            *composeCard = thirteen;
            addFirst(compose,composeCard);
            composeCard = malloc(sizeof(enum Card));
            *composeCard = out;
            addFirst(compose,composeCard);
            break;
        case oneOut:
            composeCard = malloc(sizeof(enum Card));
            *composeCard = one;
            addFirst(compose,composeCard);
            composeCard = malloc(sizeof(enum Card));
            *composeCard = out;
            addFirst(compose,composeCard);
            break;
    }
    return compose;
}

void drawCard(const enum Card * card){
    if(card == NULL)
        return;
    switch (*card) {
        case one:
            printf("One\n");
            break;
        case two:
            printf("tow\n");
            break;
        case three:
            printf("three\n");
            break;
        case four:
            printf("four\n");
            break;
        case five:
            printf("five\n");
            break;
        case six:
            printf("six\n");
            break;
        case seven:
            printf("seven\n");
            break;
        case eight:
            printf("eight\n");
            break;
        case nine:
            printf("nine\n");
            break;
        case ten:
            printf("ten\n");
            break;
        case eleven:
            printf("eleven\n");
            break;
        case twelve:
            printf("twelve\n");
            break;
        case thirteen:
            printf("thirteen\n");
            break;
        case ThirteenOut:
            printf("ThirteenOut\n");
            break;
        case oneOut:
            printf("OneOut\n");
            break;
        case out:
            printf("Out\n");
            break;
            //TODO ajouter les autre cartes
    }
}



void destroyCard(enum Card ** card){
  //TODO destroyCard
  //free(*card);
  *card = NULL;
}

char* getAsset(const enum Card * card){
    if (card == NULL)
        return "assets/Design_Cartes/Derriere_Carte.png";
    switch (*card) {
        case one:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case two:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case three:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case four:
            return "assets/Design_Cartes/Carte4_1.png";
        case five:
            return "assets/Design_Cartes/Carte5_2.png";
        case six:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case seven:
            return "assets/Design_Cartes/Carte7_4.png";
        case eight:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case nine:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case ten:
            return "assets/Design_Cartes/Carte10_1.png";
        case eleven:
            return "assets/Design_Cartes/CarteV_1.png";
        case twelve:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case thirteen:
            return "assets/Design_Cartes/CarteValeur_3.png";
        case ThirteenOut:
            return "assets/Design_Cartes/CarteSortirPions_2.png";
        case oneOut:
            return "assets/Design_Cartes/CarteSortirPions_2.png";
            //TODO ajouter les autre cartesd
        default:
            return "assets/Design_Cartes/Derriere_Carte.png";
    }
}


void makeDeck(Linkedlist *cards, Linkedlist *gameRules) {
    clear(cards);
    enum Card * card ;
    for (int i = 0; i < 4; ++i) {
        for (enum Card c = one ; c <= thirteen; ++c) {

            card = malloc(sizeof(enum Card));
            *card = c;
            if(*card == thirteen)
                 *card = ThirteenOut;
            if(*card == one)
                *card = oneOut;

            addFirst(cards,card);
        }
    }

}

void distributeCards(Linkedlist *cards, Linkedlist *players) {
    int nbPlayer = length(players);
    int nbDistributCards;
    if((length(cards)/length(players))%4 != 0) nbDistributCards = 5;
    else nbDistributCards = 4;
    Player * p;

    for (int i = 0; i < nbPlayer; i++) {
        p = get(players,i);
        for (int j = 0; j < nbDistributCards; j++) {
            addLast(p->cards, pollRandom(cards));
        }
    }
}

char * cardToString(const enum Card * card){
    if(card == NULL)
        return NULL;
    switch (*card) {
        case one:
            return "One";
        case two:
            return "tow";
        case three:
            return "three";
        case four:
            return "four";
        case five:
            return "five";
        case six:
            return "six";
        case seven:
            return "seven";
        case eight:
            return "eight";
        case nine:
            return "nine";
        case ten:
            return "ten";
        case eleven:
            return "eleven";
        case twelve:
            return "twelve";
        case thirteen:
            return "thirteen";
        case ThirteenOut:
            return "ThirteenOut";
        case oneOut:
            return "OneOut";
        case out:
            return "Out";

            //TODO ajouter les autre cartes
    }
}
