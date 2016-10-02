#include <pebble.h>
#include "steps.h"
#include "storage.h"
#include "home.h"
#include "sprites.h"


void health_handler(HealthEventType event, void *context) {
  updateSteps();
  updateNumSteps();
}

void handle_init(void) {
  APP_LOG(APP_LOG_LEVEL_INFO, "Starting App");
  initSprites();
  APP_LOG(APP_LOG_LEVEL_INFO, "Finished init sprites");
  loadStorage();
  getNumStepsAtOpen();
  APP_LOG(APP_LOG_LEVEL_INFO, "Starting show home");
  show_home();
  APP_LOG(APP_LOG_LEVEL_INFO, "Finished show home");
  if(!health_service_events_subscribe(health_handler, NULL)) {
    APP_LOG(APP_LOG_LEVEL_ERROR, "Health not available!");
  }
  app_timer_register(500, updatePebblim, NULL);
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
