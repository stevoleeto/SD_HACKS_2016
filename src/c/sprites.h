#pragma once
#include <pebble.h>

#define MAX_SPRITES 32

struct Part {

  struct Part* parent;
  int sprite;
  char xdist;
  char ydist;

};

struct Pebblim {

  struct Part* body;
  struct Part* eyeleft;
  struct Part* eyeright;
  struct Part* mouth;
  struct Part* arm;
  struct Part* legleft;
  struct Part* legright;
  struct Part* extra[5];

};

struct Sprite {

  char x;
  char y;
  char width;
  char height;
  int frame;
  float xpos;
  float ypos;
  float vspeed;
  float hspeed;
  bool visible;
  BitmapLayer* layer;
  GBitmap *imageIndex;

};

struct Sprite* sprites[MAX_SPRITES];
struct Pebblim* pebblim;

void initSprites();
void destroySprites();
int createSprite(int x, int y, int w, int h, uint32_t image);
void updateSprite(int index);
void destroySprite(int index);
void drawSprite(int index, Window* window);

// Pebblim functions
struct Pebblim* createPebblim(int x, int y);
void updatePebblim();
void destroyPebblim(struct Pebblim* peb);
