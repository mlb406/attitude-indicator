#include <pebble.h>
#include "main.h"

static Window *window;
static Layer *bg_layer;

static void bg_create_proc(Layer *layer, GContext *ctx) {
	graphics_context_set_fill_color(ctx, GColorCobaltBlue);
	
	graphics_fill_rect(ctx, GRect(0, 0, 144, 84), 0, GCornersAll);

	graphics_context_set_fill_color(ctx, GColorWindsorTan);

	graphics_fill_rect(ctx, GRect(0, 84, 144, 84), 0, GCornersAll);

	//-------------------------------------------------------------
	//Lines

	graphics_context_set_stroke_color(ctx, GColorWhite);
	graphics_context_set_antialiased(ctx, false);
	graphics_context_set_stroke_width(ctx, 3);

	for (int i = 0; i < 6; i++) {
		graphics_draw_line(ctx, GPoint(line_points_left_x[i], line_points_left_y[i]), GPoint(line_points_right_x[i], line_points_right_y[i]));
	}

	//----------------------------------------------------------------
	//Corners of steering box

	graphics_context_set_fill_color(ctx, GColorPastelYellow);
	graphics_context_set_stroke_color(ctx, GColorBlack);
	graphics_context_set_stroke_width(ctx, 1);

	graphics_fill_rect(ctx, GRect(15, 7, 14, 5), 0, GCornerNone);
	graphics_fill_rect(ctx, GRect(15, 7, 5, 14), 0, GCornerNone);
	graphics_draw_rect(ctx, GRect(15, 7, 14, 5));
	graphics_draw_rect(ctx, GRect(15, 7, 5, 14));
	
}

static void main_window_load() {
	bg_layer = layer_create(GRect(0, 0, 144, 168));
	layer_set_update_proc(bg_layer, bg_create_proc);
	layer_add_child(window_get_root_layer(window), bg_layer);

}

static void main_window_unload() {
	layer_destroy(bg_layer);
}

static void init() {
	window = window_create();

	window_set_window_handlers(window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});

	window_stack_push(window, true);
}

static void deinit() {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
