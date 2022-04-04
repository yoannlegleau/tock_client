//
// Created by adzer on 1/04/2022.
//

#ifndef TOCK_CLIENT_DRAWABLE_H
#define TOCK_CLIENT_DRAWABLE_H

/**
 * \brief Ajoute un objet a la liste des objets à afficher
 * \param object a afficher
 * \param render Fonction de rendu
 */
void addDrawable(void* object, void (*render)(void *));

/**
 * \brief Calcule et affiche l'intégralités des objet
 */
void RenderAllDrawable();

void setVisibility(void* object, bool visibility);

/**
 * \brief Defini l'objet comme modifier pour une mise a jour du rendut ulterieurs;
 * \param object
 */
void modify(void* object);


#endif //TOCK_CLIENT_DRAWABLE_H
