#include <pebble.h>
#include "home.h"
#include "steps.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window * s_window;
static GFont s_res_roboto_condensed_21;
static GBitmap * s_res_sprite_topaz_ogt;
static Layer * main_layer;
static TextLayer * steps_walked_layer;
static BitmapLayer * pebblim_layer;
static Layer * menu_layer;

static void initialise_ui(void) {
  s_window = window_create();
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_sprite_topaz_ogt = gbitmap_create_with_resource(RESOURCE_ID_SPRITE_TOPAZ_OGT);
  // main
  main_layer = layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(s_window), (Layer *) main_layer);
  
  // steps_walked_layer
  steps_walked_layer = text_layer_create(GRect(0, 20, 144, 30));
  text_layer_set_background_color(steps_walked_layer, GColorClear);
  text_layer_set_text(steps_walked_layer, "427 steps");
  text_layer_set_text_alignment(steps_walked_layer, GTextAlignmentCenter);
  text_layer_set_font(steps_walked_layer, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *)steps_walked_layer);
  
  // pebblim_layer
  pebblim_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(pebblim_layer, s_res_sprite_topaz_ogt);
  layer_add_child(window_get_root_layer(s_window), (Layer *)pebblim_layer);
  
  // menu_layer
  menu_layer = layer_create(GRect(0, 148, 144, 20));
  layer_add_child(window_get_root_layer(s_window), (Layer *)menu_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  layer_destroy(main_layer);
  text_layer_destroy(steps_walked_layer);
  bitmap_layer_destroy(pebblim_layer);
  layer_destroy(menu_layer);
  gbitmap_destroy(s_res_sprite_topaz_ogt);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_home(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_home(void) {
  window_stack_remove(s_window, true);
}
