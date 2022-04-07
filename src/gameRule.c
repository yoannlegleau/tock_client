/**
 * \file gameRule.c
 * \brief Enumeration des variantes de règles de jeu
 * \author LE GLEAU Yoann
 * \date 16/02/2022
 * \version 1
 */


#include "gameRule.h"
#include "linkedlist.h"
#include "card.h"
#include <stdlib.h>

void destroyGameRuleVoid(void * gameRule){
  destroyCard(gameRule);
}

void destroyGameRule(enum GameRule ** gameRule){
  free(*gameRule);
}
