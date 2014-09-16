#define undefined -0x77777777
#include "sgui_main.hpp"
#undef main
SguiEnvironment e;

//Returns whether the mouse is hovering over the widget to which the callback belongs.
bool isMouseOver(SguiCallback* data)
{
	SguiCallback* b = data;
	int ax, ay;
	SDL_GetMouseState(&ax, &ay);
	int widgetX = b->parent->parent->x + b->parent->x;
	int widgetY = b->parent->parent->y + b->parent->y;
	if (ax >= widgetX && ax <= widgetX + b->parent->w &&
		ay >= widgetY && ay <= widgetY + b->parent->h)
	{
		return true;
	}
	return false;
}

bool isMouseClicked(SguiCallback *data)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		return true;
	}
	return false;
}

bool isMouseUnclicked(SguiCallback *data)
{
	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT))
	{
		return false;
	}
	return true;
}

void showWidget(SguiWidget* parent)
{
	apply(parent->parent->x + parent->x, parent->parent->y + parent->y, parent->img, screen);
	return;
}

void dragParentWindow(SguiCallback* parent)
{
	int mx, my;
	int ox, oy;
	SDL_GetMouseState(&mx, &my);
	ox = mx - parent->parent->parent->x;
	oy = my - parent->parent->parent->y;
	if (parent->parent->mouseOffsetX == undefined && parent->parent->mouseOffsetY == undefined)
	{
		parent->parent->mouseOffsetX = ox;
		parent->parent->mouseOffsetY = oy;
	}
	parent->parent->parent->x = mx - parent->parent->mouseOffsetX;
	parent->parent->parent->y = my - parent->parent->mouseOffsetY;
	return;
}

void undragParentWindow(SguiCallback* parent)
{
	parent->parent->mouseOffsetX = undefined;
	parent->parent->mouseOffsetY = undefined;
	return;
}

void main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	int imgFlags = IMG_INIT_PNG;
	IMG_Init(imgFlags);
	screen = SDL_GetWindowSurface(gWindow);
	SDL_SetSurfaceBlendMode(screen, SDL_BLENDMODE_BLEND);
	SDL_Event ev;
	bool quit = 0;
	SguiWidget wdg = SguiWidget(
		NULL, IMG_Load("res/titlebar.png"), 0, -30, 250, 30, NULL, showWidget, 
		{SguiCallback({ isMouseOver, isMouseClicked }, dragParentWindow),
		SguiCallback({ isMouseOver, isMouseUnclicked }, undragParentWindow),
		});
	SDL_Surface *u = IMG_Load("res/background.png");
	while (!quit)
	{
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT){ quit = true; }
		if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_1){ e.spawn_window(10, 10, 100, 75, "res/window.png", { wdg }); }
		apply(0, 0, u, screen);
		e.perform_gui_operations();
		SDL_UpdateWindowSurface(gWindow);
	}
	return;
}