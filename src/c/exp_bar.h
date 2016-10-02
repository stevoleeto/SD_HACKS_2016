#pragma once

#include <pebble.h>

typedef Layer ExpBar;

ExpBar * exp_bar_create(GRect frame);
void exp_bar_destroy(ExpBar * exp_bar);
void exp_bar_increment_progress(ExpBar * exp_bar, int16_t progress);
void exp_bar_set_progress(ExpBar * exp_bar, int16_t progress_percent);
void exp_bar_set_corner_radius(ExpBar * exp_bar, uint16_t corner_radius);
void exp_bar_set_foreground_color(ExpBar * exp_bar, GColor color);
void exp_bar_set_background_color(ExpBar * exp_bar, GColor color);