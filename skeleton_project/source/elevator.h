#pragma once
#include "queue.h"
#include "door.h"

typedef struct Elevator_s {
    int current_floor;
    int last_floor;
    bool initial;
    char state; //i = initialize, s = stop, d = down, u = up
    bool stop_button;
} Elevator;

extern Elevator elevator;

void Run_elevator();
void Stop_state();
void Up_state();
void Down_state();