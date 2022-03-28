//
// Created by adzerake on 23/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "linkedlist.h"

#define MAX_BUFFER_SIZE 100
#define REG_START '<'
#define REG_END '>'

char * getByKey(Linkedlist *liste,char *key){
    int i;
    KeyValue * kv;
    char * result = NULL;
    if(!isEmpty(liste))
        for(i=0;i<length(liste);i++){
            kv = (KeyValue *)get(liste,i);
            if(strcmp(kv->key,key)==0){
                result = kv->value;
            }
        }
    return result;
}


Linkedlist * loadFromPath(const char *path){
    FILE * file = fopen(path, "r");
    if ( file == NULL ) {
        printf( "Cannot open file %s\n", path );
        exit( 0 );
    }

    Linkedlist * keyValues = linkedListFactory();
    if (file == NULL)
        exit(EXIT_FAILURE);
    char * c = "";
    while(!feof(file)){
        fscanf(file,"%c",c);
        if(*c == REG_START){
            KeyValue * keyValue = keyValueFactory("\0","\0");
            fscanf(file,"%c",c);
            while(*c != REG_END){
                strcat(keyValue->key,c);
                fscanf(file,"%c",c);
            }
            fscanf(file,"%c",c); // passer le caractaire REG_END
            while(!feof(file) && *c != '\n'){
                strcat(keyValue->value,c);
                fscanf(file,"%c",c);
            }
            addLast(keyValues,keyValue);
        }
    }
    fclose(file);
    return keyValues;
}

KeyValue * keyValueFactory(char * key,char * value){
    KeyValue * kv = malloc(sizeof(KeyValue));
    kv->key = (char *) malloc(MAX_BUFFER_SIZE);
    strcpy(kv->key,key);
    kv->value = (char *) malloc(MAX_BUFFER_SIZE);
    strcpy(kv->value,key);
    return kv;
}
void drawKeyValue(KeyValue *keyValue){
    printf("key: %s\n",keyValue->key);
    printf("value: %s\n",keyValue->value);
}

bool toBool(char *s){
    return (strcmp(s,"true") == 0);
}
