#pragma once
#define MAX_AMOUNT_OF_CITIES  5
#define MAX_NUMBER_OF_STOPS 100

typedef struct{
  bool exists;
  int condition; //icon
  int temperature;
  int id;
  char name[1][30];
  char subtitle[1][30];
} City;

typedef struct{
  bool exists;
  char id[1][5];
  char name[1][45];
} BusStop;  

void main_window_create();
void main_window_destroy();
int main_window_save_cities();
int main_window_load_cities();
Window *main_window_get_window();

