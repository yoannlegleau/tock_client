/**
 * \file Linkedlist.c
 * \brief liste chainer generique
 * \author LE GLEAU yoann
 * \date 25/01/2022
 * \version 1
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
Elem * elemFactory(const Linkedlist * l, const void * o){
    Elem * elem = malloc(size(l));
    elem->object=o;
    elem->next= elem;
    return elem;
}

Linkedlist * linkedListFactory(const int typeSize){
    Linkedlist * list = malloc(sizeof(Linkedlist));
    list->size = typeSize;
    list->last = NULL;
    return list;
}

int size(const Linkedlist *l) {
    return l->size;
}

int contains(const Linkedlist *l,const void *o) {
    //TODO int contains(Linkedlist *l, void *o)
    return 0;
}

void addFirst(Linkedlist *l,const void *o) {
    //le pointer de depar est la fin si la liste est vide
    if(l->last == NULL)
        addLast(l,o);
    else{
        Elem * elem = elemFactory(l,o);
        elem->next = l->last->next;
        l->last->next = elem;
    }
}

void addLast(Linkedlist *l, const void *o) {
    Elem * elem = elemFactory(l,o);
    if(l->last == NULL)
        l->last = elem;
    else{
        elem->next = l->last->next;
        l->last->next = elem;
        l->last = elem;
    }
    l->size++;
}

Linkedlist *clone(const Linkedlist *l) {
    //TODO Linkedlist *clone(Linkedlist *l)
    return NULL;
}

void clear(const Linkedlist *l) {
    //TODO void clear(Linkedlist *l)
}

void destroy(Linkedlist *l) {
    //TODO void destroy(Linkedlist *l)
}

void * get(const Linkedlist *l,const int index) {
    //TODO void * get(Linkedlist *l, int index)
    return NULL;
}

void *getFirst(const Linkedlist *l) {
    return l->last->next->object;
}

void *getLast(const Linkedlist *l) {
    return l->last->object;
}

void drawListe(const Linkedlist *l,const void (*draw)(void * o)){
    Elem *iterator = l->last->next;
    do {
        draw(iterator->object);
        iterator = iterator->next;
    }while (iterator != l->last->next);
}