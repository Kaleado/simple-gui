#include "sgui_main.hpp"

SguiEnvironment e;

//Returns whether the mouse is hovering over the widget to which the callback belongs.
bool isMouseOver(SguiCallback* data)
{
	SguiCallback* b = data;
	int ax, ay;
	SDL_GetMouseState(&ax, &ay);
	if (ax >= b->parent->x && ax <= b->parent->x + b->parent->w &&
		ax >= b->parent->y && ax <= b->parent->y + b->parent->h)
	{
		return true;
	}
	return false;
}

void main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	screen = SDL_GetWindowSurface(gWindow);
	SDL_SetSurfaceBlendMode(screen, SDL_BLENDMODE_BLEND);
	bool quit = 0;
	SDL_Event ev;
	SguiWindow a;
	a.border = IMG_Load("res/window.png");
	a.w = a.border->w;
	a.h = a.border->h;
	a.x = 10;
	a.y = 10;
	e.windows.push_back(a);
	while (!quit)
	{
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT){ quit = true; }
		e.perform_gui_operations();
		SDL_UpdateWindowSurface(gWindow);
	}
	return;
}