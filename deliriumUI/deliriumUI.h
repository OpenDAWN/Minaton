 
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
	int	type;
	int	x;
	int	y;
	int	w;
	int	h;
	bool	pressed;
	bool	hover;
	const char* label;
} deliriumUIWidget;

void cleanUpDeliriumUI();
void setDeliriumUIGridSize(int, int, int, int);
void setDeliriumUICurrentWindowSize(int, int);
int addDeliriumUIWidget(int, int, int, int, char*);
void displayDeliriumUIWidget(cairo_t*, int);
void displayAllDeliriumUIWidgets(cairo_t* cr);
void setDeliriumUIWidgetHover(int, bool);
void isMouseOverDeliriumUIWidget(int, int);
void hasMouseClickedDeliriumUIWidget(int, int);







