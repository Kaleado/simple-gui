#ifndef SGUI_WINDOW_H
#define SGUI_WINDOW_H
#include "sgui_widget.hpp"

//Class for windows which appear on the screen. Things like window titles,
//titlebars, close buttons, and other decorations can be added as widgets.
class SguiWindow
{
public:
	int x, y; //X and Y coordinates on the screen.
	int w, h; //Width and height of the window.
	SDL_Surface* border; //The image displayed around the window.
	std::vector <SguiWidget> widgets; //A list of the widgets contained in the window.
	void show() //Show the window on the screen.
	{
		apply(x, y, border, screen);
		for (int i = 0; i < widgets.size(); i++)
		{
			if (widgets[i].show){ widgets[i].show(&widgets[i]); }
		}
		return;
	}
};

#endif