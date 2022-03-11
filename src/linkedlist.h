#include <stdbool.h>

/**
 * \file Linkedlist.h
 * \brief liste chainer generique
 * \author LE GLEAU yoann
 * \date 25/01/2022
 * \version 1
 * \details Baser sur les specification suivantes https://docs.oracle.com/javase/7/docs/api/java/util/LinkedList.html
 */

typedef struct Linkedlist Linkedlist;

/**
 * \brief (ruteur) Cree une nouvelle list chainer
 * \param typeSyze taille du type utiliser
 * \return la liste
 * \example Linkedlist list = linkedListFactory(sizeof(int)
 */
Linkedlist * linkedListFactory( int typeSize);

/**
 * \brief Renvoie la taille des element contenue.
 * \param l Linkedlist conserner
 * \return int
 */
int size( Linkedlist * l);

/**
 * \brief Renvoie le nombre d'éléments de la liste l.
 * \param l Linkedlist conserner
 * \return nombre d'éléments ou 0 si la liste est vide
 */
int length( Linkedlist *l);

/**
 * \brief Renvoie true si cette liste ne contient aucun élément.
 * \param l liste cible
 * \return true si cette liste ne contient aucun élément
 * \details Cette implémentation renvoie length() == 0.
 */
bool isEmpty(Linkedlist *l);

/**
 * \brief Renvoie le nombre d'occurrence de l'objet dans la liste
 * \param l Linkedlist
 * \param o pointeure de comparaison
 * \return int corespondent
 */
int contains( Linkedlist * l, void * o);

/**
 * \brief Ajoute l'objet O au debut de la liste
 * \param l
 * \param o
 */
void addFirst(Linkedlist * l, void * o);

/**
 * \brief Ajoute l'objet O a la fin de la liste
 * \param l
 * \param o
 */
void addLast(Linkedlist *l,  void * o);

/**
 * \brief Renvoie une reel copie de la liste
 * \param l liste copier
 * \return copie de la liste
 */
Linkedlist * clone( Linkedlist * l);

/**
 * \brief Suprime tout les objects de la liste
 * \param l Linkedlist
 */
void clear(Linkedlist * l);

/**
 * \brief Suprime de la liste un object
 * \param l Linkedlist
 * \param i (index) position de l'object
 */
void removeElem(Linkedlist * l, int i);

/**
 * \brief Suprime le premier objet de la liste
 * \param l Linkedlist
 */
void removeFirst(Linkedlist *l);

/**
 * \brief Suprime la lise et libert l'espace memoire
 * \param l Linkedlist
 */
void destroy(Linkedlist * l);

/**
 * \brief Renvoie l'élément à la position spécifiée dans cette liste.
 * \param l
 * \param index
 * \return objet ou NULL si hor liste
 */
void * get( Linkedlist * l, int index );

/**
 * \brief Renvoie le premiere élément dans cette liste.
 * \param l
 * \return
 */
void * getFirst( Linkedlist * l);

/**
 * \brief Renvoie le dernière élément dans cette liste.
 * \param l
 * \return
 */
void * getLast( Linkedlist * l);

/**
 * \brief Renvoie le premiere élément dans cette liste et le supprime.
 * \param l
 * \return
 */
void * pollFirst(Linkedlist * l);

/**
 * \brief afficher le contenu de la liste
 * \param l liter a afficher
 * \param draw fonction draw'affichage de l'object
 */
void drawListe(Linkedlist *l,void (*draw)(void *));

void foreach(Linkedlist * l, void (*pVoid)(void *));


/*
 IDER DE FONCTION A IMPLEMENTER
pollFirst()
remove()
remove(int index)
remove(Object o)
removeFirst()
set(int index, E element)
toArray()
*/