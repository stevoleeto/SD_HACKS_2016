#include <pebble.h>
#include "exp_bar.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

typedef struct {
  int16_t exp_percent;
  int16_t corner_radius;
  GColor foreground_color;
  GColor background_color;
} ExpBarData;

static int16_t scale_exp_bar_width_px(unsigned int exp_percent, int16_t rect_width_px) {
  return ((exp_percent * (rect_width_px)) / 100);
}

static void exp_bar_update_proc(ExpBar * exp_bar_layer, GContext* ctx) {
  ExpBarData * data = (ExpBarData *) layer_get_data(exp_bar_layer);
  GRect bounds = layer_get_bounds(exp_bar_layer);

  int16_t exp_bar_width_px = scale_exp_bar_width_px(data->exp_percent, bounds.size.w);
  GRect exp_bar = GRect(bounds.origin.x, 0, exp_bar_width_px, 5);

  graphics_context_set_fill_color(ctx, data->foreground_color);
  graphics_fill_rect(ctx, bounds, data->corner_radius, GCornersAll);
  graphics_context_set_fill_color(ctx, data->background_color);
  graphics_fill_rect(ctx, exp_bar, data->corner_radius, GCornersAll);

#ifdef PBL_PLATFORM_APLITE
  graphics_context_set_stroke_color(ctx, data->background_color);
  graphics_draw_rect(ctx, exp_bar);
#endif
}

ExpBar * exp_bar_create(GRect frame) {
  ExpBar * exp_bar = layer_create_with_data(frame, sizeof(ExpBarData));
  layer_set_update_proc(exp_bar, exp_bar_update_proc);
  layer_mark_dirty(exp_bar);

  ExpBarData *data = (ExpBarData *)layer_get_data(exp_bar);
  data->exp_percent = 0;
  data->corner_radius = 1;
  data->foreground_color = GColorBlack;
  data->background_color = GColorWhite;

  return exp_bar;
}

void exp_bar_destroy(ExpBar * exp_bar) {
  if (exp_bar) {
    layer_destroy(exp_bar);
  }
}

void exp_bar_increment_progress(ExpBar * exp_bar, int16_t experience) {
  ExpBarData * data = (ExpBarData *) layer_get_data(exp_bar);
  data->exp_percent = MIN(100, data->exp_percent + experience);
  layer_mark_dirty(exp_bar);
}

void exp_bar_set_progress(ExpBar * exp_bar, int16_t exp_percent) {
  ExpBarData * data = (ExpBarData *) layer_get_data(exp_bar);
  data->exp_percent = MIN(100, exp_percent);
  layer_mark_dirty(exp_bar);
}

void exp_bar_set_corner_radius(ExpBar * exp_bar, uint16_t corner_radius) {
  ExpBarData * data = (ExpBarData *) layer_get_data(exp_bar);
  data->corner_radius = corner_radius;
  layer_mark_dirty(exp_bar);
}

void exp_bar_set_foreground_color(ExpBar * exp_bar, GColor color) {
  ExpBarData * data = (ExpBarData *) layer_get_data(exp_bar);
  data->foreground_color = color;
  layer_mark_dirty(exp_bar);
}

void exp_bar_set_background_color(ExpBar * exp_bar, GColor color) {
  ExpBarData * data = (ExpBarData *) layer_get_data(exp_bar);
  data->background_color = color;
  layer_mark_dirty(exp_bar);
}