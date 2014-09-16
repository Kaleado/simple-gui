#define undefined -0x77777777
#include "sgui_main.hpp"
#undef main
SguiEnvironment e;
SDL_Event ev;

//Returns whether the mouse is hovering over the widget to which the callback belongs.
bool isMouseOver(SguiCallback* data)
{
	int ax, ay;
	SDL_GetMouseState(&ax, &ay);
	int widgetX = data->parent->parent->x + data->parent->x;
	int widgetY = data->parent->parent->y + data->parent->y;
	if (ax >= widgetX && ax <= widgetX + data->parent->w &&
		ay >= widgetY && ay <= widgetY + data->parent->h)
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
	if (ev.type == SDL_MOUSEBUTTONUP)
	{
		return true;
	}
	return false;
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
	if (parent->parent->parent->isBeingDragged == false)
	{
		parent->parent->mouseOffsetX = ox;
		parent->parent->mouseOffsetY = oy;
		parent->parent->parent->isBeingDragged = true;
	}
	parent->parent->parent->x = mx-parent->parent->mouseOffsetX;
	parent->parent->parent->y = my-parent->parent->mouseOffsetY;
	return;
}

void undragParentWindow(SguiCallback* parent)
{
	parent->parent->mouseOffsetX = undefined;
	parent->parent->mouseOffsetY = undefined;
	parent->parent->parent->isBeingDragged = false;
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
	bool quit = 0;
	SguiWidget wdg = SguiWidget(
		IMG_Load("res/titlebar.png"), 0, -30, 250, 30, NULL, showWidget, 
		{SguiCallback({ isMouseUnclicked }, undragParentWindow),
		SguiCallback({ isMouseOver, isMouseClicked }, dragParentWindow),
		SguiCallback({}, NULL)
		});
	SDL_Surface *u = IMG_Load("res/background.png");
	while (!quit)
	{
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT){ quit = true; }
		if (ev.type == SDL_KEYDOWN && ev.key.keysym.sym == SDLK_1)
		{ 
			e.spawn_window(10, 10, 100, 75, "res/window.png", { wdg }); 
		}
		apply(0, 0, u, screen);
		e.perform_gui_operations();
		SDL_UpdateWindowSurface(gWindow);
	}
	return;
}