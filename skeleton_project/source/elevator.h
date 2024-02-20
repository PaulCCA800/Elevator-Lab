#pragma once
#include "queue.h"
#include "door.h"

typedef struct Elevator_s {
    int current_floor;
    int last_floor;
    bool intial;
    char state; //i = initialize, s = stop, d = down, u = up
    bool stop_button;
} Elevator;

Elevator elevator = {.current_floor = -1, .last_floor = -1, .intial = 1, .state = 'i', .stop_button = 0};

void Run();
void Stop_state();
void Up_state();
void Down_state();

void Run_motor(Queue current_queue);