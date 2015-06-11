
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
// Initialise widget list

void displayDeliriumUIWidget(cairo_t* cr, int widgetNumber)
{
	// Draw base
	if (deliriumUIWidgets[widgetNumber].pressed) {
		cairo_set_source_rgba(cr, 0.4, 0.9, 0.1, 1);
	} else {
		cairo_set_source_rgba(cr, 0.3, 0.5, 0.1, 1);
	}
	roundedBox(cr, deliriumUIWidgets[widgetNumber].x, deliriumUIWidgets[widgetNumber].y,
		deliriumUIWidgets[widgetNumber].w, deliriumUIWidgets[widgetNumber].h);
	cairo_fill_preserve(cr);

	// Draw border
	cairo_set_source_rgba(cr, 0.4, 0.9, 0.1, 1);
	cairo_set_line_width(cr, 4.0);
	cairo_stroke(cr);

	// Draw label
	cairo_text_extents_t extents;
	cairo_set_font_size(cr, 32.0);
	cairo_text_extents(cr, deliriumUIWidgets[widgetNumber].label, &extents);
	cairo_move_to(cr,
	              (deliriumUIWidgets[widgetNumber].x + deliriumUIWidgets[widgetNumber].w / 2) - extents.width / 2,
	              (deliriumUIWidgets[widgetNumber].y + deliriumUIWidgets[widgetNumber].h / 2) + extents.height / 2);
	cairo_set_source_rgba(cr, 0, 0, 0, 1);
	cairo_show_text(cr, deliriumUIWidgets[widgetNumber].label);
}


//------------------------------------------------------------------
// Initialise widget list

void cleanUpDeliriumUI()
{
	free(deliriumUIWidgets);
}





