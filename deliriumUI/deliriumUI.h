 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cairo/cairo.h>

typedef struct {
	int originalWidth;
	int originalHeight;
	int currentWidth;
	int currentHeight;
	int gridX;
	int gridY;
	int widgetWidth;
	int widgetHeight;
} delWin;

static delWin deliriumWindow;

typedef struct {
	int         x;
	int         y;
	int         w;
	int         h;
	bool        pressed;
	const char* label;
} Button;

typedef struct {
	int type;
	int         x;
	int         y;
	int         w;
	int         h;
	bool        pressed;
	const char* label;
} deliriumUIWidget;

void cleanUpDeliriumUI();
void setDeliriumUIGridSize(int, int, int, int);
void setDeliriumUICurrentWindowSize(int, int);
int addDeliriumUIWidget(int, int, int, int, char*);
void displayDeliriumUIWidget(cairo_t*, int);

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





