#pragma once
#include "driver/elevio.h"
#include "queue.h"
#include <stdbool.h>

typedef struct Panel_s {
    bool pressed;
    int floor;
    bool internal;
    bool up;
} Panel;

extern Panel panel;

void Panel_lights(Queue_ele* q, int value);
void Button_pressed(); //checks if a button is pressed