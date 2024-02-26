#ifndef DOOR_H
#define DOOR_H

#include <stdbool.h>
#include <time.h>
#include "driver/elevio.h"

typedef struct Door_s {
    time_t timer;
    bool door_status;
    bool obstruction;
} Door;

extern Door door;

int Get_timer();
bool Get_door_status();
bool Get_obstruction();

void Close_door();
void Open_door();

#endif