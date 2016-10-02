#include <pebble.h>
#include "steps.h"
#include "storage.h"

void handle_init(void) {
	APP_LOG(APP_LOG_LEVEL_INFO, "Starting App");
  loadStorage();
  getNumStepsAtOpen();
}

void handle_deinit(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Stopping App");
  saveStorage();
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}