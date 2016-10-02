#include <pebble.h>
#include "steps.h"
#include "home.h"

// static Window * s_main_window;
// static BitmapLayer * pebblim_layer;
// static GBitmap * pebblim_bitmap = NULL;
// struct sprites {
//   char start_x;
//   char start_y;
//   char bound_x;
//   char bound_y;
//   char pebblim_id;
// };

// static const uint32_t PEBBLIMS[] = {
//   RESOURCE_ID_SPRITE_TOPAZ_OG,  // 0
//   RESOURCE_ID_SPRITE_TOPAZ_OGT  // 1
// };

// static void window_load(Window * window) {
//   APP_LOG(APP_LOG_LEVEL_DEBUG, "Entering window_load");
//   Layer * main_layer = window_get_root_layer(window);
//   GRect bounds = layer_get_bounds(main_layer);
  
//   pebblim_layer = bitmap_layer_create(GRect(0, 0, bounds.size.w, bounds.size.h));
//   layer_add_child(main_layer, bitmap_layer_get_layer(pebblim_layer));
  
//   if (pebblim_bitmap) {
//     gbitmap_destroy(pebblim_bitmap);
//   }
  
//   pebblim_bitmap = gbitmap_create_with_resource(PEBBLIMS[1]);
//   bitmap_layer_set_compositing_mode(pebblim_layer, GCompOpSet);
//   bitmap_layer_set_bitmap(pebblim_layer, pebblim_bitmap);
// };

// static void window_unload(Window * window) {
//   APP_LOG(APP_LOG_LEVEL_DEBUG, "Entering window_unload");
// }

void handle_init(void) {
	APP_LOG(APP_LOG_LEVEL_INFO, "Starting App");
  getNumAtOpenSteps();
  show_home();
}

void handle_deinit(void) {
  hide_home();
  APP_LOG(APP_LOG_LEVEL_INFO, "Stopping App");
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}