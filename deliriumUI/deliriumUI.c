
#include "deliriumUI.h"

static deliriumUIObject* deliriumUIObjects;
static int numberOfUIObjects = 1;


//------------------------------------------------------------------
// Initialise object list

void initDeliriumUI()
{
	deliriumUIObjects = malloc( sizeof(deliriumUIObject) * numberOfUIObjects );

	deliriumUIObjects[numberOfUIObjects].x = 2;
	deliriumUIObjects[numberOfUIObjects].y = 2;
	deliriumUIObjects[numberOfUIObjects].w = 128;
	deliriumUIObjects[numberOfUIObjects].h = 64;
	deliriumUIObjects[numberOfUIObjects].pressed = false;
	deliriumUIObjects[numberOfUIObjects].label = "Test";


} 

//------------------------------------------------------------------
// Initialise object list

int adDeliriumUIObject()
{
	numberOfUIObjects++;

	deliriumUIObjects = realloc( deliriumUIObjects, sizeof(deliriumUIObject) * numberOfUIObjects );

	deliriumUIObjects[numberOfUIObjects].x = 0;
	deliriumUIObjects[numberOfUIObjects].y = 0;
	deliriumUIObjects[numberOfUIObjects].w = 0;
	deliriumUIObjects[numberOfUIObjects].h = 0;
	deliriumUIObjects[numberOfUIObjects].pressed = false;

	return numberOfUIObjects; // return handle number
} 

//------------------------------------------------------------------
// Initialise object list

void displayDeliriumUIObject(cairo_t* cr, int objectNumber)
{
	// Draw base
	if (deliriumUIObjects[objectNumber].pressed) {
		cairo_set_source_rgba(cr, 0.4, 0.9, 0.1, 1);
	} else {
		cairo_set_source_rgba(cr, 0.3, 0.5, 0.1, 1);
	}
	roundedBox(cr, deliriumUIObjects[objectNumber].x, deliriumUIObjects[objectNumber].y,
		deliriumUIObjects[objectNumber].w, deliriumUIObjects[objectNumber].h);
	cairo_fill_preserve(cr);

	// Draw border
	cairo_set_source_rgba(cr, 0.4, 0.9, 0.1, 1);
	cairo_set_line_width(cr, 4.0);
	cairo_stroke(cr);

	// Draw label
	cairo_text_extents_t extents;
	cairo_set_font_size(cr, 32.0);
	cairo_text_extents(cr, deliriumUIObjects[objectNumber].label, &extents);
	cairo_move_to(cr,
	              (deliriumUIObjects[objectNumber].x + deliriumUIObjects[objectNumber].w / 2) - extents.width / 2,
	              (deliriumUIObjects[objectNumber].y + deliriumUIObjects[objectNumber].h / 2) + extents.height / 2);
	cairo_set_source_rgba(cr, 0, 0, 0, 1);
	cairo_show_text(cr, deliriumUIObjects[objectNumber].label);
}


//------------------------------------------------------------------
// Initialise object list

void cleanUpDeliriumUI()
{
	free(deliriumUIObjects);
}





