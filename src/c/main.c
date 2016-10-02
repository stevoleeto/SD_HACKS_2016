#include <pebble.h>
#include "steps.h"
#include "storage.h"
#include "home.h"


void handle_init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Starting App");
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
