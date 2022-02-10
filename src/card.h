/**
 * \file card.h
 * \brief gestion des cartes
 * \author JARRIER allan
 * \date 28/01/2022
 * \version 1
 */

update #ifndef TOCK_CLIENT_CARD_H
#define TOCK_CLIENT_CARD_H

#include "linkedlist.h"
#include <stdbool.h>
#include <stdio.h>

//Linkedlist * l = linkedListFactory(sizeof(enum Card));

/**
 * \brief chaque enume corespon a une action distinct
 * TODO se metre dacord pour les nom
 */
enum Card{empty,
        one, two, three, four, five, six, seven, eight, nine, ten, eleven, twelve, thirteen, eighteen,
        swap, eleven_out };

/**
 * \brief affiche le nom dew catres dans le terminal
 * \param card
 * \version 1
 */
void drawCard(const enum Card * card);

#endif //TOCK_CLIENT_CARD_H

