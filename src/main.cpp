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

void dragParent(SguiCallback* parent)
{
	int mx, my;
	int ox, oy;
	SDL_GetMouseState(&mx, &my);
	ox = mx - parent->parent->parent->x;
	oy = my - parent->parent->parent->y;
	parent->parent->parent->x = mx;
	parent->parent->parent->y = my;
	return;
}

void test(SguiCallback* parent)
{
	parent->parent->parent->x = 50;
	parent->parent->parent->y = 50;
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
	
	SguiWidget wdg = SguiWidget(NULL, 0, 0, 100, 5, NULL, NULL, { SguiCallback(&wdg, { isMouseOver, isMouseClicked }, dragParent) });
	//e.add_callback(SguiCallback(&wdg, {isMouseOver, isMouseClicked}, test), &wdg);
	e.spawn_window(10, 10, 100, 75, "res/window.png", { wdg });

	while (!quit)
	{
		SDL_PollEvent(&ev);
		if (ev.type == SDL_QUIT){ quit = true; }
		e.perform_gui_operations();
		SDL_UpdateWindowSurface(gWindow);
	}
	return;
}