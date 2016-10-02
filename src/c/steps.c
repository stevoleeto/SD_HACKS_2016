#include <pebble.h>
#include "steps.h"
#include "storage.h"


void getNumStepsAtOpen(){
  HealthMetric metric = HealthMetricStepCount;
  time_t start = time_start_of_today();
  time_t end = time(NULL);
  
  // Check the metric has data available for today
  HealthServiceAccessibilityMask mask = health_service_metric_accessible(metric, start, end);
  
  if(mask & HealthServiceAccessibilityMaskAvailable) {
    // Data is available!
    APP_LOG(APP_LOG_LEVEL_INFO, "Steps today: %d", (int)health_service_sum_today(metric));
    stepsToday = (int)health_service_sum_today(metric);
    int newSteps = stepsToday - player.steps_today_last;
    character.steps += newSteps;
    player.steps_today_last = stepsToday;
    APP_LOG(APP_LOG_LEVEL_INFO, "The player has done %d steps since last using the app", newSteps);
  } else {
    // No data recorded yet today
    APP_LOG(APP_LOG_LEVEL_ERROR, "Data unavailable!");
    stepsToday = 1;
    player.steps_today_last = 1;
  }
}

void updateSteps(){
  HealthMetric metric = HealthMetricStepCount;
  stepsToday = (int)health_service_sum_today(metric);
  int newSteps = stepsToday - player.steps_today_last;
  character.steps += newSteps;
  player.steps_today_last = stepsToday;
  APP_LOG(APP_LOG_LEVEL_INFO, "The player walked %d steps while playing the app", newSteps);
}