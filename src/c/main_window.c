#include <pebble.h>
#include "main_window.h"
#include "error_window.h"

Window *mainWindow;
MenuLayer *mainMenuLayer;

City cities[MAX_AMOUNT_OF_CITIES];
City currentCityToWrite;  

const char *conditions[] = {
  "Clear",
  "Clear",
  "Windy",
  "Cold",
  "Partly Cloudy",
  "Partly Cloudy",
  "Hazey",
  "Cloudy",
  "Rainy",
  "Snowy",
  "Hailing",
  "Cloudy",
  "Stormy",
  "Unknown Conditions"
};

uint16_t menu_get_num_sections_callback(MenuLayer *menu_layer, void *data) {
  return 2;
}

uint16_t get_amount_of_cities(){
  uint16_t amount = 0;
  for(int i=0; i < MAX_AMOUNT_OF_CITIES; i++){
    if(cities[i].exists){
      amount++;
    }
    else{
      break;
    }
  }
  
  return amount;
} 

uint16_t menu_get_num_rows_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    
  switch(section_index){
    case 0:
      return get_amount_of_cities();
    case 1:
      return 1;
    default:
      return 0;
  }
}

int16_t menu_get_header_height_callback(MenuLayer *menu_layer, uint16_t section_index, void *data) {
    return MENU_CELL_BASIC_HEADER_HEIGHT;
}

void menu_draw_header_callback(GContext* ctx, const Layer *cell_layer, uint16_t section_index, void *data) {
    switch(section_index){
      case 0:
//         menu_cell_basic_header_draw(ctx, cell_layer, "Cities");
        break;
      case 1:
//         menu_cell_basic_header_draw(ctx, cell_layer, "More...");
        break;      
    }
}

void menu_draw_row_callback(GContext* ctx, const Layer *cell_layer, MenuIndex *cell_index, void *data) {
//   char subtitleText[1][20];
  
//   subtitleText = cities[cell_index->row].condition[0];
  
  switch(cell_index->section){
      case 0:
        menu_cell_basic_draw(ctx, cell_layer, cities[cell_index->row].name[0], cities[cell_index->row].subtitle[0], NULL);
        break;
      
      case 1:
            menu_cell_basic_draw(ctx, cell_layer, "Add city", NULL, NULL);
        break;
    }
}
char *get_readable_dictation_status(DictationSessionStatus status){
    switch(status){
        case DictationSessionStatusSuccess:
            return "Success";
        case DictationSessionStatusFailureTranscriptionRejected:
            return "User rejected success";
        case DictationSessionStatusFailureTranscriptionRejectedWithError:
            return "User rejected error";
        case DictationSessionStatusFailureSystemAborted:
            return "Too many errors, UI gave up";
        case DictationSessionStatusFailureNoSpeechDetected:
            return "No speech, UI exited";
        case DictationSessionStatusFailureConnectivityError:
            return "No BT/internet connection";
        case DictationSessionStatusFailureDisabled:
            return "Voice dictation disabled";
        case DictationSessionStatusFailureInternalError:
            return "Internal error";
        case DictationSessionStatusFailureRecognizerError:
            return "Failed to transcribe speech";
    }
    return "Unknown";
}

void send_weather_request(char *city){
  DictionaryIterator *iter;
  app_message_outbox_begin(&iter);
  
  if(iter == NULL){
    APP_LOG(APP_LOG_LEVEL_ERROR, "Iter is null! Not sending");
    return;
  }
  
  dict_write_cstring(iter, MESSAGE_KEY_getWeather, city);
  dict_write_end(iter);
  
  app_message_outbox_send(); 
}

void dictation_session_callback(DictationSession *session, DictationSessionStatus status, char *transcription, void *context){
  switch(status){
    case DictationSessionStatusSuccess:
      send_weather_request(transcription);
      break;
    case DictationSessionStatusFailureTranscriptionRejected:
      break;
    default:
//       error_window_set_error(get_readable_dictation_status(status));
      error_window_show(get_readable_dictation_status(status));
      break;
  }
}

void launch_dictation(){
  static char last_text[40];
  
  DictationSession *session = dictation_session_create(sizeof(last_text), dictation_session_callback, NULL);
  
  if(session == NULL){
    APP_LOG(APP_LOG_LEVEL_ERROR, "Dictation Session not created");
    return;
  }
  
  dictation_session_start(session);
}

void menu_select_callback(MenuLayer *menu_layer, MenuIndex *cell_index, void *data) {
// 	APP_LOG(APP_LOG_LEVEL_INFO, cell_index);
  switch(cell_index->section){
    case 0:
      for(int i=0; i < MAX_AMOUNT_OF_CITIES-1; i++){  
        //The plan is to delete the city we want removed, then shift the rest up one
        if(i >= cell_index->row){
          City nonExistingCity = {
              .exists = false
            };
            City tempCity = cities[i+1];
          
            cities[i] = tempCity;
            cities[i+1] = nonExistingCity;
        }
      }
      main_window_save_cities();
    
      menu_layer_reload_data(mainMenuLayer);
      
//       uint32_t pattern[] = {
//         150, 50, 100, 10, 20
//       };
    
//       VibePattern vibe = {
//         .durations = pattern,
//         .num_segments = ARRAY_LENGTH(pattern)
//       };
      
//       vibes_enqueue_custom_pattern(vibe);
      break;
    
    case 1:
      launch_dictation();
      break;
  }
  
//   error_window_show("Error DAWG!");

}


