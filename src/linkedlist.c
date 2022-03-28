/**
 * \file Linkedlist.c
 * \brief liste chainer generique
 * \author LE GLEAU yoann
 * \date 25/01/2022
 * \version 1
 * \image html assets/img/linkedListFactory.png
 */



#include <malloc.h>
#include <stdlib.h>
#include "linkedlist.h"


typedef struct Elem Elem;
struct Elem {
    void * object;
    Elem * next;
};

typedef struct Linkedlist Linkedlist;
struct Linkedlist {
    Elem * last;
    int length;
};

Elem * getElem( Linkedlist *l, int index);

/**
 * \brief Cree un Element de list en initialisent l'espace memoire. par defaux l'element "boucle" sur lui meme
 * \param l
 * \param o
 * \return
 */
Elem * elemFactory( Linkedlist * l, void * o){
    Elem * elem = malloc(sizeof(Elem));
    elem->object=o;
    elem->next= elem;

    return elem;
}

Linkedlist * linkedListFactory(){
    Linkedlist * list = malloc(sizeof(Linkedlist));
    list->last = NULL;
    list->length = 0;
    return list;
}


int length( Linkedlist *l) {
    return l->length;
}

bool isEmpty(Linkedlist *l) {
    return (length(l) == 0);
}

int contains( Linkedlist *l, void *o) {
    //TODO int contains(Linkedlist *l, void *o)
    return 0;
}

void addFirst(Linkedlist *l, void *o) {
    //le pointer de depar est la fin si la liste est vide
    if(l->last == NULL)
        addLast(l,o);
    else{
        Elem * elem = elemFactory(l,o);
        elem->next = l->last->next;
        l->last->next = elem;
        l->length++;
    }
}

void addLast(Linkedlist *l, void *o) {
    Elem * elem = elemFactory(l,o);
    if(l->last == NULL)
        l->last = elem;
    else{
        elem->next = l->last->next;
        l->last->next = elem;
        l->last = elem;
    }
    l->length++;
}

Linkedlist *clone( Linkedlist *l) {
    //TODO Linkedlist *clone(Linkedlist *l)
    return NULL;
}

void clear(Linkedlist *l) {
    while (l->length>0){
        removeFirst(l);
    }
}

void removeElem(Linkedlist *l, int i) {
    Elem * elem = getElem(l, i);
    if(length(l) == 1)
        l->last = NULL;
    else
        getElem(l, i - 1)->next = getElem(l, i + 1);
    l->length--;

    //FIXME fuite de memoire
    //free(elem);
}

void removeFirst(Linkedlist *l) {
    removeElem(l,0);
}


void destroy(Linkedlist *l) {
    while (!isEmpty(l))
        removeFirst(l);
    free(l);
}

Elem * getElem( Linkedlist *l, int index) {
    if(isEmpty(l))
        return NULL;
    int len = length(l);
    if(index>0)
        index = index % len;
    else{
        index = len-(abs(index)%len);
    }
    Elem * elem = l->last->next;
    for (int i = 0; i < index; i++) {
        elem = elem->next;
    }
    return elem;
}

void * get( Linkedlist *l, int index) {
    if(isEmpty(l))
        return NULL;
    else
        return getElem(l,index)->object;
}

void *getFirst( Linkedlist *l) {
    if(isEmpty(l))
        return NULL;
    return l->last->next->object;
}

void *getLast( Linkedlist *l) {
    return l->last->object;
}

void *pollFirst(Linkedlist *l) {
    if(isEmpty(l))
        return NULL;
    void * result = getFirst(l);
    removeFirst(l);
    return result;
}

void * pollRandom(Linkedlist * l) {
    if (isEmpty(l))
        return NULL;
    int index = rand() % l->length;
    void *result = get(l, index);
    removeElem(l, index);
    return result;
}

void foreach(Linkedlist *l, void (*pVoid)(void *)) {
    if(isEmpty(l))
        return;
    Elem *iterator = l->last->next;
    for(int i = 0; i < l->length; ++i) {
        pVoid(iterator->object);
        iterator = iterator->next;
    }
}






