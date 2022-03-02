/**
 * \file card.c
 * \brief gestion des cartes
 * \author JARRIER allan
 * \date 28/01/2022
 * \version 1
 */

#include "card.h"
#include <stdlib.h>


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
            //TODO ajouter les autre cartes
    }
}

void makeDeck(Linkedlist *cards, Linkedlist *gameRules) {
    clear(cards);
    enum Card * card = malloc(sizeof(enum Card));
    for (int i = 0; i < 4; ++i) {
        for (enum Card c = one ; c <= thirteen; ++c) {
            card = malloc(sizeof(enum Card));
            *card = c;
            addFirst(cards,card);
        }
    }
}


