#include <pebble.h>
#include "steps.h"
#include "storage.h"
#include "home.h"


void health_handler(HealthEventType event, void *context) {
  updateSteps();
  updateNumSteps();
}

void handle_init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Starting App");
  loadStorage();
  getNumStepsAtOpen();
  show_home();
  if(!health_service_events_subscribe(health_handler, NULL)) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
  }
}

void handle_deinit(void) {
  hide_home();
  saveStorage();
  APP_LOG(APP_LOG_LEVEL_INFO, "Stopping App");
}

int main(void) {
	handle_init();
	app_event_loop();
	handle_deinit();
}
