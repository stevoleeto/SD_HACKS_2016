#pragma once

struct Characters {
  int chosen;
  int steps;
  int level;
} character;

struct Players{
  int steps_today_last;
  int steps_best;
} player;

void loadStorage();
void saveStorage();