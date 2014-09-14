#ifndef SGUI_WIDGET_H
#define SGUI_WIDGET_H
#include "sgui_callback.hpp"

class SguiWindow;

//Class for widgets which appear in each window.
class SguiWidget
{
private:
public:
	std::vector <SguiCallback> callbacks; //The callbacks associated with the widget.
	SguiWindow* parent; //The widget's parent window.
	int x, y; //The widget's position in its parent window.
	int w, h; //The widget's width and height.
	void* data; //The data used by the widget.
	void*(show)(SguiWidget*); //Function pointer to show the widget on screen.
	SguiWidget(){} //Empty constructor.
	SguiWidget(SguiWindow* parent,
				int x, int y,
				int w, int h,
				void* data,
				void*(show)(SguiWidget*))
	{
		this->parent = parent;
		this->x = x; this->y = y;
		this->w = w; this->h = h;
		this->data = data;
		this->show = show;
	}
};

#endif