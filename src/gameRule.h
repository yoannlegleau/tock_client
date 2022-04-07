/**
 * \file gameRule.h
 * \brief Enumeration des variantes de règles de jeu
 * \author LE GLEAU Yoann
 * \date 16/02/2022
 * \version 1
 */


#ifndef TOCK_CLIENT_GAMERULE_H
#define TOCK_CLIENT_GAMERULE_H

/* ---------- Structure ---------- */

/**
 * \brief Ensembles des règles et variantes lier a une cartes
 */
enum GameRule{FiveForOpponent};

/* ---------- Constructor ---------- */

/**
 * \brief Liber l'espace memoire allouer
 * \param gameRule
 */
void destroyGameRuleVoid(void * gameRule);

void destroyGameRule(enum GameRule ** gameRule);

#endif //TOCK_CLIENT_GAMERULE_H
