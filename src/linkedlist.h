/**
 * \file Linkedlist.h
 * \author LE GLEAU yoann
 * \date 25/01/2022
 */

typedef struct Linkedlist Linkedlist;

/**
 * \brief (Construteur) Cree une nouvelle list chainer
 * \param typeSyze taille du type utiliser
 * \return la liste
 * \example Linkedlist list = linkedListFactory(sizeof(int)
 */
Linkedlist * linkedListFactory(int typeSize);

/**
 * \brief Renvoie le nombre d'éléments de la liste l.
 * \param l Linkedlist conserner
 * \return nombre d'éléments ou 0 si la liste est vide
 */
int size(Linkedlist * l);

/**
 * \brief Renvoie le nombre d'occurrence de l'objet dans la liste
 * \param l Linkedlist
 * \param o pointeure de comparaison
 * \return int corespondent
 */
int contains(Linkedlist * l, void * o);

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
void addLast(Linkedlist * l, void * o);

/**
 * \brief Renvoie une reel copie de la liste
 * \param l liste copier
 * \return copie de la liste
 */
Linkedlist * clone(Linkedlist * l);

/**
 * \brief Suprime tout les objects de la liste
 * \param l Linkedlist
 */
void clear(Linkedlist * l);

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
void * get(Linkedlist * l, int index );

/**
 * \brief Renvoie le premiere élément dans cette liste.
 * \param l
 * \return
 */
void * getFirst(Linkedlist * l);

/**
 * \brief Renvoie le dernière élément dans cette liste.
 * \param l
 * \return
 */
void * getLast(Linkedlist * l);

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