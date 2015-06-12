/*
  Copyright 2015 Nick Bailey
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <cairo/cairo.h>

#include "lv2/lv2plug.in/ns/extensions/ui/ui.h"
#include "pugl/pugl.h"
#include "deliriumUI/deliriumUI.h"

#define minaton_UI_URI "http://nickbailey.co.nr/plugins/minaton#ui"

typedef struct {
	PuglView*            view;
	LV2UI_Write_Function write;
	LV2UI_Controller     controller;
	int                  width;
	int                  height;
	float                brightness;
	bool                 exit;
} minatonUI;

static void
onReshape(PuglView* view, int width, int height)
{
	setDeliriumUICurrentWindowSize(width, height);
}


static void
onDisplay(PuglView* view)
{

	cairo_t* cr = puglGetContext(view);

	/* Set surface to opaque color (r, g, b) */
	cairo_set_source_rgb (cr, 0.1,0,0);
	cairo_paint (cr);

	displayAllDeliriumUIWidgets(cr);
}

static void
onKeyboard(PuglView* view, bool press, uint32_t key)
{
	if (press) {
		fprintf(stderr, "Keyboard press %c\n", key);
	} else {
		fprintf(stderr, "Keyboard release %c\n", key);
	}
}

static void
onMotion(PuglView* view, int x, int y)
{
	// fprintf(stderr, "Motion: %d,%d\n", x, y);
	isMouseOverDeliriumUIWidget(x, y);
}

static void
onMouse(PuglView* view, int button, bool press, int x, int y)
{
	fprintf(stderr, "Mouse %d %s at %d,%d\n",
	        button, press ? "down" : "up", x, y);

	if (press == true && button == 1)
		hasMouseClickedDeliriumUIWidget(x, y);
		else
					hasMouseClickedDeliriumUIWidget(-1,-1);

}

static void
onScroll(PuglView* view, int x, int y, float dx, float dy)
{
	fprintf(stderr, "Scroll %f %f\n", dx, dy);
}


static LV2UI_Handle
instantiate(const LV2UI_Descriptor*   descriptor,
            const char*               plugin_uri,
            const char*               bundle_path,
            LV2UI_Write_Function      write_function,
            LV2UI_Controller          controller,
            LV2UI_Widget*             widget,
            const LV2_Feature* const* features)
{
	minatonUI* self = (minatonUI*)malloc(sizeof(minatonUI));
	if (!self) {
		return NULL;
	}

	self->write      = write_function;
	self->controller = controller;
	self->width      = 480;
	self->height     = 256;
	self->exit       = false;

	
	setDeliriumUIGridSize(self->width, self->height, 10, 10);

	// Get parent window and resize API from features
	PuglNativeWindow parent = 0;
	LV2UI_Resize*    resize = NULL;
	for (int i = 0; features && features[i]; ++i) {
		printf("Feature %s\n", features[i]->URI );
		if (!strcmp(features[i]->URI, LV2_UI__parent)) {
			parent = (PuglNativeWindow)features[i]->data;
		} else if (!strcmp(features[i]->URI, LV2_UI__resize)) {
			resize = (LV2UI_Resize*)features[i]->data;
		}
	}

	if (!parent) {
		fprintf(stderr, "error: minaton_ui: No parent window provided.\n");
		free(self);
		return NULL;
	}

	 addDeliriumUIWidget(0,0,3,1,"Test");
	 addDeliriumUIWidget(0,1,3,1,"Frog");
	 addDeliriumUIWidget(0,2,3,1,"Abracadabra");

	 addDeliriumUIWidget(4,0,1,1,"A");
	 addDeliriumUIWidget(5,0,1,1,"B");
	 addDeliriumUIWidget(6,0,1,1,"C");
	 addDeliriumUIWidget(7,0,1,1,"D");
	 addDeliriumUIWidget(8,0,1,1,"E");

	 addDeliriumUIWidget(4,2,4,4,"Overlap 1");
	 addDeliriumUIWidget(6,5,4,4,"Overlap 2");

	// Set up pugl window

	self->view = puglInit(NULL, NULL);
	puglInitWindowParent(self->view, parent);
	puglInitWindowSize(self->view, 1280,800);
	puglInitResizable(self->view, true);
	puglInitContextType(self->view, PUGL_CAIRO);
	puglIgnoreKeyRepeat(self->view, false);

	puglSetDisplayFunc(self->view, onDisplay);
	puglSetReshapeFunc(self->view, onReshape);
	puglSetKeyboardFunc(self->view, onKeyboard);
	puglSetMotionFunc(self->view, onMotion);
	puglSetMouseFunc(self->view, onMouse);
	puglSetScrollFunc(self->view, onScroll);

	puglCreateWindow(self->view, "minaton");
	puglSetHandle(self->view, self);
	puglShowWindow(self->view);

	if (resize) {
		resize->ui_resize(resize->handle, self->width, self->height);
	}

	*widget = (void*)puglGetNativeWindow(self->view);
	return self;
}

static int
idle(LV2UI_Handle handle)
{
	minatonUI* self = (minatonUI*)handle;

	// Silly pulsing animation to check that idle handler is working
	self->brightness = fmod(self->brightness + 0.01, 1.0);
	puglPostRedisplay(self->view);
	puglProcessEvents(self->view);

	return 0;
}

static void
cleanup(LV2UI_Handle handle)
{

	minatonUI* self = (minatonUI*)handle;
	self->exit = true;

	fprintf(stderr, "\nMinaton shutting down........\n");

	puglDestroy(self->view);
	free(self);

}

static void
port_event(LV2UI_Handle handle,
           uint32_t     port_index,
           uint32_t     buffer_size,
           uint32_t     format,
           const void*  buffer)
{
	minatonUI* self = (minatonUI*)handle;
}

static const LV2UI_Idle_Interface idle_iface = { idle };

static const void*
extension_data(const char* uri)
{
	if (!strcmp(uri, LV2_UI__idleInterface)) {
		return &idle_iface;
	}
	return NULL;
}

static const LV2UI_Descriptor descriptor = {
	minaton_UI_URI,
	instantiate,
	cleanup,
	port_event,
	extension_data
};

LV2_SYMBOL_EXPORT
const LV2UI_Descriptor*
lv2ui_descriptor(uint32_t index)
{
	switch (index) {
	case 0:
		return &descriptor;
	default:
		return NULL;
	}
}
