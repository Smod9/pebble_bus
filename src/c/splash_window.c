#include <pebble.h>
#include "splash_window.h"

Window *splashWindow;
GBitmap *splashImage;
BitmapLayer *splashImageLayer;
TextLayer *splashImageTitle;

void splash_window_load(Window *window){
  Layer *window_layer = window_get_root_layer(window);
  
  //Set the gbitmap to the resource we want
  //Note: Resources can be referenced like `RESOURCE_ID_[resource_id]
  splashImage = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SPLASH);
  splashImageLayer = bitmap_layer_create(GRect(10,30,168, 100));
  
  bitmap_layer_set_bitmap(splashImageLayer, splashImage);
  bitmap_layer_set_compositing_mode(splashImageLayer, GCompOpSet);
  layer_add_child(window_layer, bitmap_layer_get_layer(splashImageLayer));
  
  splashImageTitle = text_layer_create(GRect(60,120,168, 50));
  text_layer_set_text(splashImageTitle, "RFTA Buses!");
//   text_layer_set_text_alignment(splashImageTitle, GTextAlignmentCenter);
  layer_add_child(window_layer, text_layer_get_layer(splashImageTitle));
}

void splash_window_unload(Window *window){
  gbitmap_destroy(splashImage);
  bitmap_layer_destroy(splashImageLayer);
  text_layer_destroy(splashImageTitle);
}

void splash_window_disappear(Window *window){
  window_stack_remove(window, true);
}

void splash_window_create(){  
  splashWindow = window_create();
  
  //Could actually init this struct above and pass it in
  window_set_window_handlers(splashWindow, (WindowHandlers){
    .load = splash_window_load,
    .unload = splash_window_unload,
    .disappear = splash_window_disappear
  });
}

void splash_window_destroy(){
  window_destroy(splashWindow);
}

Window *splash_window_get_window(){
  return splashWindow;
}