#ifndef SGUI_MAIN_H
#define SGUI_MAIN_H
#include "sgui_window.hpp"

//Main encapsulating class, holding all other elements of the GUI.
class SguiEnvironment
{
public:
	SguiWindow* focusedWindow;//The window that currently has focus.
	std::vector <SguiWindow> windows;
	std::vector <SguiCallback*> callbackArray;
	//Add a callback to the callback array, as well as an assigned widget.
	void add_callback(SguiCallback a, SguiWidget* b)
	{
		b->callbacks.push_back(a); //Add callback A to widget B.
		callbackArray.push_back(&b->callbacks.back()); //Add callback B's new address to the callback array.
		return;
	}
	//Remove the callback, if it exists. Do nothing if it does not.
	void remove_callback(SguiCallback* a)
	{
		//If the callback can be found in the callback array.
		if (std::find(callbackArray.begin(), callbackArray.end(), a) != callbackArray.end())
		{ 
			//Remove the callback.
			callbackArray.erase(std::find(callbackArray.begin(), callbackArray.end(), a), callbackArray.end());
		}
		return;
	}
	void spawn_window(int x, int y, 
		int w, int h, 
		std::string borderPath, 
		std::vector <SguiWidget> widgets)
	{
		SguiWindow wnd;
		wnd.mouseOffsetX = undefined;
		wnd.mouseOffsetY = undefined;
		wnd.border = IMG_Load(borderPath.c_str());
		wnd.w = w; wnd.h = h; wnd.x = x; wnd.y = y;
		wnd.widgets = widgets;
		windows.push_back(wnd);
		for (int i = 0; i < windows.back().widgets.size(); i++)
		{
			//Set the widget's parent to the window to be created, at the end of the windows vector.
			windows.back().widgets[i].parent = &windows.back(); 
			for (int j = 0; j < windows.back().widgets[i].callbacks.size(); j++)
			{
				windows.back().widgets[i].callbacks[j].parent = &windows.back().widgets[i];
				callbackArray.push_back(&windows.back().widgets[i].callbacks[j]);
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
		//Iterate over every callback in the callback array (i.e. every callback that can be executed).
		for (int j = 0; j < callbackArray.size(); j++)
		{
			bool successful = true;
			for (int i = 0; i < callbackArray[j]->conditions.size(); i++)
			{
				//Check each condition for true / false, setting the 'successful' flag as necessary.
				if (callbackArray[j]->conditions[i](callbackArray[j]) == false){ successful = false; break; }
			}
			//Execute the callback if none of the conditions fail.
			if (successful){ callbackArray[j]->callback(callbackArray[j]); }
		}
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
		//set_focus();
		execute_callbacks();
		show_windows();
		return;
	}
};

#endif