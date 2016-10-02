#include <pebble.h>
#include "storage.h"

uint32_t key = 0;
int num_items = 0;

#define USER_CHARACTER 0

void initStorage(){
  if (persist_exists(key)) {
    // Read persisted value
    num_items = persist_read_int(key);
  } else {
    // Choose a default value
    num_items = 10;

    // Remember the default value until the user chooses their own value
    persist_write_int(key, num_items);
  }
}