
#include "deliriumUI.h"

static deliriumUIWidget* deliriumUIWidgets = NULL;
static int numberOfUIWidgets = 1;



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
// Initialise widget list

void displayDeliriumUIWidget(cairo_t* cr, int widgetNumber)
{


	int x = deliriumUIWidgets[widgetNumber].x * deliriumWindow.widgetWidth;
	int y = deliriumUIWidgets[widgetNumber].y * deliriumWindow.widgetHeight;
	int w = deliriumUIWidgets[widgetNumber].w * deliriumWindow.widgetWidth;
	int h = deliriumUIWidgets[widgetNumber].h * deliriumWindow.widgetHeight;

	// Draw base
	if (deliriumUIWidgets[widgetNumber].pressed) {
		cairo_set_source_rgba(cr, 0.3, 0.3, 0.3, 1);
	} else {
		cairo_set_source_rgba(cr, 0.5, 0.5, 0.5, 1);
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
}


//------------------------------------------------------------------
// Initialise widget list

void cleanUpDeliriumUI()
{
	free(deliriumUIWidgets);
}





