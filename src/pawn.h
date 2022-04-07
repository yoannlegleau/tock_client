/**
 * \file pawn.h
 * \brief Structure des pions pour le server
 * \author LE GLEAU Yoann
 * \date 11/03/2022
 * \version 1
 */


#ifndef TOCK_CLIENT_PAWN_H
#define TOCK_CLIENT_PAWN_H

#include <stdbool.h>

typedef struct Pawn Pawn;
struct Pawn {
    int IDplayer;
    int location; //index du tableau du plateau (principalement en prevision de l'envoi de données au server)
    bool invincibility;
};

#endif //TOCK_CLIENT_PAWN_H
