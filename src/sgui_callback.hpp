#ifndef SGUI_CALLBACK_H
#define SGUI_CALLBACK_H
#include "sgui_render.h"

class SguiWidget;

//Class for callbacks that are executed when certain conditions are met.
class SguiCallback
{
public:
	SguiWidget* parent; //The widget to which this callback belongs. If none, is set to NULL.
	std::vector <bool*(SguiCallback*)> conditions; //The conditions to be met in order for the callback to run.
	void(*callback)(void*); //A function pointer to the function to be executed when the conditions are met.
};

//Returns whether the mouse is hovering over the widget to which the callback belongs.
bool isMouseOver(SguiCallback* data)
{
	SguiCallback* b = data;
	int ax, ay;
	SDL_GetMouseState(&ax, &ay);
	if (ax >= b->parent->x && ax <= b->parent->x+b->parent->w &&
		ax >= b->parent->y && ax <= b->parent->y+b->parent->h)
	{
		return true;
	}
	return false;
}

#endif