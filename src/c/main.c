#include <pebble.h>
#include "steps.h"
#include "storage.h"
#include "home.h"

#define LEVEL_GOAL 100


void health_handler(HealthEventType event, void *context) {
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Handling step change!");
  updateSteps();
  updateNumSteps();
//   updateExpBarProgress((int) ((getTotalUserSteps() / LEVEL_GOAL) * 100) % 100);
  updateExpBarProgress(getTotalUserSteps() % 100);
  if((getTotalUserSteps() / LEVEL_GOAL) >  character.level) {
    character.level = getTotalUserSteps() / LEVEL_GOAL;
    updateLevelInt(character.level);
  }
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