void process_tuple(Tuple *t){
    uint32_t key = t->key;
    int value = t->value->int32;
    
    if(key == MESSAGE_KEY_icon ){
      currentCityToWrite.condition = value;
    }
    else if(key == MESSAGE_KEY_cityid){
      currentCityToWrite.id = value;
    }
    else if(key == MESSAGE_KEY_temperature){
      currentCityToWrite.temperature = value;
    }
    else if(key == MESSAGE_KEY_cityname){
      strncpy(currentCityToWrite.name[0], t->value->cstring, sizeof(currentCityToWrite.name[0])) ;
    }
    else if(key == MESSAGE_KEY_color_picker){
      GColor color = GColorFromHEX(t->value->int32);
      menu_layer_set_highlight_colors(mainMenuLayer, color, gcolor_legible_over(color));
    }
    else{
      return;
    }
  
    APP_LOG(APP_LOG_LEVEL_INFO, "Got key %d with value %d", (int)key, value);
}

void message_inbox(DictionaryIterator *iter, void *context){  
    Tuple *t = dict_read_first(iter);
    if(t){
        process_tuple(t);
    }
    while(t != NULL){
        t = dict_read_next(iter);
        if(t){
            process_tuple(t);
        }
    }
    //Build the subtitle for the data we just got
    snprintf(currentCityToWrite.subtitle[0], sizeof(currentCityToWrite.subtitle[0]), "%d°, %s", currentCityToWrite.temperature, conditions[currentCityToWrite.condition]);
  
    //See if this city already exists. if so, just update it. 
     for(int i = 0; i < MAX_AMOUNT_OF_CITIES; i++){
        if(cities[i].id == currentCityToWrite.id){
          currentCityToWrite.exists = true;
          cities[i] = currentCityToWrite;
        }
    }
    
    //If the city doesnt already exits, add it to our list of cities
    if(!currentCityToWrite.exists){
      for(int i = 0; i < MAX_AMOUNT_OF_CITIES; i++){
        if(!cities[i].exists){
          currentCityToWrite.exists = true;
          cities[i] = currentCityToWrite;
          vibes_double_pulse();
          break;
        }
      }
    }
      
  menu_layer_reload_data(mainMenuLayer);
  
//    vibes_short_pulse();
//   vibes_long_pulse();
  
  //Save the new list of cities
  main_window_save_cities();
  
  currentCityToWrite.exists = false;
}

void message_inbox_dropped(AppMessageResult reason, void *context){
    APP_LOG(APP_LOG_LEVEL_INFO, "Message dropped, reason %d.", reason);
}

int currentlyRefreshing = 0;
void refresh_weather(){
  if(currentlyRefreshing < MAX_AMOUNT_OF_CITIES){
    if(cities[currentlyRefreshing].exists){
      send_weather_request(cities[currentlyRefreshing].name[0]);
      currentlyRefreshing++;
      app_timer_register(500, refresh_weather, NULL);
    }
    else{
      app_timer_register(900000, refresh_weather, NULL);
    }
  }
}

void setup_menu_layer(Window *window) {
	Layer *window_layer = window_get_root_layer(window);

    mainMenuLayer = menu_layer_create(GRect(0, 0, 180, 168));
    
    menu_layer_set_callbacks(mainMenuLayer, NULL, (MenuLayerCallbacks){
        .get_num_sections = menu_get_num_sections_callback,
        .get_num_rows = menu_get_num_rows_callback,
        .get_header_height = menu_get_header_height_callback,
        .draw_header = menu_draw_header_callback,
        .draw_row = menu_draw_row_callback,
        .select_click = menu_select_callback,
    });

    menu_layer_set_click_config_onto_window(mainMenuLayer, window);
    layer_add_child(window_layer, menu_layer_get_layer(mainMenuLayer));
  
    menu_layer_set_highlight_colors(mainMenuLayer, GColorBlueMoon, gcolor_legible_over(GColorBlueMoon));


}

//Save cities to storage
int main_window_save_cities(){
  APP_LOG(APP_LOG_LEVEL_INFO, "Saving cities");
  int value = 0;
  for(int i = 0; i < MAX_AMOUNT_OF_CITIES; i++){
      APP_LOG(APP_LOG_LEVEL_INFO, "Saved city %d ", i);
      value += persist_write_data(i, &cities[i], sizeof(City));
  }
  return value;
}

//Read Cities from storage
int main_window_load_cities(){  
  int value = 0;
  for(int i = 0; i < MAX_AMOUNT_OF_CITIES; i++){
      APP_LOG(APP_LOG_LEVEL_INFO, "loaded city %d ", i);
      value += persist_read_data(i, &cities[i], sizeof(City));
  }
  return value;
}

void main_window_load(Window *window){
  setup_menu_layer(window);
  
  app_message_register_inbox_received(message_inbox);
  app_message_open(256, 256);
  
  //set timer to update weather data
  app_timer_register(500, refresh_weather, NULL);

  
}

void main_window_unload(Window *window){
  main_window_destroy(mainMenuLayer);
}

void main_window_create(){  
  mainWindow = window_create();
  
  //Could actually init this struct above and pass it in
  window_set_window_handlers(mainWindow, (WindowHandlers){
    .load = main_window_load,
    .unload = main_window_unload
  });
}

void main_window_destroy(){
  window_destroy(mainWindow);
}

Window *main_window_get_window(){
  return mainWindow;
}