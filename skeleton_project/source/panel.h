#pragma once
#include "driver/elevio.h"
#include "queue.h"

struct Panel {
    bool pressed;
    int floor;
    bool internal;
    bool up;
};

Panel panel {.pressed = 0, .floor = -1, .internal = 0, .up = 0}

void Button_pressed(Panel panel); //checks if a button is pressed and returns it's associated queue object if it is