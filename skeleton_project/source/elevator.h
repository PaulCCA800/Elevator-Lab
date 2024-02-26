#pragma once
#include "queue.h"
#include "door.h"
#include "driver/elevio.h"

typedef struct Elevator_s {
    int current_floor;
    int last_floor;
    char state; //i = initialize, s = stop, d = down, u = up
    char stop_prev_state;
    bool stop_button;
} Elevator;

extern Elevator elevator;

void Initial_state();
void Run_elevator();
void Stop_state();
void Up_state();
void Down_state();