#ifndef SGUI_RENDER_H
#define SGUI_RENDER_H

#include <SDL.h>
#include <SDL_image.h>
#include <ctime>
#include <string>
#include <random>
#include <vector>

//Camera X and Y values.
int camX=0, camY=0;

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int WINDOW_WIDTH = SCREEN_WIDTH + 240;
const int WINDOW_HEIGHT = SCREEN_HEIGHT + 240;

//The surface contained by the window
SDL_Surface* screen = NULL;

void apply(int x, int y, SDL_Surface* src, SDL_Surface* dst);
SDL_Surface* load_surface(std::string path);

SDL_Surface* load_surface(std::string path)
{
	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, screen->format, NULL);
		if (optimizedSurface == NULL)
		{
			printf("Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}

void apply(int x, int y, SDL_Surface* src, SDL_Surface* dst)
{
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	offset.w = 1;
	offset.h = 1;
	SDL_BlitSurface(src, NULL, dst, &offset);
	return;
}

#endif