
#include "deliriumUI.h"
#include <math.h>
#define M_PI 3.14159265358979323846264338327

void displayDiliriumUIFader(deliriumUI* deliriumUI_window, cairo_t* cr, int widgetNumber)
{
	deliriumUIWidget* deliriumUIWidgets = deliriumUI_window->deliriumUIWidgets;

	int x = deliriumUIWidgets[widgetNumber].x * deliriumUI_window->widgetWidth;
	int y = deliriumUIWidgets[widgetNumber].y * deliriumUI_window->widgetHeight;
	int w = deliriumUIWidgets[widgetNumber].w * deliriumUI_window->widgetWidth;
	int h = deliriumUIWidgets[widgetNumber].h * deliriumUI_window->widgetHeight;

	float value = 1; // deliriumUIWidgets[widgetNumber].value;

	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_rectangle(cr, x, y, w, h);
	cairo_clip(cr);

	// Draw label
	cairo_text_extents_t extents;
	cairo_set_font_size(cr, h / 5);
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

	y -= (h/8);
	float fader_height = h - (h/8);

	float value_to_ypixel = fader_height*value;

	// ------------------------------------------------------------------

	// draw vertical scale bars
	cairo_set_line_width(cr, 0.4);
	cairo_set_source_rgba(cr, 0.9,0.9,0.9,1.0);

	for (int yl=0; yl<fader_height; yl+=(fader_height/10))
	{
		cairo_move_to(cr, x+(w/3), y+yl);
	 	cairo_line_to(cr, x+(w-(w/3)), y+yl);
	    	cairo_stroke(cr);
	}

	// draw vertical grey line down the middle
	cairo_set_line_width(cr, 4);
	cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
	cairo_move_to(cr, x+(w/2), y);
	cairo_line_to(cr, x+(w/2), y + fader_height);
	cairo_stroke(cr);

	// draw horizontal thin black line at fader_value height
	cairo_set_line_width(cr, fader_height/6);
	cairo_set_source_rgba(cr, 0.0,0.0,0.0,1.0);
	cairo_move_to(cr, x+(w/4), y+value_to_ypixel);
	cairo_line_to(cr, x+(w-(w/4)), y+value_to_ypixel);
	cairo_stroke(cr);

	// draw horizontal thick black line at fader_value height
	cairo_set_line_width(cr, fader_height/4);
	cairo_set_source_rgba(cr, 0.0,0.0,0.0,0.3);
	cairo_move_to(cr, x+(w/4), y+value_to_ypixel);
	cairo_line_to(cr, x+(w-(w/4)), y+value_to_ypixel + 1.1);
	cairo_stroke(cr);

	// set up grad
	cairo_pattern_t* pat;

	pat = cairo_pattern_create_linear(x+(w/4), y+value_to_ypixel, x+(w-(w/4)), y+value_to_ypixel );
	cairo_pattern_add_color_stop_rgba(pat, 0.0,0.2,0.2,0.2,1);
        cairo_pattern_add_color_stop_rgba(pat, 0.4,0.8,0.8,0.8,1);
        cairo_pattern_add_color_stop_rgba(pat, 1.0,0.4,0.4,0.4,1);

	// draw horizontal blue line at fader_value height
	cairo_set_line_width(cr, h/24);
	cairo_set_source(cr, pat);
	cairo_move_to(cr, x+(w/4), y+value_to_ypixel);
	cairo_line_to(cr, x+ (w-(w/4)), y+value_to_ypixel);
	cairo_stroke(cr);

	cairo_reset_clip(cr);
	cairo_pattern_destroy (pat);
}











