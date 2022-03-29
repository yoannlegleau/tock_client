//
// Created by adzerake on 16/02/2022.
//

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
