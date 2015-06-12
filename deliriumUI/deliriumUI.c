
#include "deliriumUI.h"

static deliriumUIWidget* deliriumUIWidgets = NULL;
static int numberOfUIWidgets = 1;

static void roundedBox(cairo_t* cr, double x, double y, double w, double h)
{
	static const double radius  = 10;
	static const double degrees = 3.14159265 / 180.0;

	cairo_new_sub_path(cr);
	cairo_arc(cr,
	          x + w - radius,
	          y + radius,
	          radius, -90 * degrees, 0 * degrees);
	cairo_arc(cr,
	          x + w - radius, y + h - radius,
	          radius, 0 * degrees, 90 * degrees);
	cairo_arc(cr,
	          x + radius, y + h - radius,
	          radius, 90 * degrees, 180 * degrees);
	cairo_arc(cr,
	          x + radius, y + radius,
	          radius, 180 * degrees, 270 * degrees);
	cairo_close_path(cr);
}

//------------------------------------------------------------------
// Add widget

int addDeliriumUIWidget(int _x, int _y, int _w, int _h, char* _label)
{
	deliriumUIWidgets = realloc( deliriumUIWidgets, sizeof(deliriumUIWidget) * numberOfUIWidgets );

	deliriumUIWidgets[numberOfUIWidgets-1].x = _x;
	deliriumUIWidgets[numberOfUIWidgets-1].y = _y;
	deliriumUIWidgets[numberOfUIWidgets-1].w = _w;
	deliriumUIWidgets[numberOfUIWidgets-1].h = _h;
	deliriumUIWidgets[numberOfUIWidgets-1].pressed = false;
	deliriumUIWidgets[numberOfUIWidgets-1].hover = false;
	deliriumUIWidgets[numberOfUIWidgets-1].label = _label;

	numberOfUIWidgets++;

	return numberOfUIWidgets-1; // return handle number
} 

//------------------------------------------------------------------
// set packing grid size

void setDeliriumUIGridSize(int _w, int _h, int _x, int _y)
{
	deliriumWindow.originalWidth = _w;
	deliriumWindow.originalHeight = _h;
	deliriumWindow.currentWidth = _w;
	deliriumWindow.currentHeight = _h;
	deliriumWindow.gridX = _x;
	deliriumWindow.gridY = _y;
	deliriumWindow.widgetWidth = _w / _x;
	deliriumWindow.widgetHeight = _h / _y;
}

//------------------------------------------------------------------
// set current window size

void setDeliriumUICurrentWindowSize(int _w, int _h)
{
	deliriumWindow.currentWidth = _w;
	deliriumWindow.currentHeight = _h;
	deliriumWindow.widgetWidth = _w / deliriumWindow.gridX;
	deliriumWindow.widgetHeight = _h / deliriumWindow.gridY;
}

//------------------------------------------------------------------
// Display wisget

void displayDeliriumUIWidget(cairo_t* cr, int widgetNumber)
{

	int x = deliriumUIWidgets[widgetNumber].x * deliriumWindow.widgetWidth;
	int y = deliriumUIWidgets[widgetNumber].y * deliriumWindow.widgetHeight;
	int w = deliriumUIWidgets[widgetNumber].w * deliriumWindow.widgetWidth;
	int h = deliriumUIWidgets[widgetNumber].h * deliriumWindow.widgetHeight;

	x += deliriumUIWidgets[widgetNumber].pressed * 2;
	y += deliriumUIWidgets[widgetNumber].pressed * 2;

	

	cairo_rectangle(cr, x, y, w, h);
	cairo_clip(cr);

	// Draw base
	if (deliriumUIWidgets[widgetNumber].hover) {
		cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 1);
	} else {
		cairo_set_source_rgba(cr, 0.3, 0.3, 0.3, 1);
	}

	roundedBox(cr, x, y, w, h);
	cairo_fill_preserve(cr);

	// Draw border
	cairo_set_source_rgba(cr, 0.0, 0.0, 0.0, 1);
	cairo_set_line_width(cr, 4.0);
	cairo_stroke(cr);

	// Draw label
	cairo_text_extents_t extents;
	cairo_set_font_size(cr, deliriumWindow.widgetHeight / 1.5);
	cairo_text_extents(cr, deliriumUIWidgets[widgetNumber].label, &extents);
	cairo_move_to(cr,
	              (x + w / 2) - extents.width / 2,
	              (y + h / 2) + extents.height / 2);

	cairo_set_source_rgba(cr, 0, 0, 0, 1);
	cairo_show_text(cr, deliriumUIWidgets[widgetNumber].label);

	cairo_reset_clip(cr);


}

//------------------------------------------------------------------
// Display all widgets

void displayAllDeliriumUIWidgets(cairo_t* cr)
{
	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		displayDeliriumUIWidget(cr, widgetNumber);
	}
}

//------------------------------------------------------------------
// Set widget hover flag

void setDeliriumUIWidgetHover(int widgetNumber, bool _hover)
{
	deliriumUIWidgets[widgetNumber].hover = _hover;
}

//------------------------------------------------------------------
// check if mouse is hovering over widget
void isMouseOverDeliriumUIWidget(int _x, int _y)
{
	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		int x = deliriumUIWidgets[widgetNumber].x * deliriumWindow.widgetWidth;
		int y = deliriumUIWidgets[widgetNumber].y * deliriumWindow.widgetHeight;
		int w = deliriumUIWidgets[widgetNumber].w * deliriumWindow.widgetWidth;
		int h = deliriumUIWidgets[widgetNumber].h * deliriumWindow.widgetHeight;

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

void hasMouseClickedDeliriumUIWidget(int _x, int _y)
{
	for (int widgetNumber=0; widgetNumber<numberOfUIWidgets-1; ++widgetNumber)
	{
		int x = deliriumUIWidgets[widgetNumber].x * deliriumWindow.widgetWidth;
		int y = deliriumUIWidgets[widgetNumber].y * deliriumWindow.widgetHeight;
		int w = deliriumUIWidgets[widgetNumber].w * deliriumWindow.widgetWidth;
		int h = deliriumUIWidgets[widgetNumber].h * deliriumWindow.widgetHeight;

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

void cleanUpDeliriumUI()
{
	free(deliriumUIWidgets);
}





