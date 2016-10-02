#include <pebble.h>
#include "storage.h"

#define USER_CHARACTER 0
#define STEPS_CHARACTER 1
#define LEVEL_CHARACTER 2
#define PLAYER_STEPS_TODAY_LAST 3
#define PLAYER_STEPS_BEST 4

void loadCharacter(){
  if (persist_exists(USER_CHARACTER)) {
    character.chosen = persist_read_int(USER_CHARACTER);
    APP_LOG(APP_LOG_LEVEL_INFO, "Loaded user character %d", character.chosen);

  } else {
    character.chosen = 0;
    persist_write_int(USER_CHARACTER, 0);
    APP_LOG(APP_LOG_LEVEL_ERROR, "Failed to load character");

  }
}

void loadCharacterSteps(){
  if (persist_exists(STEPS_CHARACTER)) {
    character.steps = persist_read_int(STEPS_CHARACTER);
    APP_LOG(APP_LOG_LEVEL_INFO, "Loaded user steps %d", character.steps);

  } else {
    character.steps = 0;
    persist_write_int(STEPS_CHARACTER, 0);
    APP_LOG(APP_LOG_LEVEL_ERROR, "Failed to load steps");

  }
}

void loadCharacterLevel(){
  if (persist_exists(LEVEL_CHARACTER)) {
    character.level = persist_read_int(LEVEL_CHARACTER);
    APP_LOG(APP_LOG_LEVEL_INFO, "Loaded user level %d", character.level);

  } else {
    character.level = 1;
    persist_write_int(LEVEL_CHARACTER, 1);
    APP_LOG(APP_LOG_LEVEL_ERROR, "Failed to load level");

  }
}

void loadPlayerTodayLast(){
  if (persist_exists(PLAYER_STEPS_TODAY_LAST)) {
    player.steps_today_last = persist_read_int(PLAYER_STEPS_TODAY_LAST);
    APP_LOG(APP_LOG_LEVEL_INFO, "Loaded player steps for today %d", player.steps_today_last);

  } else {
    player.steps_today_last = 0;
    persist_write_int(PLAYER_STEPS_TODAY_LAST, 0);
    APP_LOG(APP_LOG_LEVEL_ERROR, "Failed to load steps");

  }
}

void loadPlayerBest(){
  if (persist_exists(PLAYER_STEPS_BEST)) {
    player.steps_best = persist_read_int(PLAYER_STEPS_BEST);
    APP_LOG(APP_LOG_LEVEL_INFO, "Loaded best player steps %d", player.steps_best);

  } else {
    player.steps_best = 0;
    persist_write_int(PLAYER_STEPS_BEST, 0);
    APP_LOG(APP_LOG_LEVEL_ERROR, "Failed to load best");

  }
}

void loadStorage(){
  loadCharacter(); 
  loadCharacterSteps();
  loadCharacterLevel();
  loadPlayerTodayLast();
  loadPlayerBest();
}

void saveCharacter(){
  persist_write_int(USER_CHARACTER, character.chosen);
  persist_write_int(STEPS_CHARACTER, character.steps);
  persist_write_int(LEVEL_CHARACTER, character.level);
}

void savePlayer(){
  persist_write_int(PLAYER_STEPS_TODAY_LAST, player.steps_today_last);
  persist_write_int(PLAYER_STEPS_BEST, player.steps_best);
}

void saveStorage(){
  saveCharacter();
  savePlayer();
  APP_LOG(APP_LOG_LEVEL_INFO, "Saved Storage");
}