
#include "deliriumUI.h"
#include <math.h>
#define M_PI 3.14159265358979323846264338327

void displayDiliriumUISwitch(deliriumUI* deliriumUI_window, cairo_t* cr, int widgetNumber)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
	int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
	int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
	int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

	float value = deliriumUIWidgets[widgetNumber].pressed; // deliriumUIWidgets[widgetNumber].value;

	float sx = x;
	float sy = y;
	float sw = w;
	float sh = h * 0.8;

	//---------------------

	if (value)
	{
		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), sw/2.8, 0.0, 2 * M_PI);

		cairo_set_source_rgba(cr, 0,0,0,0.5);
		cairo_fill(cr);

		cairo_pattern_t* grad1;
		grad1 = cairo_pattern_create_linear(sx+(sw/1.9), sy+(sh/1.9), sx+(sw/3), sy+(sh/3) );

		cairo_pattern_add_color_stop_rgba(grad1, 0,0.2,0.2,0.2,1);
		cairo_pattern_add_color_stop_rgba(grad1, 0.3,0.4,0.4,0.4,1);
		cairo_pattern_add_color_stop_rgba(grad1, 1,0.0,0.0,0.0,1);

		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), sw/3, 0.0, 2 * M_PI);

		cairo_set_source(cr, grad1);
		cairo_fill(cr);

		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), sw/5, 0.0, 2 * M_PI);

		cairo_set_source_rgba(cr, 0,0,0,0.5);
		cairo_fill(cr);

		cairo_pattern_t* grad_led;
		grad_led = cairo_pattern_create_radial(sx+(w/1.9), sy+(sh/1.9), 0, sx+(sw/2), sy+(sh/2), sw/2.5);

		cairo_pattern_add_color_stop_rgba(grad_led, 0,0.0,0.9,0.0,1);
	        cairo_pattern_add_color_stop_rgba(grad_led, 0.3,0.0,0.1,0.0,1);
	        cairo_pattern_add_color_stop_rgba(grad_led, 0.9,0.0,0.10,0.0,1);
	        cairo_pattern_add_color_stop_rgba(grad_led, 1.0,0.0,0.0,0.0,1);

		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), sw/6, 0.0, 2 * M_PI);
		cairo_set_source(cr, grad_led);
		cairo_fill(cr);

	}
	else
	{
		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), (sw/2.8), 0.0, 2 * M_PI);

		cairo_set_source_rgba(cr, 0,0,0,0.5);
		cairo_fill(cr);
	
		cairo_pattern_t* grad1;

		grad1 = cairo_pattern_create_linear(sx+(sw/1.9), sy+(sh/1.9), sx+(sw/3), sy+(sh/3) );

		cairo_pattern_add_color_stop_rgba(grad1, 0,0.2,0.2,0.2,1);
		cairo_pattern_add_color_stop_rgba(grad1, 0.5,0.4,0.4,0.4,1);
		cairo_pattern_add_color_stop_rgba(grad1, 1,0.0,0.0,0.0,1);

		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), (sw/3), 0.0, 2 * M_PI);

		cairo_set_source(cr, grad1);
		cairo_fill(cr);

		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), (sw/5), 0.0, 2 * M_PI);

		cairo_set_source_rgba(cr, 0,0,0,0.5);
		cairo_fill(cr);

		cairo_pattern_t* grad_led;

		grad_led = cairo_pattern_create_radial(sx+(sw/2), sy+(sh/2), 0, sx+(sw/2), sy+(sh/2), (sw/2.5) );

		cairo_pattern_add_color_stop_rgba(grad_led, 0,0.0,0.2,0.0,1);
	        cairo_pattern_add_color_stop_rgba(grad_led, 0.3,0.0,0.01,0.0,1);
	        cairo_pattern_add_color_stop_rgba(grad_led, 0.8,0.0,0.01,0.0,1);
	        cairo_pattern_add_color_stop_rgba(grad_led, 1.0,0.0,0.0,0.0,1);

		cairo_arc(cr, sx+(sw/1.9), sy+(sh/1.9), (sw/6), 0.0, 2*M_PI);
		cairo_set_source(cr, grad_led);
		cairo_fill(cr);
	}

	// Draw label
	cairo_text_extents_t extents;
	cairo_set_font_size(cr, h / 6);
	cairo_text_extents(cr, deliriumUIWidgets[widgetNumber].label, &extents);

	cairo_move_to(cr,
	              (x + w / 2) - extents.width / 2,
	              (y + h) - extents.height / 4);

	if (deliriumUIWidgets[widgetNumber].hover) {
		cairo_set_source_rgba(cr, 1, 1, 1, 1);;
	} else {
		cairo_set_source_rgba(cr, 1, 1, 1, 0.6);;
	}

	cairo_show_text(cr, deliriumUIWidgets[widgetNumber].label);

	cairo_reset_clip(cr);
}
