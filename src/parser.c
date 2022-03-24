//
// Created by adzerake on 23/03/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

#ifdef __unix__
    #include <regex.h>
#endif
#ifdef _WIN32

#endif


#define MAX_BUFFER_SIZE 100

char* parsByKey(const char *path, char* key) {
    FILE * file = fopen(path, "r" );
    if (file == NULL)
        exit(EXIT_FAILURE);

    char reg[MAX_BUFFER_SIZE] = "^<";
    strcat(reg,key);
    strcat(reg,">.*");


    char *line = malloc(MAX_BUFFER_SIZE);
    while(fgets(line,MAX_BUFFER_SIZE,file) != NULL){
        printf("%s",line);
    }

    fclose(file);

    return line;
}