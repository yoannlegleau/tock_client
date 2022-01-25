/**
 * \file Linkedlist.c
 * \author LE GLEAU yoann
 * \date 25/01/2022
 * \image html assets/img/linkedListFactory.png
 */


#include <stdio.h>
#include <malloc.h>
#include "linkedlist.h"
#include <stdbool.h>

typedef struct Elem Elem;
struct Elem {
    void * object;
    Elem * next;
};

typedef struct Linkedlist Linkedlist;
struct Linkedlist {
    Elem * last;
    int size;
};

/**
 * \brief Cree un Element de list en initialisent l'espace memoire. par defaux l'element "boucle" sur lui meme
 * \param l
 * \param o
 * \return
 */
Elem * elemFactory(Linkedlist * l , void * o){
    Elem * elem = malloc(size(l));
    elem->object=o;
    elem->next= elem;
    return elem;
}

Linkedlist * linkedListFactory(int typeSize){
    Linkedlist * list = malloc(sizeof(Linkedlist));
    list->size = typeSize;
    list->last = NULL;
    return list;
}

int size(Linkedlist *l) {
    return l->size;
}

int contains(Linkedlist *l, void *o) {
    //TODO int contains(Linkedlist *l, void *o)
    return 0;
}

void addFirst(Linkedlist *l, void *o) {
    //le pointer de depar est la fin si la liste est vide
    //TOTEST
    if(l->last == NULL)
        addLast(l,o);
    else{
        Elem * elem = elemFactory(l,o);
        elem->next = l->last->next;
        l->last->next = elem;
    }
}

void addLast(Linkedlist *l, void *o) {
    //TOTEST
    Elem * elem = elemFactory(l,o);
    if(l->last = NULL)
        l->last = elem;
    else{
        elem->next = l->last->next;
        l->last->next = elem;
        l->last = elem;
    }
    l->size++;
}

Linkedlist *clone(Linkedlist *l) {
    //TODO Linkedlist *clone(Linkedlist *l)
    return NULL;
}

void clear(Linkedlist *l) {
    //TODO void clear(Linkedlist *l)
}

void destroy(Linkedlist *l) {
    //TODO void destroy(Linkedlist *l)
}

void * get(Linkedlist *l, int index) {
    //TODO void * get(Linkedlist *l, int index)
    return NULL;
}

void *getFirst(Linkedlist *l) {
    //TODO void *getFirst(Linkedlist *l)
    return NULL;
}

void *getLast(Linkedlist *l) {
    //TODO void *getLast(Linkedlist *l)
    return NULL;
}

