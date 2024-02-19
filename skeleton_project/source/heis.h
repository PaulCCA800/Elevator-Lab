#pragma once
#include "queue.h"
#include "door.h"

struct Heis {
    int current_floor;
    int last_floor;
    bool intial; //i = initialize, s = stop, d = down, u = up
    char state;
    bool stop_button;
};

Heis heis {.current_floor = -1, .last_floor = -1, .intial = 1, .state = 'i', .stop_button = 0}

void Run_motor(Queue current_queue);