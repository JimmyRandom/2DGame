#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include<SDL2/SDL_image.h>

class WindowInit {
    public:
        WindowInit (int height, int width);
        ~WindowInit ();
        void LoadImage (std :: string path);
        void Close ();
        void BlitImage ();
        SDL_Rect stretchRect;

    protected:
        int windowHeight;
        int windowWidth;
        SDL_Window *window = NULL;
        SDL_Surface *windowSurface = NULL;
        SDL_Surface *loadedSurface = NULL;
        void Init ();


};

WindowInit :: WindowInit (int height, int width) {
    windowHeight = height;
    windowWidth = width;
    Init();
}

WindowInit :: ~WindowInit (){
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
                windowSurface = SDL_GetWindowSurface (window);
                stretchRect.x = 0;
                stretchRect.y = 0;
                stretchRect.w = windowWidth;
                stretchRect.h = windowHeight;
            }
        }
    }
}

void WindowInit :: LoadImage (std :: string path) {
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

void WindowInit :: Close () {
    SDL_FreeSurface (windowSurface);
    SDL_DestroyWindow (window);
    IMG_Quit();
    SDL_Quit();
}
























