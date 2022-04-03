//
// Created by adzer on 03/04/2022.
//

#include <stdlib.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Drawable.h"
#include "../linkedlist.h"
#include "mainSDL.h"

Linkedlist * drawables = NULL;

typedef struct Drawable Drawable;
struct Drawable {
    void * object;
    void (*render)(void *);
    bool update;
};

/**
 * \brief Test si la liste des drawables a été initialiser
 * \return
 */
bool isInitDrawable(){
    return drawables != NULL;
}

/**
 * \brief initialise la list des drawables si se n'est pas dejas fais (singleton)
 */
void initDrawable(){
    if(!isInitDrawable())
        drawables = linkedListFactory(free);
}

Drawable * drawableFactory(void * o,void (*r)(void *)){
Drawable * drawable = malloc(sizeof(Drawable));
drawable->object = o;
drawable->render = r;
drawable->update = false;
return drawable;
}

void addDrawable(void* object, void (*render)(void *)){
    initDrawable();
    addLast(drawables, drawableFactory(object,render));
}

void RenderAllDrawable(){
    Drawable * index = NULL;
    initDrawable();
    if(!isEmpty(drawables))
        for (int i = 0; i < length(drawables) ; i++) {
            index = get(drawables,i);
            if (!index->update) {
                index->render(index->object);
                //TODO faire le rendu dynamiquement
                //index->update = true;
            }
        }
    renderBackground();
    SDL_RenderPresent(SDLgetRender());
    SDL_RenderClear(SDLgetRender());

#ifdef __unix__
    sleep(100);
#endif
#ifdef _WIN32
    //Sleep(2000);
#endif
}

void setVisibility(void* object, bool visibility){
    //TODO setVisibility(void* object, bool visibility)
}

void modify(void* object){
    //TODO modify(void* object)
}
