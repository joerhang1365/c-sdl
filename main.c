#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include "surface.h"
#include "texture.h"

bool initialize();
void events(SDL_Event *event);
void update();
void render();
void clean();

SDL_Window *window = NULL;
SDL_Texture *image = NULL;
SDL_Renderer *renderTarget = NULL;
SDL_Event event;
SDL_Rect drawingRect;

const unsigned int WINDOW_WIDTH = 640;
const unsigned int WINDOW_HEIGHT = 480;

float frameTime = 0;
int previousTime = 0;
int currentTime = 0;
float deltaTime = 0;

bool running = true;

int main(int argc, char *argv[])
{
   if(initialize() == false)
   {
      return -1;
   }

   while(running)
   {
      while(SDL_PollEvent(&event) != 0)
      {
         events(&event);
      }
      update();
      render();
   }
   clean();

   return 0;
}

bool initialize()
{
   // window
   if(SDL_Init(SDL_INIT_VIDEO) > 0)
   {
      printf("video initialization error\n");
      return false;
   }
   else
   {
      window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
      if(window == NULL)
      {
         printf("window creation error\n");
         return false;
      }
   }

   // renderer
   renderTarget = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

   // image flags
   int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
   if(!(IMG_Init(imageFlags) & imageFlags))
   {
      printf("error unknown image type\n");
   }

   // textures
   image = loadTexture("src/images/background.jpg", renderTarget);

   // rect
   drawingRect.x = drawingRect.y = 0;
   drawingRect.w = 640;
   drawingRect.h = 480;

   return true;
}

void events(SDL_Event *event)
{
   if(event->type == SDL_QUIT)
   {
      running = false;
   }
   else if(event->type == SDL_KEYDOWN)
   {
      switch(event->key.keysym.sym)
      {
         case SDLK_1:
            printf("pressed key 1\n"); break;
         case SDLK_2:
            printf("pressed key 2\n"); break;
         case SDLK_3:
            printf("pressed key 3\n"); break;
      }
   }
   else if(event->type == SDL_MOUSEBUTTONDOWN)
   {
      if(event->button.button == SDL_BUTTON_LEFT)
      {
         printf("pressed left mouse\n");
      }
      else if(event->button.button == SDL_BUTTON_RIGHT)
      {
         printf("pressed right mouse\n");
      }
   }
}

void update()
{
   // sets framerate
   previousTime = currentTime;
   currentTime = SDL_GetTicks();
   deltaTime = (currentTime - previousTime) / 1000.0f;

   frameTime += deltaTime;
   if(frameTime >= 0.25f)
   {
      frameTime = 0;
      // add things here
   }
}

void render()
{ 
   //SDL_BlitScaled(imageSurface, NULL, windowSurface, &drawingRect);
   //SDL_UpdateWindowSurface(window);
   SDL_RenderClear(renderTarget);
   SDL_RenderCopy(renderTarget, image, NULL, NULL);
   SDL_RenderPresent(renderTarget);
}

void clean()
{
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderTarget);
   SDL_DestroyTexture(image);
   window = NULL;
   renderTarget = NULL;
   SDL_Quit();
}

