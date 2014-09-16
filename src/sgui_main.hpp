#ifndef SGUI_MAIN_H
#define SGUI_MAIN_H
#include "sgui_window.hpp"

//Main encapsulating class, holding all other elements of the GUI.
class SguiEnvironment
{
public:
	SguiWindow* focusedWindow; //The window that currently has focus.
	std::vector <SguiWindow> windows; //The windows present on the screen.
	void spawn_window(int x, int y, 
		int w, int h, 
		std::string borderPath, 
		std::vector <SguiWidget> widgets)
	{
		windows.push_back(SguiWindow(x, y, w, h, IMG_Load(borderPath.c_str()), widgets));
		windows.back().mouseOffsetX = undefined;
		windows.back().mouseOffsetY = undefined;
		for (int i = 0; i < windows.back().widgets.size(); i++)
		{
			//Set the widget's parent to the window to be created, at the end of the windows vector.
			windows.back().widgets[i].parent = &windows.back(); 
			for (int j = 0; j < windows.back().widgets[i].callbacks.size(); j++)
			{
				//Set the callback's parent widget as the widget it is attached to.
				windows.back().widgets[i].callbacks[j].parent = &windows.back().widgets[i];
			}
		}
		return;
	}
	//Set the focused window, based on mouse position.
	void set_focus()
	{
		for (int i = 0; i < windows.size(); i++)
		{
			//Set B to the address of windows[i], for simplicity.
			SguiWindow *b = &windows[i];
			int ax, ay;
			//Get the mouse state, and insert the value into C.
			int c = SDL_GetMouseState(&ax, &ay); 
			//Determine whether the mouse is over the window, and the left mouse button is clicked.
			if (ax >= b->x && ax <= b->x + b->w &&
				ax >= b->y && ax <= b->y + b->h &&
				c & SDL_BUTTON(SDL_BUTTON_LEFT))
			{
				std::swap(windows.begin() + i, windows.end());
				focusedWindow = &windows[windows.size()-1];
			}
		}
		return;
	}

	//Executes callbacks if all conditions are met.
	void execute_callbacks()
	{
		bool successful = true;
		int i=0, j=0, k=0, l=0;
		for (; i < windows.size(); i++)
		{
			for (; j < windows[i].widgets.size(); j++)
			{
				for (; k < windows[i].widgets[j].callbacks.size(); k++)
				{
					successful = true;
					for (; l < windows[i].widgets[j].callbacks[k].conditions.size(); l++)
					{
						if (windows[i].widgets[j].callbacks[k].conditions[l](&windows[i].widgets[j].callbacks[k]) == false)
						{ 
							successful = false;
							break;
						}
					}
					if (successful)
					{ 
						if (windows[i].widgets[j].callbacks[k].callback)
						{
							windows[i].widgets[j].callbacks[k].callback(&windows[i].widgets[j].callbacks[k]); 
						}
					}
				}}}
		return;
	}

	//Display all the open windows on the screen.
	void show_windows()
	{
		for (int i = 0; i < windows.size(); i++)
		{
			windows[i].show();
		}
		return;
	}
	void perform_gui_operations()
	{
		set_focus();
		execute_callbacks();
		show_windows();
		return;
	}
};

#endif