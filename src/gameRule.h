//
// Created by adzerake on 16/02/2022.
//

#ifndef TOCK_CLIENT_GAMERULE_H
#define TOCK_CLIENT_GAMERULE_H

/**
 * \brief ensembles des regles et varientes lier a une catre
 */
enum GameRule{minusFiveForOpponent};

void destroyGameRuleVoid(void * gameRule);

void destroyGameRule(enum GameRule ** gameRule);

#endif //TOCK_CLIENT_GAMERULE_H
