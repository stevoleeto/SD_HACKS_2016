#include <pebble.h>
#include "sprites.h"
#define MAX_SPRITES 32

void initSprites() {
  int i = 0;
  for (; i < MAX_SPRITES; i++) {
    sprites[i] = 0;
  }
};

int createSprite(int x, int y, int w, int h, uint32_t image) {
  struct Sprite* sp = 0;
  int index = 0;
  bool done = false;
  
  for (; index < 32 && !done; index++) {
    if (sprites[index] == 0) {
      sprites[index] = malloc(sizeof(struct Sprite)); 
      sp = sprites[index];
      done = true;
    }
  }
  index--;
  
  if (!done) {
    return -1;
  }
  
  sp->imageIndex = gbitmap_create_with_resource(image);
  sp->visible = true;
  sp->x = x;
  sp->y = y;
  sp->width = w;
  sp->height = h;
  sp->vspeed = 0.0;
  sp->hspeed = 0.0;
  sp->xpos = (float)x;
  sp->ypos = (float)y;
  sp->layer = 0;
  
  return index;
};
void updateSprite(int index) {
  struct Sprite* sp = sprites[index];
  
  bitmap_layer_destroy(sp->layer);
  
  sp->xpos += sp->hspeed;
  sp->ypos -= sp->vspeed;
  sp->x = (int)(sp->xpos);
  sp->y = (int)(sp->ypos);
  sp->layer = bitmap_layer_create(GRect(sp->x,sp->y,sp->width,sp->height));
};

void destroySprite(int index) {
  gbitmap_destroy(sprites[index]->imageIndex);
  free(sprites[index]);
  sprites[index] = 0;
};

void drawSprite(int index, Window* window) {
  struct Sprite* sp = sprites[index];
  if (sp->visible == true) {
    bitmap_layer_set_compositing_mode(sp->layer,GCompOpSet);
    bitmap_layer_set_bitmap(sp->layer,sp->imageIndex);
    layer_add_child(window_get_root_layer(window),bitmap_layer_get_layer(sp->layer));
  }
};

//Pebblim functions


struct Pebblim* createPebblim(int x, int y) {
  struct Pebblim* peb = malloc(sizeof(struct Pebblim));
  
  struct Part* pt;
  int xorigin, yorigin;
//body  
  peb->body = malloc(sizeof(struct Part));
  pt = peb->body;
  
  pt->parent = 0;
  pt->sprite = createSprite(42,53,58,45,RESOURCE_ID_SPRITE_TOPAZ_BODY);
  pt->xdist = (char)0;
  pt->ydist = (char)0;
//left eye
  peb->eyeleft = malloc(sizeof(struct Part));
  pt = peb->eyeleft;

  pt->parent = peb->body;  
  pt->xdist = (char)1;
  pt->ydist = (char)8;
  xorigin = (int)((sprites[(pt->parent)->sprite])->x)+(int)(pt->xdist);
  yorigin = sprites[pt->parent->sprite]->y+pt->ydist;
  pt->sprite = createSprite(xorigin,yorigin,14,13,RESOURCE_ID_SPRITE_TOPAZ_EYELEFT);
//right eye
  peb->eyeright = malloc(sizeof(struct Part));
  pt = peb->eyeright;
  
  pt->parent = peb->body;
  pt->xdist = (char)22;
  pt->ydist = (char)7;
  xorigin = sprites[pt->parent->sprite]->x+pt->xdist;
  yorigin = sprites[pt->parent->sprite]->y+pt->ydist;
  pt->sprite = createSprite(xorigin,yorigin,14,13,RESOURCE_ID_SPRITE_TOPAZ_EYERIGHT);
//mouth
  peb->mouth = malloc(sizeof(struct Part));
  pt = peb->mouth;
  
  pt->parent = peb->body;
  pt->xdist = (char)13;
  pt->ydist = (char)24;
  xorigin = sprites[pt->parent->sprite]->x+pt->xdist;
  yorigin = sprites[pt->parent->sprite]->y+pt->ydist;
  pt->sprite = createSprite(xorigin,yorigin,13,7,RESOURCE_ID_SPRITE_TOPAZ_MOUTH);
  
//tail
  peb->extra[0] = malloc(sizeof(struct Part));
  pt = peb->extra[0];
  
  pt->parent = peb->body;
  pt->xdist = (char)40;
  pt->ydist = (char)40;
  xorigin = sprites[pt->parent->sprite]->x+pt->xdist;
  yorigin = sprites[pt->parent->sprite]->y+pt->ydist;
  pt->sprite = createSprite(xorigin,yorigin,19,15,RESOURCE_ID_SPRITE_TOPAZ_TAIL);

  return peb;
};

void updatePebblim(struct Pebblim* peb) {
  //TODO holy crap this is going to be a lot of code
};
void destroyPebblim(struct Pebblim* peb) {
  
  destroySprite(peb->body->sprite);
  destroySprite(peb->eyeleft->sprite);
  destroySprite(peb->eyeright->sprite);
  destroySprite(peb->mouth->sprite);
  destroySprite(peb->arm->sprite);
  destroySprite(peb->legleft->sprite);
  destroySprite(peb->legright->sprite);
  
  free(peb->body);
  free(peb->eyeleft);
  free(peb->eyeright);
  free(peb->mouth);
  free(peb->arm);
  free(peb->legleft);
  free(peb->legright);
  for (int i = 0; i < 5; i++) {
    free(peb->extra[i]);
  }
  free(peb);
  
};