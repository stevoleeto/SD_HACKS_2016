#include <pebble.h>
#include "steps.h"
#include "home.h"
#include "sprites.h"
#include "exp_bar.h"

// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY

static GFont s_res_roboto_condensed_21;
static Layer * main_layer;
static TextLayer * steps_walked_layer;
static BitmapLayer * pebblim_layer;
static Layer * menu_layer;
static TextLayer * menu_text_layer;
static ExpBar * exp_bar;

char updateStepsBuffer[32];
char updateLevelBuffer[32];

char * iToA(int num) {
  if(num == 0) return "0";
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
  snprintf(updateStepsBuffer, 32, "%d steps", getTotalUserSteps());
  text_layer_set_text(steps_walked_layer, updateStepsBuffer);
}

void updateExpBarProgress(int newPercent) {
  if(newPercent < 0 || newPercent > 100) return;
  exp_bar_set_progress(exp_bar, newPercent);
}

void updateLevelInt(int newLevel) {
  text_layer_set_text(menu_text_layer, strcat(iToA(newLevel), " - Pebblim"));
}

void updateLevel() {
  snprintf(updateLevelBuffer, 32, "Pebblim - %d", getCharacterLevel());
  text_layer_set_text(menu_text_layer, updateLevelBuffer);
}

static void initialise_ui(void) {
  s_window = window_create();
  pebblim = createPebblim(42, 53);
  window_set_background_color(s_window, PBL_IF_COLOR_ELSE(GColorWhite, GColorWhite));
  #ifndef PBL_SDK_3
    window_set_fullscreen(s_window, true);
  #endif

  s_res_roboto_condensed_21 = fonts_get_system_font(FONT_KEY_ROBOTO_CONDENSED_21);

  // main_layer
  main_layer = layer_create(GRect(0, 0, 144, 168));
  layer_add_child(window_get_root_layer(s_window), (Layer *)main_layer);

  // steps_walked_layer
  steps_walked_layer = text_layer_create(GRect(0, 0, 144, 24));
  updateNumSteps();
  text_layer_set_text_alignment(steps_walked_layer, GTextAlignmentCenter);
  text_layer_set_font(steps_walked_layer, s_res_roboto_condensed_21);
  layer_add_child(main_layer, (Layer *) steps_walked_layer);

  APP_LOG(APP_LOG_LEVEL_INFO, "updating sprites");
  for (int i = 0; i < MAX_SPRITES; i++) {
     if (sprites[i] != 0){
       APP_LOG(APP_LOG_LEVEL_INFO, "updated sprite %d", i);
       updateSprite(i);
       APP_LOG(APP_LOG_LEVEL_INFO, "drawing sprites lelz %d",i);
       drawSprite(i,s_window);
     }
  }

  // pebblim_layer
  pebblim_layer = bitmap_layer_create(GRect(0, 24, 144, 120));
  layer_add_child(main_layer, (Layer *) pebblim_layer);

  // exp_bar
  exp_bar = exp_bar_create(GRect(20, 134, 104, 5));
  exp_bar_set_corner_radius(exp_bar, 2);
  exp_bar_set_foreground_color(exp_bar, GColorDarkCandyAppleRed);
  exp_bar_set_background_color(exp_bar, GColorCobaltBlue);
  layer_add_child(main_layer, (Layer *) exp_bar);

  // menu_layer
  menu_layer = layer_create(GRect(0, 144, 144, 24));
  layer_add_child(main_layer, (Layer *) menu_layer);

  // menu_text_layer
  menu_text_layer = text_layer_create(GRect(0, 0, 144, 24));
  text_layer_set_text(menu_text_layer, "Plebbim");
  updateLevel();
  text_layer_set_text_alignment(menu_text_layer, GTextAlignmentCenter);
  text_layer_set_font(menu_text_layer, s_res_roboto_condensed_21);
  layer_add_child(menu_layer, (Layer *) menu_text_layer);
}

static void destroy_ui(void) {
  text_layer_destroy(steps_walked_layer);
  bitmap_layer_destroy(pebblim_layer);
  text_layer_destroy(menu_text_layer);
  layer_destroy(menu_layer);
  layer_destroy(main_layer);
  window_destroy(s_window);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  APP_LOG(APP_LOG_LEVEL_INFO, "clearing out sprites");
  for (int i = 0; i < MAX_SPRITES; i++) {
    destroySprite(i);
  }
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
