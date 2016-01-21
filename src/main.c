#include <pebble.h>
#include "main.h"

static Window *window;
static Layer *bg_layer;
static TextLayer *time_layer;
static TextLayer *airbus_layer;
static GFont airbus_font;

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
  
  /*
	//----------------------------------------------------------------
	//Corners of steering box

	graphics_context_set_fill_color(ctx, GColorPastelYellow);
	graphics_context_set_stroke_color(ctx, GColorBlack);
	graphics_context_set_stroke_width(ctx, 1);

	graphics_fill_rect(ctx, GRect(15, 15, 14, 5), 0, GCornerNone);
	graphics_fill_rect(ctx, GRect(15, 15, 5, 14), 0, GCornerNone);
	graphics_draw_rect(ctx, GRect(15, 15, 14, 5));
	graphics_draw_rect(ctx, GRect(15, 15, 5, 14));
	
	graphics_fill_rect(ctx, GRect(115, 15, 14, 5), 0, GCornerNone);
	graphics_fill_rect(ctx, GRect(124, 15, 5, 14), 0, GCornerNone);
	graphics_draw_rect(ctx, GRect(115, 15, 14, 5));
	graphics_draw_rect(ctx, GRect(124, 15, 5, 14));

	graphics_fill_rect(ctx, GRect(15, 153, 14, 5), 0, GCornerNone);
	graphics_fill_rect(ctx, GRect(15, 144, 5, 14), 0, GCornerNone);
	graphics_draw_rect(ctx, GRect(15, 153, 14, 5));
	graphics_draw_rect(ctx, GRect(15, 144, 5, 14));

	graphics_fill_rect(ctx, GRect(115, 153, 14, 5), 0, GCornerNone);
	graphics_fill_rect(ctx, GRect(124, 144, 5, 14), 0, GCornerNone);
	graphics_draw_rect(ctx, GRect(115, 153, 14, 5));
	graphics_draw_rect(ctx, GRect(124, 144, 5, 14));

  */
}

static void update_time() {
	time_t temp = time(NULL);
	struct tm *t = localtime(&temp);

	static char buffer[] = "000000";
  
  strftime(buffer, sizeof(buffer), "%H%M%S", t);
  
  text_layer_set_text(time_layer, buffer);
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  update_time();
}

static void main_window_load() {
	airbus_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_AIRBUS_18));

	bg_layer = layer_create(GRect(0, 0, 144, 168));
	layer_set_update_proc(bg_layer, bg_create_proc);
	layer_add_child(window_get_root_layer(window), bg_layer);
  
  airbus_layer = text_layer_create(GRect(0, 0, 144, 168));
  text_layer_set_text_color(airbus_layer, GColorYellow);
  text_layer_set_background_color(airbus_layer, GColorClear);
  text_layer_set_text_alignment(airbus_layer, GTextAlignmentCenter);
  text_layer_set_font(airbus_layer, airbus_font);
  text_layer_set_text(airbus_layer, "Airbus @");
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(airbus_layer));

	time_layer = text_layer_create(GRect(0, 146, 144, 24));
	text_layer_set_text_color(time_layer, GColorYellow);
	text_layer_set_background_color(time_layer, GColorClear);
	text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
	text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_18_BOLD));
	text_layer_set_text(time_layer, "000000");
	layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_layer));
}

static void main_window_unload() {
	text_layer_destroy(time_layer);
	layer_destroy(bg_layer);
  text_layer_destroy(airbus_layer);
}

static void init() {
	window = window_create();
  
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);

	window_set_window_handlers(window, (WindowHandlers) {
		.load = main_window_load,
		.unload = main_window_unload,
	});

	window_stack_push(window, true);
  
  update_time();
}

static void deinit() {
	window_destroy(window);
}

int main(void) {
	init();
	app_event_loop();
	deinit();
}
