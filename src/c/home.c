#include <pebble.h>
#include "steps.h"
#include "home.h"
#include "exp_bar.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window * s_window;
static GFont s_res_roboto_condensed_21;
static GBitmap * s_res_sprite_topaz_eyeleft;
static Layer * main_layer;
static TextLayer * steps_walked_layer;
static BitmapLayer * pebblim_layer;
static Layer * menu_layer;
static TextLayer * menu_text_layer;
static ExpBar * exp_bar;

char * iToA(int num) {
  static char buff[20] = {};
  int i = 0, temp_num = num, length = 0;
  char *string = buff;
  
  if(num >= 0) { //See NOTE
    // count how many characters in the number
    while(temp_num) {
      temp_num /= 10;
      length++;
    }
    // assign the number to the buffer starting at the end of the 
    // number and going to the begining since we are doing the
    // integer to character conversion on the last number in the
    // sequence
    for(i = 0; i < length; i++) {
      buff[(length-1)-i] = '0' + (num % 10);
      num /= 10;
    }
    buff[i] = '\0'; // can't forget the null byte to properly end our string
  } else {
    return "Unsupported Number";
  }
  
  return string;
}

void updateNumSteps() {
  text_layer_set_text(steps_walked_layer, strcat(iToA(stepsToday), " steps"));
}

void updateExpBarProgress(int newPercent) {
  if(newPercent < 0 || newPercent > 100) return;
  exp_bar_set_progress(exp_bar, newPercent);
}

void updateLevel() {
  int level = getCharacterLevel();
  text_layer_set_text(menu_text_layer, strcat("Pebblim - lvl. ", iToA(level)));
}

static void initialise_ui(void) {
  s_window = window_create();
  window_set_background_color(s_window, PBL_IF_COLOR_ELSE(GColorFolly, GColorWhite));
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif
  
  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);
  s_res_sprite_topaz_eyeleft = gbitmap_create_with_resource(RESOURCE_ID_SPRITE_TOPAZ_EYELEFT);
  
  // main_layer
  main_layer = layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(s_window), (Layer *)main_layer);
  
  // steps_walked_layer
  steps_walked_layer = text_layer_create(GRect(0, 0, 144, 24));
  updateNumSteps();
  text_layer_set_text_alignment(steps_walked_layer, GTextAlignmentCenter);
  text_layer_set_font(steps_walked_layer, s_res_roboto_condensed_21);
  layer_add_child(window_get_root_layer(s_window), (Layer *) steps_walked_layer);
  
  // pebblim_layer
  pebblim_layer = bitmap_layer_create(GRect(0, 24, 144, 120));
  layer_add_child(window_get_root_layer(s_window), (Layer *) pebblim_layer);
  
  // exp_bar
  exp_bar = exp_bar_create(GRect(20, 134, 104, 5));
  
  exp_bar_set_corner_radius(exp_bar, 2);
  exp_bar_set_foreground_color(exp_bar, GColorDarkCandyAppleRed);
  exp_bar_set_background_color(exp_bar, GColorCobaltBlue);
  layer_add_child(window_get_root_layer(s_window), (Layer *) exp_bar);
  
  // menu_layer
  menu_layer = layer_create(GRect(0, 144, 144, 24));
  layer_add_child(window_get_root_layer(s_window), (Layer *) menu_layer);
  
  // menu_text_layer
  menu_text_layer = text_layer_create(GRect(0, 0, 144, 24));
  updateLevel();
  text_layer_set_text_alignment(menu_text_layer, GTextAlignmentCenter);
  text_layer_set_font(steps_walked_layer, s_res_roboto_condensed_21);
  layer_add_child(menu_layer, (Layer *) menu_text_layer);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  layer_destroy(main_layer);
  text_layer_destroy(steps_walked_layer);
  bitmap_layer_destroy(pebblim_layer);
  layer_destroy(menu_layer);
  gbitmap_destroy(s_res_sprite_topaz_eyeleft);
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
