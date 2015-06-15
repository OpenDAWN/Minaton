 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cairo/cairo.h>
#include "pugl/pugl.h"

typedef enum 
{
	deliriumUI_Button,
	deliriumUI_Knob
} deliriumUI_WidgetType;

typedef struct {
	deliriumUI_WidgetType	type;
	int	x;
	int	y;
	int	w;
	int	h;
	bool	pressed;
	bool	hover;
	const char* label;
	float value;
} deliriumUIWidget;

typedef struct {
	int originalWidth;
	int originalHeight;
	int currentWidth;
	int currentHeight;
	int gridX;
	int gridY;
	int widgetWidth;
	int widgetHeight;
	deliriumUIWidget* deliriumUIWidgets;
	int numberOfUIWidgets;
} deliriumUI;


void cleanUpDeliriumUI(deliriumUI*);
void setDeliriumUIGridSize(deliriumUI*, int, int, int, int);
void setDeliriumUICurrentWindowSize(deliriumUI*, int, int);
int addDeliriumUIButtonWidget(deliriumUI*, int, int, int, int, char*);
int addDeliriumUIKnobWidget(deliriumUI*, int, int, int, int, char*);
void displayDeliriumUIWidget(deliriumUI*, cairo_t*, int);
void displayAllDeliriumUIWidgets(deliriumUI*, cairo_t* cr);
void setDeliriumUIWidgetHover(deliriumUI*, int, bool);
void isMouseOverDeliriumUIWidget(deliriumUI*, int, int);
void hasMouseClickedDeliriumUIWidget(deliriumUI*, int, int);

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


void displayDiliriumUIButton(deliriumUI*, cairo_t*, int);
void displayDiliriumUIKnob(deliriumUI*, cairo_t*, int);


