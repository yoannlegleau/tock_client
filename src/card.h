/**
 * \file card.h
 * \brief Gestion des cartes
 * \author LE GLEAU Yoann
 * \date 28/01/2022
 * \version 1
 */

#ifndef TOCK_CLIENT_CARD_H
#define TOCK_CLIENT_CARD_H

/* ---------- Includes ---------- */

#include "linkedlist.h"
#include <stdbool.h>
#include <stdio.h>

/* ---------- Structure ---------- */

/**
 * \brief chaque enume corespon a une action distinct
 */
enum Card{one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, eighteen,
        out, swap, ThirteenOut, oneOut, sevenSplit };

/**
 * \brief Fonction de destruction ds cartes
 * \param card
 */
void destroyCard(enum Card ** card);

/* ---------- Getters ---------- */

/**
 * \brief retour le chemain ver l'asset associer a la carte
 * \param card
 * \return
 */
char* getAsset(const enum Card * card);

/**
 * \brief Retourne une liste des cartes qui compose la care en parameters
 * \param card carte a décomposer
 * \return Linkedlist liste de cartes
 * \details Une care composé est une carte qui possède plusieurs effets.
 */
Linkedlist * getCardCompose(const enum Card * card);

/* ---------- Testes ---------- */

/**
 * \brief Retourne vrais si la carte est une carte composé
 * \param card
 * \return bool
 * \details Une care composé est une carte qui possède plusieurs effets.
 */
bool isComposed(const enum Card * card);

/**
 * \brief Retourne vais si une carte composer est divisible
 * \param card
 * \return
 * \details Une carte composer est divisible quand le joueur n'est pas obliger de jouer toutes ces fonctionaliter pour pouvoir la jouer.
 * \example oneOut est divisible car le joueur doit soit avencer de 1 soit sortire un pion. au contraire pour seven split le joueur est obliger de jouer les 7 carte 1
 */
bool isComposedSplittable(const enum Card * card);

/* ---------- Utilities ---------- */

/**
 * \brief ajout des cartes dans la list pour cree un paket de carte coherent et prend en compte les règles sélectionner
 * \param cards liste de carte
 * \param gameRules liste des règles
 */
void makeDeck(Linkedlist * cards, Linkedlist * gameRules);

/**
 * \brief Distribuer les carters entre plusieurs joueurs
 * \param cards
 * \param players
 */
void distributeCards(Linkedlist *cards, Linkedlist *players);

/**
 * \brief ajout des cartes dans la list pour cree un paket de carte coherent et prend en compte les règles sélectionner
 * \param cards liste de carte
 * \param gameRules liste des règles
 */
void makeDeck(Linkedlist * cards, Linkedlist * gameRules);

/* ---------- Displays ---------- */

/**
 * \brief affiche le nom dew catres dans le terminal
 * \param card
 * \version 1
 */
void drawCard(const enum Card * card);

/**
 * \brief affiche une carte au centre du plateau
 * \param card
 */
void DrawCardMiddle(enum Card * card);



char * cardToString(const enum Card * card);

#endif //TOCK_CLIENT_CARD_H
