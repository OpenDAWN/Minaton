
#include "deliriumUI.h"

//------------------------------------------------------------------
// Add Widget

int addDeliriumUIWidget(deliriumUI* deliriumUI_window, deliriumUI_WidgetType widgetType, float _x, float _y, float _w, float _h, char* _label)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUIWidgets = realloc( deliriumUIWidgets, sizeof(deliriumUIWidget) * numberOfUIWidgets );

	deliriumUI_window->deliriumUIWidgets = deliriumUIWidgets;

	deliriumUIWidgets[numberOfUIWidgets-1].type = widgetType;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].y = _y;
	deliriumUIWidgets[numberOfUIWidgets-1].w = _w;
	deliriumUIWidgets[numberOfUIWidgets-1].h = _h;
	deliriumUIWidgets[numberOfUIWidgets-1].pressed = false;
	deliriumUIWidgets[numberOfUIWidgets-1].hover = false;
	deliriumUIWidgets[numberOfUIWidgets-1].label = _label;
	deliriumUIWidgets[numberOfUIWidgets-1].value = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].toggleMode = false;
	deliriumUIWidgets[numberOfUIWidgets-1].clickTop = 0;
	deliriumUIWidgets[numberOfUIWidgets-1].clickBottom = 0;

	switch (widgetType)
	{
		
		case deliriumUI_Fader:
			deliriumUIWidgets[numberOfUIWidgets-1].clickTop = 20;
			deliriumUIWidgets[numberOfUIWidgets-1].clickBottom = 20;
			break;	

		case deliriumUI_Switch:
			deliriumUIWidgets[numberOfUIWidgets-1].toggleMode = true;
			break;
	}



	numberOfUIWidgets++;

	deliriumUI_window->numberOfUIWidgets = numberOfUIWidgets;

	return numberOfUIWidgets-1; // return handle number
}



//------------------------------------------------------------------
// set packing grid size

void setDeliriumUIGridSize(deliriumUI* deliriumUI_window, int _w, int _h, int _x, int _y)
{
	deliriumUI_window->originalWidth = _w;
	deliriumUI_window->originalHeight = _h;
	deliriumUI_window->currentWidth = _w;
	deliriumUI_window->currentHeight = _h;
	deliriumUI_window->gridX = _x;
	deliriumUI_window->gridY = _y;
	deliriumUI_window->widgetWidth = _w / _x;
	deliriumUI_window->widgetHeight = _h / _y;
}

//------------------------------------------------------------------
// set current window size

void setDeliriumUICurrentWindowSize(deliriumUI* deliriumUI_window, int _w, int _h)
{
	deliriumUI_window->currentWidth = _w;
	deliriumUI_window->currentHeight = _h;
	deliriumUI_window->widgetWidth = _w / deliriumUI_window->gridX;
	deliriumUI_window->widgetHeight = _h / deliriumUI_window->gridY;
}

//------------------------------------------------------------------
// Display widget
void displayDeliriumUIWidget(deliriumUI* deliriumUI_window, cairo_t* cr, int widgetNumber)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	deliriumUI_WidgetType type = deliriumUIWidgets[widgetNumber].type;

	switch (type)
	{
		case deliriumUI_Button:
			displayDiliriumUIButton(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_Knob:
			displayDiliriumUIKnob(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_MicroKnob:
			displayDiliriumUIMicroKnob(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_Fader:
			displayDiliriumUIFader(deliriumUI_window, cr, widgetNumber);
			break;

		case deliriumUI_Switch:
			displayDiliriumUISwitch(deliriumUI_window, cr, widgetNumber);
			break;
	}
}

//------------------------------------------------------------------
// Display all widgets

void displayAllDeliriumUIWidgets(deliriumUI* deliriumUI_window, cairo_t* cr)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	/* Set surface to opaque color (r, g, b) */
	cairo_set_source_rgb (cr, 0.2, 0.0, 0.0);
	cairo_paint (cr);

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
	}
}

//--------------------------------------------------------------------------

void setValueFromMousePosition(deliriumUI* deliriumUI_window, int widgetNumber, int _x, int _y)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	float x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
	float y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
	float w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
	float h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

	float clickTop = h * (deliriumUIWidgets[widgetNumber].clickTop/100);
	float clickBottom = h * (deliriumUIWidgets[widgetNumber].clickBottom/100);
	
	y += clickTop;
	h -= (clickTop+clickBottom);

	float newValue = (_y - y) / h;

	printf("%f - %f\n",clickTop, clickBottom);

	setValueDiliriumUIFader(deliriumUI_window, widgetNumber, newValue );
	deliriumUIWidgets[widgetNumber].hover = true;
}

//------------------------------------------------------------------
// check if mouse is hovering over widget
void isMouseOverDeliriumUIWidget(deliriumUI* deliriumUI_window, cairo_t* cr, int _x, int _y)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUI_window->currentWidgetNumber = -1;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		float x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
		float y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
		float w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
		float h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

		if (deliriumUIWidgets[widgetNumber].pressed && deliriumUIWidgets[widgetNumber].type==deliriumUI_Fader)
		{

			setValueFromMousePosition(deliriumUI_window, widgetNumber, _x, _y);
			displayDeliriumUIWidget(deliriumUI_window, cr, widgetNumber);
		}

		if (!deliriumUI_window->mouseButton[1])
		{
			if (_x>=x && _y>=y && _x<=x+w && _y<=y+h) 
			{
				deliriumUIWidgets[widgetNumber].hover = true;
				deliriumUI_window->currentWidgetNumber = widgetNumber;
			}
			else
			{
				deliriumUIWidgets[widgetNumber].hover = false;
			}
		}
	}
}


//------------------------------------------------------------------
// check if widget has been clicked by mouse button

void hasMouseClickedDeliriumUIWidget(deliriumUI* deliriumUI_window, int _x, int _y)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		float x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
		float y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
		float w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
		float h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

		w -= 2;
		h -= 2;
	
		if (!deliriumUIWidgets[widgetNumber].toggleMode)
		{
			if (_x>=x && _y>=y && _x<=x+w && _y<=y+h && deliriumUIWidgets[widgetNumber].type==deliriumUI_Fader) 
			{
				deliriumUIWidgets[widgetNumber].pressed = true;
				setValueFromMousePosition(deliriumUI_window, widgetNumber, _x, _y);


			}
			else
			{
				deliriumUIWidgets[widgetNumber].pressed = false;
			}
		}
		else
		{
			if (_x>=x && _y>=y && _x<=x+w && _y<=y+h) 
			{
				deliriumUIWidgets[widgetNumber].pressed = 1-deliriumUIWidgets[widgetNumber].pressed;

			}
		}
	}
}

//------------------------------------------------------------------
// Return number of widgets

int getNumberOfWidgets(deliriumUI* deliriumUI_window)
{
	return deliriumUI_window->numberOfUIWidgets;
}

//------------------------------------------------------------------
// Initialise widget list

void cleanUpDeliriumUI(deliriumUI* deliriumUI_window)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	free(deliriumUIWidgets);
}





