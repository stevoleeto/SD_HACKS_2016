#include <pebble.h>

void handle_init(void) {
	APP_LOG(APP_LOG_LEVEL_DEBUG, "Handling Init");
}

void handle_deinit(void) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Handling Deinit");
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}