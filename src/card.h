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
        out, swap, ThirteenOut, oneOut };

/**
 * \brief Retourne vrais si la carte est une carte composé
 * \param card
 * \return bool
 * \details Une care composé est une carte qui possède plusieurs effets.
 */
bool isComposed(const enum Card * card);

/**
 * \brief Retourne une liste des cartes qui compose la care en parameters
 * \param card carte a décomposer
 * \return Linkedlist liste de cartes
 * \details Une care composé est une carte qui possède plusieurs effets.
 */
Linkedlist * getCardCompose(const enum Card * card);

/**
 * \brief affiche le nom dew catres dans le terminal
 * \param card
 * \version 1
 */
void drawCard(const enum Card * card);

/**
 * \brief retour le chemain ver l'asset associer a la carte
 * \param card
 * \return
 */
char* getAsset(const enum Card * card);

/**
 * \brief ajout des cartes dans la list pour cree un paket de carte coherent et prend en compte les règles sélectionner
 * \param cards liste de carte
 * \param gameRules liste des règles
 */
void makeDeck(Linkedlist * cards, Linkedlist * gameRules);

void distributeCards(Linkedlist *cards, Linkedlist *players);

void destroyCard(enum Card ** card);

char * cardToString(const enum Card * card);

#endif //TOCK_CLIENT_CARD_H
