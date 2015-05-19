/**
    name:   Initialisation.cpp
    type:   source code
    description: Window initialisation, image loading, texture rendering.
        -
    @author: Arba
*/

#include "Initialisation.h"

Window :: Window () {
    windowProperties.h = 768;
    windowProperties.w = 1024;
    imageProperties.w = 1024;
    imageProperties.h = 768;

    Init();
}

Window :: Window (int width, int height) {
    windowProperties.h = height;
    windowProperties.w = width;
    imageProperties.w = width;
    imageProperties.h = height;

    Init();
}

Window :: ~Window (){
    if (setCloseImage == 1) CloseImage();
    if  (setCloseTexture == 1) CloseTexture ();


    SDL_DestroyWindow (window);
    window = NULL;

    IMG_Quit ();
    SDL_Quit ();
}

void Window :: Init () {
    imageProperties.x = 0;
    imageProperties.y = 0;

    windowProperties.x = 0;
    windowProperties.y = 0;

    if (SDL_Init (SDL_INIT_VIDEO) < 0) {
        printf ("Error in SDL_Init : %s", SDL_GetError());
    }
    else {
        window = SDL_CreateWindow ("2DGame", windowProperties.x, windowProperties.y, windowProperties.w, windowProperties.h, SDL_WINDOW_SHOWN );
        if (window == NULL) {
            printf("Error creating window : %s", SDL_GetError());
        }
        else {
            if (!IMG_Init (IMG_INIT_PNG) ){
                printf ("Error initialising PNG : %s", IMG_GetError());
            }
        }
    }
}

void Window :: ImageInit () {
    windowSurface = SDL_GetWindowSurface (window);
    setCloseImage = 1;
}

void Window :: TextureInit () {
    ScaleQuality scaleQuality;
    if (!SDL_SetHint (SDL_HINT_RENDER_SCALE_QUALITY,  scaleQuality.anisotropicFiltering)) {
            printf("Error setting rendering quality : %s", SDL_GetError ());
    }
    else {
        renderer = SDL_CreateRenderer (window, -1, SDL_RENDERER_ACCELERATED);
        if (renderer == NULL) {
            printf ("Error creating renderer : %s", SDL_GetError());
        }
        else {
            SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
            setCloseTexture = 1;
        }
    }
}

void Window :: LoadImage (string path) {
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

void Window :: BlitImage () {
    SDL_BlitScaled (loadedSurface, NULL, windowSurface, &imageProperties);
    SDL_UpdateWindowSurface (window);
}




void Window :: LoadTexture (string path) {
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

void Window :: RenderTexture () {
    SDL_RenderClear (renderer);
    SDL_RenderCopy (renderer, texture, NULL, NULL);
    SDL_RenderPresent (renderer);
}

void Window :: CloseImage () {

    SDL_FreeSurface(loadedSurface);
    loadedSurface = NULL;

    SDL_FreeSurface (windowSurface);
    windowSurface = NULL;
}

void Window :: CloseTexture () {

    SDL_DestroyTexture (texture);
    texture = NULL;
    SDL_DestroyRenderer (renderer);
    renderer = NULL;
}

