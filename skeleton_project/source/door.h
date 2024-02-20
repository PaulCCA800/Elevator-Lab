#pragma once
#include <stdbool.h>
#include <time.h>

typedef struct Door_s {
    int timer;
    bool door_status;
    bool obstruction;
} Door;

Door door = {.timer = 0, .door_status = 0, .obstruction = 0}

int Get_timer();
bool Get_door_status();
bool Get_obstruction();

void Close_door();
void Open_door();