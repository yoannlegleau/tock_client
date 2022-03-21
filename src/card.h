/**
 * \file card.h
 * \brief gestion des cartes
 * \author JARRIER allan
 * \date 28/01/2022
 * \version 1
 */

#ifndef TOCK_CLIENT_CARD_H
#define TOCK_CLIENT_CARD_H

#include "linkedlist.h"
#include <stdbool.h>
#include <stdio.h>

//Linkedlist * l = linkedListFactory(sizeof(enum Card));

/**
 * \brief chaque enume corespon a une action distinct
 */
enum Card{one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, eighteen,
        swap, thirteen_out };

/**
 * \brief affiche le nom dew catres dans le terminal
 * \param card
 * \version 1
 */
void drawCard(const enum Card * card);

/**
 * \brief ajout des cartes dans la list pour cree un paket de carte coherent et prend en compte les règles sélectionner
 * \param cards liste de carte
 * \param gameRules liste des règles
 */
void makeDeck(Linkedlist * cards, Linkedlist * gameRules);

void distributeCards(Linkedlist *cards, Linkedlist *players);

#endif //TOCK_CLIENT_CARD_H



