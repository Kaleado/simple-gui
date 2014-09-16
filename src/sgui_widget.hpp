#ifndef SGUI_WIDGET_H
#define SGUI_WIDGET_H
#include "sgui_callback.hpp"

class SguiWindow;

//Class for widgets which appear in each window.
class SguiWidget
{
private:
public:
	bool isBeingDragged; //Whether the widget is being dragged by the mouse.
	int mouseOffsetX, mouseOffsetY; //The mouse offset within the widget.
	std::vector <SguiCallback> callbacks; //The callbacks associated with the widget.
	SguiWindow* parent; //The widget's parent window.
	SDL_Surface* img; //The widget's appearance.
	int x, y; //The widget's position in its parent window.
	int w, h; //The widget's width and height.
	void* data; //The data used by the widget.
	void(*show)(SguiWidget*); //Function pointer to show the widget on screen.
	SguiWidget(){} //Empty constructor.
	SguiWidget(SguiWindow* parent,
				SDL_Surface* img,
				int x, int y,
				int w, int h,
				void* data,
				void(*show)(SguiWidget*),
				std::vector <SguiCallback> callbacks)
	{
		this->parent = parent;
		this->img = img;
		this->x = x; this->y = y;
		this->w = w; this->h = h;
		this->data = data;
		this->show = show;
		this->callbacks = callbacks;
		mouseOffsetX = undefined;
		mouseOffsetY = undefined;
	}
};

#endif