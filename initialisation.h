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
        WindowInit ();
        WindowInit (int width, int height);
        ~WindowInit ();

        void LoadImage (string path);
        void BlitImage ();

        void LoadTexture (string path);
        void RenderTexture ();

        SDL_Rect imageProperties;
        SDL_Rect windowProperties;

    protected:

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

        int setCloseImage;
        int setCloseTexture;
};


#endif // INITIALISATION_H_




















