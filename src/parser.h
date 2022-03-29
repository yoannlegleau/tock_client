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

void destroyKeyValueVoid(void * keyValue);

void destroyKeyValue(KeyValue ** keyValue);

void setKeyValue(char *newKey,const char *path);

char * getByKey(Linkedlist *liste,char *key);

Linkedlist *  loadFromPath(const char *path);

KeyValue * keyValueFactory(char * key,char * value);

void drawKeyValue(KeyValue *keyValue);

bool toBool(char *s);

#endif //TOCK_CLIENT_PARSER_H
