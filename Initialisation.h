/**
    name:   Initialisation.h
    type:   header file
    description: Window initialisation, image loaing, texture rendering.
        -
    @author: Arba
*/

#ifndef INITIALISATION_H_
#define INITIALISATION_H_

#include "Initialisation.h"

#include <stdio.h>
#include <string>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

using namespace std;


class WindowInit {
    public:
        WindowInit (int width, int height);
        ~WindowInit ();

        void LoadImage (std :: string path);
        void BlitImage ();

        void LoadTexture (std :: string path);
        void RenderTexture ();

        SDL_Rect stretchRect;

    protected:

        int windowHeight;
        int windowWidth;
        SDL_Window *window = NULL;
        SDL_Surface *loadedSurface = NULL;

        SDL_Surface *windowSurface = NULL;

        SDL_Renderer *renderer = NULL;
        SDL_Texture *texture = NULL;

    private:

        void Init ();

        void ImageInit ();
        void CloseImage ();

        void CloseTexture ();
        void TextureInit ();

        int setClose;
};

WindowInit :: WindowInit (int width, int height) {
    windowHeight = height;
    windowWidth = width;
    Init();
}

WindowInit :: ~WindowInit (){
    if (setClose == 0) CloseImage();
    else CloseTexture ();
}

void WindowInit :: Init () {
    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf ("Error in SDL_Init : %s", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow ("2DGame", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight, SDL_WINDOW_SHOWN );
        if (window == NULL) {
            printf("Error creating window : %s", SDL_GetError());
        }
        else {
            if (!IMG_Init (IMG_INIT_PNG) ){
                printf ("Error initialising PNG : %s", IMG_GetError());
            }
            else {
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = windowWidth;
                stretchRect.h = windowHeight;
            }
        }
    }
}

void WindowInit :: ImageInit () {
    windowSurface = SDL_GetWindowSurface (window);
}

void WindowInit :: TextureInit () {
    if (!SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY,  "2")) {
            printf("Error setting rendering quality : %s", SDL_GetError ());
    }
    else {
        renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            printf ("Error creating renderer : %s", SDL_GetError());
        }
        else {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
        }
    }
}

void WindowInit :: LoadImage (std :: string path) {
    ImageInit ();

    SDL_Surface *surface = NULL;

    surface = IMG_Load (path.c_str());
    if (surface == NULL) {
        printf ("Error loading image : %s", IMG_GetError());
    }
    else {
        loadedSurface = SDL_ConvertSurface (surface, windowSurface -> format, NULL);
        if (loadedSurface == NULL){
            printf ("Error converting surface : %s", SDL_GetError());
        }
        SDL_FreeSurface (surface);
    }
}

void WindowInit :: BlitImage () {
    SDL_BlitScaled (loadedSurface, NULL, windowSurface, &stretchRect);
    SDL_UpdateWindowSurface (window);
}




void WindowInit :: LoadTexture (std :: string path) {
    TextureInit ();
    loadedSurface = IMG_Load (path.c_str());
    if (loadedSurface == NULL) {
        printf ("Error loading image : %s", IMG_GetError());
    }
    else {
        texture = SDL_CreateTextureFromSurface (renderer, loadedSurface);
        if (texture == NULL) {
            printf ("Error creating texture : %s", SDL_GetError ());
        }
    }
    SDL_FreeSurface (loadedSurface);
}

void WindowInit :: RenderTexture () {
    SDL_RenderClear (renderer);
    SDL_RenderCopy (renderer, texture, NULL, NULL);
    SDL_RenderPresent (renderer);
}

void WindowInit :: CloseImage () {

    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;

    SDL_FreeSurface (windowSurface);
    windowSurface = NULL;
    SDL_DestroyWindow (window);
    window = NULL;

    IMG_Quit ();
    SDL_Quit ();
}

void WindowInit :: CloseTexture () {

    SDL_DestroyTexture (texture);
    texture = NULL;
    SDL_DestroyRenderer (renderer);
    renderer = NULL;

    SDL_DestroyWindow (window);
    window = NULL;

    IMG_Quit ();
    SDL_Quit ();
}


#endif // INITIALISATION_H_




















