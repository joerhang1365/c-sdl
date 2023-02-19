#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

SDL_Texture *loadTexture(char *filePath, SDL_Renderer *renderTarget);

#endif
