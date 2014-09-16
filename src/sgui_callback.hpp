#ifndef SGUI_CALLBACK_H
#define SGUI_CALLBACK_H
#include "sgui_render.h"

class SguiWidget;
class SguiCallback;

typedef bool(*condition)(SguiCallback* parent);//An awful hack to make the proper vector.

//Class for callbacks that are executed when certain conditions are met.
class SguiCallback
{
public:
	SguiWidget* parent; //The widget to which this callback belongs. If none, is set to NULL.
	std::vector <condition> conditions; //The conditions to be met in order for the callback to run.
	void (*callback)(SguiCallback*); //A function pointer to the function to be executed when the conditions are met.
	SguiCallback(std::vector <condition> conditions, void(*callback)(SguiCallback*))
	{
		//this->parent = parent;
		this->conditions = conditions;
		this->callback = callback;
		return;
	}
};

#endif