
#include "deliriumUI.h"

//------------------------------------------------------------------
// Add button widget

int addDeliriumUIButtonWidget(deliriumUI* deliriumUI_window, int _x, int _y, int _w, int _h, char* _label)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUIWidgets = realloc( deliriumUIWidgets, sizeof(deliriumUIWidget) * numberOfUIWidgets );

	deliriumUI_window->deliriumUIWidgets = deliriumUIWidgets;

	deliriumUIWidgets[numberOfUIWidgets-1].type = deliriumUI_Button;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].y = _y;
	deliriumUIWidgets[numberOfUIWidgets-1].w = _w;
	deliriumUIWidgets[numberOfUIWidgets-1].h = _h;
	deliriumUIWidgets[numberOfUIWidgets-1].pressed = false;
	deliriumUIWidgets[numberOfUIWidgets-1].hover = false;
	deliriumUIWidgets[numberOfUIWidgets-1].label = _label;
	deliriumUIWidgets[numberOfUIWidgets-1].value = 0;

	numberOfUIWidgets++;

	deliriumUI_window->numberOfUIWidgets = numberOfUIWidgets;

	printf ("\nNumber of widgets now at %d\n", deliriumUI_window->numberOfUIWidgets);

	return numberOfUIWidgets-1; // return handle number
} 

//------------------------------------------------------------------
// Add knob widget

int addDeliriumUIKnobWidget(deliriumUI* deliriumUI_window, int _x, int _y, int _w, int _h, char* _label)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	deliriumUIWidgets = realloc( deliriumUIWidgets, sizeof(deliriumUIWidget) * numberOfUIWidgets );

	deliriumUI_window->deliriumUIWidgets = deliriumUIWidgets;

	deliriumUIWidgets[numberOfUIWidgets-1].type = deliriumUI_Knob;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].y = _y;
	deliriumUIWidgets[numberOfUIWidgets-1].w = _w;
	deliriumUIWidgets[numberOfUIWidgets-1].h = _h;
	deliriumUIWidgets[numberOfUIWidgets-1].pressed = false;
	deliriumUIWidgets[numberOfUIWidgets-1].hover = false;
	deliriumUIWidgets[numberOfUIWidgets-1].label = _label;
	deliriumUIWidgets[numberOfUIWidgets-1].value = 0;

	numberOfUIWidgets++;

	deliriumUI_window->numberOfUIWidgets = numberOfUIWidgets;

	printf ("\nNumber of widgets now at %d\n", deliriumUI_window->numberOfUIWidgets);

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

//------------------------------------------------------------------
// Set widget hover flag

void setDeliriumUIWidgetHover(deliriumUI* deliriumUI_window, int widgetNumber, bool _hover)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	deliriumUIWidgets[widgetNumber].hover = _hover;
}

//------------------------------------------------------------------
// check if mouse is hovering over widget
void isMouseOverDeliriumUIWidget(deliriumUI* deliriumUI_window, int _x, int _y)
{

	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;
	int numberOfUIWidgets = deliriumUI_window->numberOfUIWidgets;

	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
		int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
		int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
		int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

		w -= 2;
		h -= 2;
		
		if (_x>=x && _y>=y && _x<=x+w && _y<=y+h) 
		{
			deliriumUIWidgets[widgetNumber].hover = true;
		}
		else
		{
			deliriumUIWidgets[widgetNumber].hover = false;
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
		int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
		int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
		int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
		int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

		w -= 2;
		h -= 2;
		
		if (_x>=x && _y>=y && _x<=x+w && _y<=y+h) 
		{
			deliriumUIWidgets[widgetNumber].pressed = true;

		}
		else
		{
			deliriumUIWidgets[widgetNumber].pressed = false;
		}
	}
}

//------------------------------------------------------------------
// Initialise widget list

void cleanUpDeliriumUI(deliriumUI* deliriumUI_window)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	free(deliriumUIWidgets);
}





