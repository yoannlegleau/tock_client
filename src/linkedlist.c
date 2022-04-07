/**
 * \file Linkedlist.c
 * \brief liste chainer generique
 * \author LE GLEAU yoann
 * \date 25/01/2022
 * \version 1
 * \image html assets/img/linkedListFactory.png
 */


/* ---------- Includes ---------- */

#include <malloc.h>
#include <stdlib.h>
#include "linkedlist.h"
#include <time.h>

/* ---------- Structure ---------- */

/**
 * \brief sous-structure de la liste comportent les object
 */
typedef struct Elem Elem;
struct Elem {
    /** \brief Pointeur d'objet a stoker dans la liste */
    void * object;

    /** \brief Prochene element de la liste */
    Elem * next;
};

struct Linkedlist {

    /** \brief fonction de destruction des objets de la liste */
    void (*destroy)(void * function);

    /** \brief Dernier element de la liste \note Le premier est donc le suivent du dernier*/
    Elem * last;

    /** \brief nomble d'objet contenu dans la liste */
    int length;
};


/* ---------- Constructor ---------- */

Linkedlist * linkedListFactory(void (*funcDest)(void * e)){
    Linkedlist * list = malloc(sizeof(Linkedlist));
    list->last = NULL;
    list->length = 0;
    list->destroy = funcDest;
    return list;
}

Linkedlist *LinkedlistClone(Linkedlist *l) {
    //Linkedlist * clone = linkedListFactory(l->destroy);
    //TODO Linkedlist *LinkedlistClone(Linkedlist *l)
    return NULL;
}

Linkedlist *clone( Linkedlist *l) {
    //TODO Linkedlist *clone(Linkedlist *l)
    return NULL;
}

void destroyLinkedList(Linkedlist **l) {
    while (!isEmpty(*l))
        removeFirst(*l);
    free(*l);
    *l = NULL;
}

/**
 * \brief Cree un Element de list en initialisent l'espace memoire. par defaux l'element "boucle" sur lui meme
 * \param o
 * \return
 */
Elem * elemFactory(void * o){
    Elem * elem = malloc(sizeof(Elem));
    elem->object=o;
    elem->next= elem;
    return elem;
}

/**
 * \brief liber la memoir allouer a un element de la list
 * \param e element a detruire
 * \param destroy fonction de destruction des objets de la liste
 */
void destroyElem(Elem **e, void (*destroy)(void *)) {
    destroy(&((*e)->object));
    //TODO free(*e);
    *e = NULL;
}


/* ---------- Getters ---------- */

int length( Linkedlist *l) {
    return l->length;
}

/**
 * \brief Renvoie l'élément à la position spécifiée dans cette liste.
 * \param l
 * \param index
 * \return objet ou NULL si hor liste
 */
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


/* ---------- Testes  ---------- */

bool isEmpty(Linkedlist *l) {
    return (length(l) == 0);
}

int contains( Linkedlist *l, void *o) {
    //TODO int contains(Linkedlist *l, void *o)
    return 0;
}


/* ---------- Utilities ---------- */

void addFirst(Linkedlist *l, void *o) {
    //le pointer de depar est la fin si la liste est vide
    if(l->last == NULL)
        addLast(l,o);
    else{
        Elem * elem = elemFactory(o);
        elem->next = l->last->next;
        l->last->next = elem;
        l->length++;
    }
}

void addLast(Linkedlist *l, void *o) {
    Elem * elem = elemFactory(o);
    if(l->last == NULL)
        l->last = elem;
    else{
        elem->next = l->last->next;
        l->last->next = elem;
        l->last = elem;
    }
    l->length++;
}

void clear(Linkedlist *l) {
    while (l->length>0){
        removeFirst(l);
    }
}

void removeElem(Linkedlist *l, int i) {
    Elem * elem = getElem(l, i);
    if (length(l) == 1)
        l->last = NULL;
    else {
        Elem *prev = getElem(l, i - 1);
        prev->next = getElem(l, i + 1);
        if(i+1 == l->length)
            l->last = prev;
    }
    l->length--;
    destroyElem(&elem, l->destroy);
}

void removeFirst(Linkedlist *l) {
    removeElem(l,0);
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
    srand ( time(NULL) );
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
