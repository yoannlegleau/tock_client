//
// Created by adzerake on 23/03/2022.
//

#ifndef TOCK_CLIENT_PARSER_H
#define TOCK_CLIENT_PARSER_H
#include <stdbool.h>
#include "linkedlist.h"

typedef struct KeyValue KeyValue;
struct KeyValue{
    char * key ;
    char * value ;
};

char * getByKey(Linkedlist *liste,char *key);

Linkedlist *  loadFromPath(const char *path);

KeyValue * keyValueFactory(char * key,char * value);

void drawKeyValue(KeyValue *keyValue);

#endif //TOCK_CLIENT_PARSER_H
